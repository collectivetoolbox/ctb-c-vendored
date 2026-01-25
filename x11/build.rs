// x11-rs: Rust bindings for X11 libraries
// The X11 libraries are available under the MIT license.
// These bindings are public domain.

extern crate pkg_config;

use anyhow::{anyhow, Context, Result};
use std::env;
use std::ffi::OsStr;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;

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
    println!("cargo:rerun-if-changed=c_src");

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
    let pkg_config_path = pkg_config_path_with_prefix(&prefix);
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

fn pkg_config_path_with_prefix(prefix: &Path) -> String {
    let mut parts = Vec::new();
    parts.push(prefix.join("lib").join("pkgconfig"));
    parts.push(prefix.join("share").join("pkgconfig"));

    if let Some(existing) = env::var_os("PKG_CONFIG_PATH") {
        parts.extend(env::split_paths(&existing));
    }

    match env::join_paths(parts) {
        Ok(joined) => joined.to_string_lossy().into_owned(),
        Err(_) => String::new(),
    }
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
    base_env.push(("AR".to_string(), command_to_string(&ar)));
    base_env.push((
        "RANLIB".to_string(),
        command_to_string(&ranlib),
    ));
    base_env.push(("PKG_CONFIG_ALLOW_CROSS".to_string(), "1".to_string()));
    base_env.push(("PKG_CONFIG_PATH".to_string(), pkg_config_path_with_prefix(prefix)));

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
    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "xorgproto",
    )?;
    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "xtrans",
    )?;
    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "xcb-proto",
    )?;
    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxdmcp",
    )?;

    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxcb",
    )?;
    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libx11",
    )?;
    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxfixes",
    )?;
    build_autotools(
        c_src_dir,
        out_dir,
        prefix,
        &base_env,
        host_arg,
        jobs.as_deref(),
        "libxi",
    )?;
    build_autotools(
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
    let _ = build_meson_xkbcommon(c_src_dir, out_dir, prefix, &base_env, &target);

    Ok(())
}

fn build_autotools(
    c_src_dir: &Path,
    out_dir: &Path,
    prefix: &Path,
    base_env: &[(String, String)],
    host_arg: Option<&str>,
    jobs: Option<&str>,
    pkg: &str,
) -> Result<()> {
    let pkg_dir = c_src_dir.join(pkg);
    if !pkg_dir.exists() {
        println!("cargo:warning=vendored x11: missing {pkg_dir:?}; skipping {pkg}");
        return Ok(());
    }

    let src_dir = prepare_source_tree(&pkg_dir, &out_dir.join("ctb-vendored-x11").join("unpacked").join(pkg))
        .with_context(|| format!("could not prepare source dir for {pkg} in {}", pkg_dir.display()))?;
    let build_root = out_dir.join("ctb-vendored-x11").join("build").join(pkg);
    let src_copy = build_root.join("src");
    let build_dir = build_root.join("build");

    // Clean build dirs to avoid subtle cross-target reuse.
    let _ = fs::remove_dir_all(&build_root);
    fs::create_dir_all(&build_dir).with_context(|| format!("create build dir for {pkg}"))?;
    copy_dir_recursive(&src_dir, &src_copy).with_context(|| format!("copy sources for {pkg}"))?;

    let mut configure_cmd = Command::new("sh");
    configure_cmd.current_dir(&build_dir);
    configure_cmd.arg(src_copy.join("configure"));
    configure_cmd.arg(format!("--prefix={}", prefix.display()));
    configure_cmd.arg("--disable-shared");
    configure_cmd.arg("--enable-static");
    configure_cmd.arg("--with-pic");
    if let Some(host) = host_arg {
        configure_cmd.arg(format!("--host={host}"));
    }

    for (k, v) in base_env {
        configure_cmd.env(k, v);
    }

    run(&mut configure_cmd).with_context(|| format!("configure {pkg}"))?;

    let mut make_cmd = Command::new("make");
    make_cmd.current_dir(&build_dir);
    if let Some(j) = jobs {
        make_cmd.arg(format!("-j{j}"));
    }
    for (k, v) in base_env {
        make_cmd.env(k, v);
    }
    run(&mut make_cmd).with_context(|| format!("make {pkg}"))?;

    let mut install_cmd = Command::new("make");
    install_cmd.current_dir(&build_dir);
    install_cmd.arg("install");
    for (k, v) in base_env {
        install_cmd.env(k, v);
    }
    run(&mut install_cmd).with_context(|| format!("make install {pkg}"))?;

    Ok(())
}

