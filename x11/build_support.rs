use anyhow::{anyhow, Context, Result};
use std::env;
use std::fs;
use std::path::{Path, PathBuf};
use std::process::Command;

pub(crate) fn pkg_config_path_with_prefix(prefix: &Path) -> String {
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

pub(crate) fn build_autotools(
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

    let src_dir = prepare_source_tree(
        &pkg_dir,
        &out_dir
            .join("ctb-vendored-x11")
            .join("unpacked")
            .join(pkg),
    )
    .with_context(|| format!("could not prepare source dir for {pkg} in {}", pkg_dir.display()))?;
    let build_root = out_dir.join("ctb-vendored-x11").join("build").join(pkg);
    let src_copy = build_root.join("src");
    let build_dir = build_root.join("build");

    // Clean build dirs to avoid subtle cross-target reuse.
    let _ = fs::remove_dir_all(&build_root);
    fs::create_dir_all(&build_dir).with_context(|| format!("create build dir for {pkg}"))?;
    copy_dir_recursive(&src_dir, &src_copy).with_context(|| format!("copy sources for {pkg}"))?;

    // Some of the Debian-sourced Xorg tarballs we consume can carry an
    // automake/autoconf toolchain mismatch in their generated files.
    // Regenerate the build system to match the user's installed autotools.
    //
    // Today this is required at least for xtrans.
    let should_autoreconf = pkg == "xtrans" || env::var_os("CTB_X11_AUTORECONF_ALL").is_some();
    if should_autoreconf {
        run_autoreconf(&src_copy, base_env, pkg)?;
    }

    let mut configure_cmd = Command::new("sh");
    configure_cmd.current_dir(&build_dir);
    configure_cmd.arg(src_copy.join("configure"));
    configure_cmd.arg(format!("--prefix={}", prefix.display()));
    configure_cmd.arg("--disable-maintainer-mode");
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

fn run_autoreconf(src_dir: &Path, base_env: &[(String, String)], pkg: &str) -> Result<()> {
    let has_configure_ac = src_dir.join("configure.ac").is_file();
    let has_configure_in = src_dir.join("configure.in").is_file();
    if !has_configure_ac && !has_configure_in {
        // Nothing to regenerate.
        return Ok(());
    }

    if !program_exists("autoreconf")? {
        return Err(anyhow!(
            "autoreconf not found in PATH, but is required to build vendored x11 ({pkg}). \
Install autoconf/automake/libtool (or set CTB_X11_USE_PKG_CONFIG=1 to use system X11)."
        ));
    }

    let mut cmd = Command::new("autoreconf");
    cmd.current_dir(src_dir);
    // -f: force, -i: install missing auxiliary files, -v: verbose
    cmd.arg("-fiv");
    for (k, v) in base_env {
        cmd.env(k, v);
    }
    run(&mut cmd).with_context(|| format!("autoreconf {pkg}"))?;
    Ok(())
}

pub(crate) fn build_meson_xkbcommon(
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
    let build_root = out_dir
        .join("ctb-vendored-x11")
        .join("build")
        .join("libxkbcommon");
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

pub(crate) fn command_to_string(cmd: &Command) -> String {
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
\
c = '{cc}'\n\
\
ar = '{ar}'\n\
\
pkgconfig = '{pkg_config}'\n\
\
\
[host_machine]\n\
\
system = '{system}'\n\
\
cpu_family = '{cpu_family}'\n\
\
cpu = '{cpu}'\n\
\
\
endian = '{endian}'\n\
\
\
[properties]\n\
\
needs_exe_wrapper = true\n"
    );
    fs::write(path, content)
        .with_context(|| format!("write meson cross file at {}", path.display()))?;
    Ok(())
}

fn env_value<'a>(pairs: &'a [(String, String)], key: &str) -> Option<&'a str> {
    pairs
        .iter()
        .find_map(|(k, v)| if k == key { Some(v.as_str()) } else { None })
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
    // scripts/download-x11 downloads Debian source artifacts and unpacks the
    // upstream sources without applying Debian patches. Apply Debian patches
    // here (without relying on dpkg tools) so builds are consistent.

    let upstream_src = find_project_src_dir(pkg_dir)
        .with_context(|| format!("locate upstream source dir under {}", pkg_dir.display()))?;

    let _ = fs::remove_dir_all(unpack_root);
    fs::create_dir_all(unpack_root)
        .with_context(|| format!("create unpack root {}", unpack_root.display()))?;

    let src_copy = unpack_root.join("src");
    fs::create_dir_all(&src_copy).with_context(|| format!("create src dir {}", src_copy.display()))?;
    copy_dir_recursive(&upstream_src, &src_copy).with_context(|| {
        format!(
            "copy upstream sources {} -> {}",
            upstream_src.display(),
            src_copy.display()
        )
    })?;

    apply_debian_patches(pkg_dir, &src_copy)
        .with_context(|| format!("apply Debian patches for {}", pkg_dir.display()))?;

    Ok(src_copy)
}

