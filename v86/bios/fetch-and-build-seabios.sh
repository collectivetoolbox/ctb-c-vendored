#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../../../../" && pwd)"
SEABIOS_SRC="$REPO_ROOT/vendor/seabios"

if [[ ! -d "$SEABIOS_SRC" ]]; then
    echo "Error: Offline SeaBIOS source directory not found at $SEABIOS_SRC" >&2
    exit 1
fi

OUT_DIR="${V86_BIOS_OUT_DIR:-${1:-$REPO_ROOT/built/v86_out/bios}}"
mkdir -p "$OUT_DIR"

# If precompiled binaries exist in vendor/seabios/out_bin or SCRIPT_DIR, copy them
if [[ -f "$SEABIOS_SRC/out_bin/seabios.bin" ]]; then
    echo "=== Copying offline SeaBIOS binaries from vendor/seabios/out_bin ==="
    cp "$SEABIOS_SRC/out_bin"/*.bin "$OUT_DIR/"
    exit 0
fi

# Otherwise, if python3 and make are present, build from offline vendor/seabios copy in a temporary directory
if command -v python3 >/dev/null 2>&1 && command -v make >/dev/null 2>&1; then
    BUILD_DIR="$REPO_ROOT/built/v86_build_tmp/seabios"
    rm -rf "$BUILD_DIR"
    mkdir -p "$BUILD_DIR"
    echo "=== Building SeaBIOS from offline source vendor/seabios ==="
    cp -r "$SEABIOS_SRC" "$BUILD_DIR/seabios"

    cp "$SCRIPT_DIR/seabios.config" "$BUILD_DIR/seabios/.config"
    make PYTHON=python3 -C "$BUILD_DIR/seabios" -j$(nproc)
    cp "$BUILD_DIR/seabios/out/bios.bin" "$OUT_DIR/seabios.bin"
    cp "$BUILD_DIR/seabios/out/vgabios.bin" "$OUT_DIR/vgabios.bin"

    cp "$SCRIPT_DIR/seabios-debug.config" "$BUILD_DIR/seabios/.config"
    make PYTHON=python3 -C "$BUILD_DIR/seabios" -j$(nproc)
    cp "$BUILD_DIR/seabios/out/bios.bin" "$OUT_DIR/seabios-debug.bin"
    cp "$BUILD_DIR/seabios/out/vgabios.bin" "$OUT_DIR/vgabios-debug.bin"

    rm -rf "$BUILD_DIR"
    exit 0
fi

echo "Warning: Python3 or make not available; copying existing bios files if available"
if ls "$SCRIPT_DIR"/*.bin >/dev/null 2>&1; then
    cp "$SCRIPT_DIR"/*.bin "$OUT_DIR/"
fi