fn build_meson_xkbcommon(
    c_src_dir: &Path,
    out_dir: &Path,
    prefix: &Path,
    base_env: &[(String, String)],
    target: &str,
) -> Result<()> {
    let pkg_dir = c_src_dir.join("libxkbcommon");
    if !pkg_dir.exists() {
        println!("cargo:warning=vendored x11: missing libxkbcommon sources; skipping");
        return Ok(());
    }

    let src_dir = prepare_source_tree(
        &pkg_dir,
        &out_dir
            .join("ctb-vendored-x11")
            .join("unpacked")
            .join("libxkbcommon"),
    )
    .context("locate libxkbcommon source")?;
    let build_root = out_dir.join("ctb-vendored-x11").join("build").join("libxkbcommon");
    let src_copy = build_root.join("src");
    let build_dir = build_root.join("build");
    let cross_file = build_root.join("cross.ini");

    let _ = fs::remove_dir_all(&build_root);
    fs::create_dir_all(&build_dir).context("create xkbcommon build dir")?;
    copy_dir_recursive(&src_dir, &src_copy).context("copy xkbcommon sources")?;

    if !program_exists("meson")? || !program_exists("ninja")? {
        println!("cargo:warning=vendored x11: meson/ninja not found; skipping libxkbcommon build");
        return Ok(());
    }

    write_meson_cross_file(&cross_file, base_env, target)?;

    let mut setup = Command::new("meson");
    setup.current_dir(&build_root);
    setup.arg("setup");
    setup.arg(&build_dir);
    setup.arg(&src_copy);
    setup.arg(format!("--prefix={}", prefix.display()));
    setup.arg("--libdir=lib");
    setup.arg("--default-library=static");
    setup.arg(format!("--cross-file={}", cross_file.display()));
    setup.arg("-Ddocs=false");
    setup.arg("-Dtests=false");
    for (k, v) in base_env {
        setup.env(k, v);
    }
    run(&mut setup).context("meson setup libxkbcommon")?;

    let mut build = Command::new("ninja");
    build.current_dir(&build_dir);
    for (k, v) in base_env {
        build.env(k, v);
    }
    run(&mut build).context("ninja build libxkbcommon")?;

    let mut install = Command::new("ninja");
    install.current_dir(&build_dir);
    install.arg("install");
    for (k, v) in base_env {
        install.env(k, v);
    }
    run(&mut install).context("ninja install libxkbcommon")?;

    Ok(())
}

fn program_exists(program: &str) -> Result<bool> {
    let status = Command::new(program).arg("--version").status();
    match status {
        Ok(s) => Ok(s.success()),
        Err(e) if e.kind() == std::io::ErrorKind::NotFound => Ok(false),
        Err(e) => Err(e).with_context(|| format!("failed to run {program} --version")),
    }
}

fn command_to_string(cmd: &Command) -> String {
    let mut s = cmd.get_program().to_string_lossy().to_string();
    for arg in cmd.get_args() {
        s.push(' ');
        s.push_str(&arg.to_string_lossy());
    }
    s
}

fn write_meson_cross_file(path: &Path, base_env: &[(String, String)], target: &str) -> Result<()> {
    let cc = env_value(base_env, "CC").unwrap_or("cc");
    let ar = env_value(base_env, "AR").unwrap_or("ar");
    let pkg_config = env::var("PKG_CONFIG").unwrap_or_else(|_| "pkg-config".to_string());

    let (cpu_family, cpu) = cpu_info_from_target(target);
    let system = if target.contains("linux") { "linux" } else { "unknown" };
    let endian = if target.contains("mips") || target.contains("powerpc64") {
        // Most of our current targets are little-endian; keep this conservative.
        "little"
    } else {
        "little"
    };

    let content = format!(
        "[binaries]\n\
c = '{cc}'\n\
ar = '{ar}'\n\
pkgconfig = '{pkg_config}'\n\
\n\
[host_machine]\n\
system = '{system}'\n\
cpu_family = '{cpu_family}'\n\
cpu = '{cpu}'\n\
endian = '{endian}'\n\
\n\
[properties]\n\
needs_exe_wrapper = true\n",
    );
    fs::write(path, content).with_context(|| format!("write meson cross file at {}", path.display()))?;
    Ok(())
}

fn env_value<'a>(pairs: &'a [(String, String)], key: &str) -> Option<&'a str> {
    pairs.iter().find_map(|(k, v)| if k == key { Some(v.as_str()) } else { None })
}

fn cpu_info_from_target(target: &str) -> (&'static str, &'static str) {
    if target.starts_with("x86_64") {
        return ("x86_64", "x86_64");
    }
    if target.starts_with("i686") || target.starts_with("i586") {
        return ("x86", "i686");
    }
    if target.starts_with("aarch64") {
        return ("aarch64", "aarch64");
    }
    if target.starts_with("armv7") || target.starts_with("arm") {
        return ("arm", "arm");
    }
    if target.starts_with("riscv64") {
        return ("riscv64", "riscv64");
    }
    ("unknown", "unknown")
}