fn apply_debian_patches(pkg_dir: &Path, src_root: &Path) -> Result<()> {
    // Debian source formats:
    // - 3.0 (quilt): <pkg>_<ver>.debian.tar.* + debian/patches/series
    // - 1.0: <pkg>_<ver>.diff.gz
    //
    // We avoid dpkg/quilt and use common Unix tools instead.

    if !program_exists("patch")? {
        return Err(anyhow!(
            "required program not found: patch (needed to apply Debian patches)"
        ));
    }

    let quilt_dir = find_single_dir(pkg_dir, "*.debian.tar.*")
        .context("find debian tarball")
        .and_then(|debian_tar| {
            if debian_tar.as_os_str().is_empty() {
                Ok(PathBuf::new())
            } else {
                unpack_debian_tar(pkg_dir, &debian_tar, src_root)
            }
        })?;

    if quilt_dir.as_os_str().is_empty() {
        // 1.0 format: apply single diff.gz if present.
        if let Some(diff) = find_first_file(pkg_dir, "*.diff.gz")? {
            apply_patch_gz(&diff, src_root).with_context(|| format!("apply {}", diff.display()))?;
        }
        return Ok(());
    }

    // 3.0 (quilt) format: apply patches in series order.
    let series = quilt_dir.join("debian").join("patches").join("series");
    if !series.exists() {
        return Ok(());
    }

    let series_contents = fs::read_to_string(&series)
        .with_context(|| format!("read quilt series at {}", series.display()))?;

    for line in series_contents.lines() {
        let line = line.trim();
        if line.is_empty() || line.starts_with('#') {
            continue;
        }
        let patch_path = quilt_dir.join("debian").join("patches").join(line);
        if !patch_path.exists() {
            return Err(anyhow!(
                "quilt patch listed in series not found: {}",
                patch_path.display()
            ));
        }
        apply_patch_file(&patch_path, src_root)
            .with_context(|| format!("apply quilt patch {}", patch_path.display()))?;
    }

    Ok(())
}

fn unpack_debian_tar(pkg_dir: &Path, debian_tar: &Path, dst: &Path) -> Result<PathBuf> {
    let work_dir = pkg_dir.join(".ctb_debian");
    let _ = fs::remove_dir_all(&work_dir);
    fs::create_dir_all(&work_dir).context("create debian work dir")?;

    let mut tar = Command::new("tar");
    tar.current_dir(&work_dir);
    tar.arg("-xf");
    tar.arg(debian_tar);
    run(&mut tar).context("unpack debian tarball")?;

    // The debian tarball contents are merged into the upstream root.
    copy_dir_recursive(&work_dir, dst).context("merge debian/ overlay")?;

    Ok(work_dir)
}

fn apply_patch_gz(diff_gz: &Path, src_root: &Path) -> Result<()> {
    let mut cmd = Command::new("sh");
    cmd.current_dir(src_root);
    cmd.arg("-c");
    cmd.arg(format!(
        "gzip -dc '{}' | patch -p1 --forward --batch",
        diff_gz.display()
    ));
    run(&mut cmd).context("apply diff.gz")?;
    Ok(())
}

