// x11-rs: Rust bindings for X11 libraries
// The X11 libraries are available under the MIT license.
// These bindings are public domain.

#![allow(clippy::vec_init_then_push)]

extern crate pkg_config;

mod build_support;

use anyhow::{anyhow, Context, Result};
use std::env;
use std::fs;
use std::path::{Path, PathBuf};

fn main() {
    if cfg!(feature = "dox") {
        return;
    }

    if let Err(err) = try_main() {
        eprintln!("x11/build.rs error: {err:#}");
        std::process::exit(1);
    }
}

fn try_main() -> Result<()> {
    println!("cargo:rerun-if-changed=build.rs");
    println!("cargo:rerun-if-changed=build_support.rs");
    println!("cargo:rerun-if-changed=c_src");
    println!("cargo:rerun-if-env-changed=CTB_X11_USE_PKG_CONFIG");
    println!("cargo:rerun-if-env-changed=CTB_X11_AUTORECONF_ALL");

    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").context("CARGO_MANIFEST_DIR not set")?);
    let c_src_dir = manifest_dir.join("c_src");

    // Allow opting back into the original pkg-config behavior.
    if env::var_os("CTB_X11_USE_PKG_CONFIG").is_some() {
        return probe_with_pkg_config(None);
    }

    let out_dir = PathBuf::from(env::var("OUT_DIR").context("OUT_DIR not set")?);
    let prefix = out_dir.join("ctb-vendored-x11").join("prefix");
    fs::create_dir_all(&prefix).context("create vendored X11 prefix dir")?;

    // Build a minimal dependency chain into our private prefix.
    //
    // Important: this is intentionally target-aware (Cargo TARGET/HOST, CC/AR
    // resolution via the `cc` crate). If the sysroot provides some deps (e.g.
    // libXau/libXrender), configure/pkg-config will pick those up.
    build_vendored_x11(&c_src_dir, &out_dir, &prefix)?;

    // Ensure subsequent pkg-config probes use our prefix first.
    let pkg_config_path = build_support::pkg_config_path_with_prefix(&prefix);
    env::set_var("PKG_CONFIG_PATH", &pkg_config_path);
    env::set_var("PKG_CONFIG_ALLOW_CROSS", "1");

    // Also expose the prefix for downstream build scripts if needed.
    println!("cargo:rustc-link-search=native={}", prefix.join("lib").display());
    println!("cargo:rustc-link-search=native={}", prefix.join("lib64").display());

    probe_with_pkg_config(Some(&pkg_config_path))
}

fn probe_with_pkg_config(pkg_config_path: Option<&str>) -> Result<()> {
    if let Some(path) = pkg_config_path {
        env::set_var("PKG_CONFIG_PATH", path);
        env::set_var("PKG_CONFIG_ALLOW_CROSS", "1");
    }

    let deps = [
        ("gl", "1", "glx"),
        ("x11", "1.4.99.1", "xlib"),
        ("x11-xcb", "1.6", "xlib_xcb"),
        ("xcursor", "1.1", "xcursor"),
        ("xext", "1.3", "dpms"),
        ("xfixes", "3.1", "xfixes"),
        ("xft", "2.1", "xft"),
        ("xi", "1.7", "xinput"),
        ("xinerama", "1.1", "xinerama"),
        ("xmu", "1.1", "xmu"),
        ("xrandr", "1.5", "xrandr"),
        ("xrender", "0.9.6", "xrender"),
        ("xpresent", "1", "xpresent"),
        ("xscrnsaver", "1.2", "xss"),
        ("xt", "1.1", "xt"),
        ("xtst", "1.2", "xtst"),
        ("xxf86vm", "1.1", "xf86vmode"),
    ];

    for &(dep, version, feature) in deps.iter() {
        let var = format!("CARGO_FEATURE_{}", feature.to_uppercase().replace('-', "_"));
        if env::var_os(var).is_none() {
            continue;
        }

        let mut cfg = pkg_config::Config::new();
        cfg.atleast_version(version);
        // Prefer the vendored prefix when present, but still allow sysroot libs
        // to satisfy transitive deps.
        cfg.probe(dep)
            .with_context(|| format!("pkg-config probe failed for {dep} (>= {version})"))?;
    }

    Ok(())
}