fn prepare_source_tree(pkg_dir: &Path, unpack_root: &Path) -> Result<PathBuf> {
    // Preferred path: if the Debian source artifacts are present, use dpkg-source
    // to apply patches exactly as Debian does.
    let dsc = fs::read_dir(pkg_dir)
        .ok()
        .and_then(|it| {
            it.filter_map(|e| e.ok())
                .map(|e| e.path())
                .find(|p| p.extension() == Some(OsStr::new("dsc")))
        });

    if let Some(dsc_path) = dsc {
        if program_exists("dpkg-source")? {
            let has_orig = fs::read_dir(pkg_dir)
                .ok()
                .map(|it| {
                    it.filter_map(|e| e.ok())
                        .map(|e| e.path())
                        .any(|p| {
                            let Some(name) = p.file_name().and_then(|n| n.to_str()) else {
                                return false;
                            };
                            name.contains(".orig.tar.") && !name.ends_with(".asc")
                        })
                })
                .unwrap_or(false);

            if has_orig {
                let _ = fs::remove_dir_all(unpack_root);
                fs::create_dir_all(unpack_root).with_context(|| {
                    format!("create dpkg-source unpack dir {}", unpack_root.display())
                })?;

                // Copy artifacts into a scratch directory dpkg-source can use.
                for entry in fs::read_dir(pkg_dir)
                    .with_context(|| format!("read dir {}", pkg_dir.display()))?
                {
                    let entry = entry?;
                    let ty = entry.file_type()?;
                    if !ty.is_file() {
                        continue;
                    }
                    let from = entry.path();
                    let to = unpack_root.join(entry.file_name());
                    fs::copy(&from, &to)
                        .with_context(|| format!("copy {} -> {}", from.display(), to.display()))?;
                }

                let mut cmd = Command::new("dpkg-source");
                cmd.current_dir(unpack_root);
                cmd.arg("--skip-pgp-check");
                cmd.arg("-x");
                cmd.arg(
                    dsc_path
                        .file_name()
                        .context("dsc file has no filename")?,
                );
                run(&mut cmd).context("dpkg-source -x")?;

                // dpkg-source creates exactly one directory.
                let produced = fs::read_dir(unpack_root)
                    .with_context(|| format!("read dir {}", unpack_root.display()))?
                    .filter_map(|e| e.ok())
                    .map(|e| e.path())
                    .find(|p| p.is_dir())
                    .context("dpkg-source produced no directory")?;

                return Ok(produced);
            } else {
                println!(
                    "cargo:warning=vendored x11: .dsc found for {}, but missing .orig.tar.*; using pre-unpacked sources",
                    pkg_dir.display()
                );
            }
        } else {
            println!(
                "cargo:warning=vendored x11: dpkg-source not found; using pre-unpacked sources for {}",
                pkg_dir.display()
            );
        }
    }

    find_project_src_dir(pkg_dir)
}

fn find_project_src_dir(pkg_dir: &Path) -> Result<PathBuf> {
    // The repo format is: c_src/<pkg>/<unpacked-project-dir> plus various .dsc/.diff files.
    // Pick the first child directory that looks like a project root.
    let mut candidates = Vec::new();
    for entry in fs::read_dir(pkg_dir).with_context(|| format!("read dir {}", pkg_dir.display()))? {
        let entry = entry?;
        let path = entry.path();
        if !path.is_dir() {
            continue;
        }
        if path.join("configure").is_file() || path.join("meson.build").is_file() {
            candidates.push(path);
        }
    }

    candidates
        .into_iter()
        .next()
        .ok_or_else(|| anyhow!("no project dir with configure/meson.build found"))
}

fn copy_dir_recursive(from: &Path, to: &Path) -> Result<()> {
    fs::create_dir_all(to).with_context(|| format!("create dir {}", to.display()))?;
    for entry in fs::read_dir(from).with_context(|| format!("read dir {}", from.display()))? {
        let entry = entry?;
        let path = entry.path();
        let dest = to.join(entry.file_name());
        let ty = entry.file_type()?;
        if ty.is_dir() {
            copy_dir_recursive(&path, &dest)?;
        } else if ty.is_file() {
            fs::copy(&path, &dest)
                .with_context(|| format!("copy {} -> {}", path.display(), dest.display()))?;
        } else if ty.is_symlink() {
            let target = fs::read_link(&path)
                .with_context(|| format!("readlink {}", path.display()))?;
            std::os::unix::fs::symlink(&target, &dest)
                .with_context(|| format!("symlink {} -> {}", target.display(), dest.display()))?;
        }
    }
    Ok(())
}

fn run(cmd: &mut Command) -> Result<()> {
    let status = cmd
        .status()
        .with_context(|| format!("failed to spawn command: {:?}", cmd))?;
    if !status.success() {
        return Err(anyhow!("command failed with exit code {status}"));
    }
    Ok(())
}