fn apply_patch_file(patch_file: &Path, src_root: &Path) -> Result<()> {
    let mut cmd = Command::new("patch");
    cmd.current_dir(src_root);
    cmd.arg("-p1");
    cmd.arg("--forward");
    cmd.arg("--batch");
    cmd.arg("-i");
    cmd.arg(patch_file);
    run(&mut cmd).context("patch")?;
    Ok(())
}

fn find_project_src_dir(pkg_dir: &Path) -> Result<PathBuf> {
    // scripts/download-x11 unpacks upstream sources into a single directory
    // under each package dir. Pick the first dir that looks like a project.
    let mut candidates = Vec::new();
    for entry in fs::read_dir(pkg_dir).with_context(|| format!("read {}", pkg_dir.display()))? {
        let entry = entry?;
        let path = entry.path();
        if !path.is_dir() {
            continue;
        }
        let name = entry.file_name();
        let name = name.to_string_lossy();
        if name == "tmp" || name == "debian" || name.starts_with('.') {
            continue;
        }
        // Heuristic: most upstream trees have a configure script or meson.build.
        if path.join("configure").exists() || path.join("meson.build").exists() {
            return Ok(path);
        }
        candidates.push(path);
    }

    if candidates.len() == 1 {
        return Ok(candidates.remove(0));
    }

    Err(anyhow!(
        "could not uniquely determine upstream source directory under {}",
        pkg_dir.display()
    ))
}

fn find_single_dir(root: &Path, pattern: &str) -> Result<PathBuf> {
    // Find a single matching file and return it.
    for entry in fs::read_dir(root).with_context(|| format!("read {}", root.display()))? {
        let entry = entry?;
        let path = entry.path();
        if !path.is_file() {
            continue;
        }
        let file_name = entry.file_name();
        let file_name = file_name.to_string_lossy();
        if glob_match(pattern, &file_name) {
            return Ok(path);
        }
    }
    Ok(PathBuf::new())
}

fn find_first_file(root: &Path, pattern: &str) -> Result<Option<PathBuf>> {
    for entry in fs::read_dir(root).with_context(|| format!("read {}", root.display()))? {
        let entry = entry?;
        let path = entry.path();
        if !path.is_file() {
            continue;
        }
        let file_name = entry.file_name();
        let file_name = file_name.to_string_lossy();
        if glob_match(pattern, &file_name) {
            return Ok(Some(path));
        }
    }
    Ok(None)
}

fn glob_match(pattern: &str, value: &str) -> bool {
    // Very small glob matcher for patterns used here ("*.ext" and "prefix*" and
    // exact matches). Avoid pulling in dependencies in build scripts.
    if let Some(rest) = pattern.strip_prefix("*") {
        return value.ends_with(rest);
    }
    if let Some(rest) = pattern.strip_suffix("*") {
        return value.starts_with(rest);
    }
    pattern == value
}

fn copy_dir_recursive(src: &Path, dst: &Path) -> Result<()> {
    fs::create_dir_all(dst).with_context(|| format!("create dir {}", dst.display()))?;

    for entry in fs::read_dir(src).with_context(|| format!("read dir {}", src.display()))? {
        let entry = entry?;
        let path = entry.path();
        let dst_path = dst.join(entry.file_name());
        if path.is_dir() {
            copy_dir_recursive(&path, &dst_path)?;
        } else {
            fs::copy(&path, &dst_path).with_context(|| {
                format!(
                    "copy file {} -> {}",
                    path.display(),
                    dst_path.display()
                )
            })?;
        }
    }

    Ok(())
}

fn run(cmd: &mut Command) -> Result<()> {
    let status = cmd
        .status()
        .with_context(|| format!("failed to execute {}", cmd.get_program().to_string_lossy()))?;
    if !status.success() {
        return Err(anyhow!("command failed with exit code {status}"));
    }
    Ok(())
}