fn build_vendored_x11(c_src_dir: &Path, out_dir: &Path, prefix: &Path) -> Result<()> {
    // If these are missing, the user likely hasn't run scripts/download-x11 yet.
    if !c_src_dir.exists() {
        return Err(anyhow!(
            "missing c_src directory at {} (run scripts/download-x11)",
            c_src_dir.display()
        ));
    }

    let target = env::var("TARGET").context("TARGET not set")?;
    let host = env::var("HOST").context("HOST not set")?;
    let jobs = env::var("NUM_JOBS").ok();

    let tool = cc::Build::new().target(&target).host(&host).get_compiler();
    let ar = cc::Build::new().target(&target).host(&host).get_archiver();
    let ranlib = cc::Build::new().target(&target).host(&host).get_ranlib();

    let tool_cflags = tool
        .args()
        .iter()
        .map(|s| s.to_string_lossy().to_string())
        .collect::<Vec<_>>()
        .join(" ");

    let mut base_env = Vec::<(String, String)>::new();
    base_env.push(("CC".to_string(), tool.path().to_string_lossy().to_string()));
    base_env.push((
        "AR".to_string(),
        build_support::command_to_string(&ar),
    ));
    base_env.push((
        "RANLIB".to_string(),
        build_support::command_to_string(&ranlib),
    ));

    // Some of the vendored autotools projects may enable maintainer rules that
    // try to invoke version-suffixed tools like `automake-1.16`. Prefer the
    // generic tool names so builds work across distros, and disable maintainer
    // mode in `configure` below to avoid regeneration where possible.
    base_env.push(("AUTOCONF".to_string(), "autoconf".to_string()));
    base_env.push(("AUTOHEADER".to_string(), "autoheader".to_string()));
    base_env.push(("AUTOMAKE".to_string(), "automake".to_string()));
    base_env.push(("ACLOCAL".to_string(), "aclocal".to_string()));

    base_env.push(("PKG_CONFIG_ALLOW_CROSS".to_string(), "1".to_string()));
    base_env.push((
        "PKG_CONFIG_PATH".to_string(),
        build_support::pkg_config_path_with_prefix(prefix),
    ));

    // Preserve user-provided flags, but prepend target tool args.
    let user_cflags = env::var("CFLAGS").unwrap_or_default();
    let combined_cflags = format!("{tool_cflags} {user_cflags}").trim().to_string();
    base_env.push(("CFLAGS".to_string(), combined_cflags));

    let user_cppflags = env::var("CPPFLAGS").unwrap_or_default();
    let combined_cppflags = format!("-I{} {user_cppflags}", prefix.join("include").display())
        .trim()
        .to_string();
    base_env.push(("CPPFLAGS".to_string(), combined_cppflags));

    let user_ldflags = env::var("LDFLAGS").unwrap_or_default();
    let combined_ldflags = format!("-L{} {user_ldflags}", prefix.join("lib").display())
        .trim()
        .to_string();
    base_env.push(("LDFLAGS".to_string(), combined_ldflags));

    let host_arg = if host != target { Some(target.as_str()) } else { None };

    // Build order matters (proto/tools first).
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "xorgproto",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "xtrans",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "xcb-proto",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxdmcp",
    )?;

    // libxcb's `xcb_auth.c` includes <X11/Xauth.h>, which is provided by
    // libXau. When building against a minimal sysroot (e.g. musl), we must
    // build/install libXau into the prefix before libxcb.
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxau",
    )?;

    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxcb",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libx11",
    )?;

    // Higher-level client libs required by several of the dependencies below
    // (and often missing from minimal sysroots).
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxrender",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxext",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxfixes",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxi",
    )?;
    build_support::build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxcursor",
    )?;

    // libxkbcommon uses meson. We'll build it if meson/ninja are available;
    // otherwise, downstream code may still link against a sysroot-provided
    // libxkbcommon.
    let _ = build_support::build_meson_xkbcommon(c_src_dir, out_dir, prefix, &base_env, &target);

    Ok(())
}
