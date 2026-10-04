#!/usr/bin/env bash
# SPDX-License-Identifier: AGPL-3.0-or-later
#
# This file is part of Collective Toolbox, a database and document workspace and utilities.
# Copyright (C) 2026 Collective Toolbox Developers
# Contact: info@collectivetoolbox.com
#
# This program is free software: you can redistribute it and/or modify it under
# the terms of the GNU Affero General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License along
# with this program.  If not, see <https://www.gnu.org/licenses/>.

set -euo pipefail

SCRIPT_DIR="$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
DEFAULT_TARGET="${SCRIPT_DIR}/RustPython-f51f27c949a5675a5902e55e32139abbf852dfc5"

show_help() {
    cat <<EOF
Usage: $(basename "$0") [OPTIONS]

Locate and clean generated files, build artifacts, caches, and precompiled
binaries in vendored RustPython.

Options:
  -n, --dry-run, --locate  Locate and display generated files without deleting
  -v, --verbose            Show detailed information for each item
  -t, --target DIR         Target directory (default: ${DEFAULT_TARGET})
      --all                Also clean generated source/lock files (data.inc.rs,
                           _opcode_metadata.py, upgrade-pylib.lock.yml)
  -h, --help               Show this help message
EOF
}

DRY_RUN="false"
VERBOSE="false"
INCLUDE_ALL="true"
TARGET_DIR="${DEFAULT_TARGET}"

while [[ $# -gt 0 ]]; do
    case "$1" in
        -n|--dry-run|--locate)
            DRY_RUN="true"
            shift
            ;;
        -v|--verbose)
            VERBOSE="true"
            shift
            ;;
        -t|--target)
            if [[ $# -lt 2 ]]; then
                echo "Error: --target requires a directory argument" >&2
                exit 1
            fi
            TARGET_DIR="$2"
            shift 2
            ;;
        --skip-required)
            INCLUDE_ALL="false"
            shift
            ;;
        -h|--help)
            show_help
            exit 0
            ;;
        *)
            echo "Error: Unknown option '$1'" >&2
            show_help >&2
            exit 1
            ;;
    esac
done

if [[ ! -d "${TARGET_DIR}" ]]; then
    echo "Error: Target directory '${TARGET_DIR}' does not exist." >&2
    exit 1
fi

# Canonicalize target path
TARGET_DIR="$(readlink -f "${TARGET_DIR}")"

remove_item() {
    local item="$1"
    if [[ -d "${item}" && ! -L "${item}" ]]; then
        rm -r "${item}" || {
            echo "Error: Failed to remove directory: ${item}" >&2
            return 1
        }
    elif [[ -f "${item}" || -L "${item}" || -e "${item}" ]]; then
        rm "${item}" || {
            echo "Error: Failed to remove file: ${item}" >&2
            return 1
        }
    fi
}

count_found=0
total_bytes=0

# Array of found items
declare -a found_items=()
declare -a found_categories=()

add_item() {
    local path="$1"
    local category="$2"
    if [[ -e "${path}" || -L "${path}" ]]; then
        found_items+=("${path}")
        found_categories+=("${category}")
        count_found=$((count_found + 1))
        local size=0
        if [[ -f "${path}" || -L "${path}" ]]; then
            size="$(stat -c %s "${path}" 2>/dev/null || echo 0)"
        elif [[ -d "${path}" ]]; then
            size="$(du -sb "${path}" 2>/dev/null | cut -f1 || echo 0)"
        fi
        total_bytes=$((total_bytes + size))
    fi
}

echo "Scanning for generated files in ${TARGET_DIR}..."

# 1. Precompiled binary executables
while IFS= read -r file; do
    add_item "${file}" "Precompiled binary"
done < <(find "${TARGET_DIR}" -type f \( -name '*.exe' -o -name '*.dll' -o -name '*.so' -o -name '*.dylib' -o -name '*.o' -o -name '*.a' \) 2>/dev/null || true)

# Compiled .wasm files (excluding Dockerfile.wasm or similar)
while IFS= read -r file; do
    if [[ "$(basename "${file}")" != Dockerfile* ]]; then
        add_item "${file}" "Compiled WebAssembly"
    fi
done < <(find "${TARGET_DIR}" -type f -name '*.wasm' 2>/dev/null || true)

# 2. Rust / Cargo build artifacts
while IFS= read -r dir; do
    add_item "${dir}" "Cargo target directory"
done < <(find "${TARGET_DIR}" -type d -name 'target' 2>/dev/null || true)

while IFS= read -r file; do
    add_item "${file}" "Cargo fix backup file"
done < <(find "${TARGET_DIR}" -type f -name '*.rs.bk' 2>/dev/null || true)

# 3. Python bytecode & compiler caches
while IFS= read -r file; do
    add_item "${file}" "Python bytecode"
done < <(find "${TARGET_DIR}" -type f \( -name '*.pyc' -o -name '*.pyo' -o -name '*.bytecode' \) 2>/dev/null || true)

while IFS= read -r dir; do
    add_item "${dir}" "Python cache directory"
done < <(find "${TARGET_DIR}" -type d -name '__pycache__' 2>/dev/null || true)

while IFS= read -r dir; do
    add_item "${dir}" "Pytest cache directory"
done < <(find "${TARGET_DIR}" -type d -name '*.pytest_cache' 2>/dev/null || true)

while IFS= read -r dir; do
    add_item "${dir}" "Cache directory"
done < <(find "${TARGET_DIR}" -type d -name '.cache' 2>/dev/null || true)

# 4. Profiling and build logs
while IFS= read -r file; do
    add_item "${file}" "Profiling / build log"
done < <(find "${TARGET_DIR}" -type f \( -name 'flame-graph.html' -o -name 'flame.txt' -o -name 'flamescope.json' -o -name 'wasm-pack.log' -o -name 'geckodriver.log' \) 2>/dev/null || true)

# 5. Web and package manager build outputs
for dir_pattern in "wasm/bin" "wasm/pkg" "wasm/dist" "wapm_packages"; do
    if [[ -d "${TARGET_DIR}/${dir_pattern}" ]]; then
        add_item "${TARGET_DIR}/${dir_pattern}" "Package / Web build artifact"
    fi
done

while IFS= read -r dir; do
    add_item "${dir}" "Node modules directory"
done < <(find "${TARGET_DIR}" -type d -name 'node_modules' 2>/dev/null || true)

for lock_file in "wapm.lock" "crates/sre_engine/Cargo.lock"; do
    if [[ -f "${TARGET_DIR}/${lock_file}" ]]; then
        add_item "${TARGET_DIR}/${lock_file}" "Generated package lockfile"
    fi
done

while IFS= read -r file; do
    add_item "${file}" "Generated Pipfile lock"
done < <(find "${TARGET_DIR}" -type f -name 'Pipfile.lock' 2>/dev/null || true)

# 6. Test outputs and generated slices
for generated_test in \
    "extra_tests/cpython_tests_results.json" \
    "extra_tests/cpython_generated_slices.py" \
    "crates/doc/generated"
do
    if [[ -e "${TARGET_DIR}/${generated_test}" ]]; then
        add_item "${TARGET_DIR}/${generated_test}" "Generated test/doc output"
    fi
done

while IFS= read -r file; do
    add_item "${file}" "Generated test snippet"
done < <(find "${TARGET_DIR}/extra_tests/snippets" -type f -name 'whats_left_*.py' 2>/dev/null || true)

# 7. Editor and environment files gitignored by RustPython
for editor_file in ".vscode" ".idea" ".repl_history.txt" "wasm/demo/.envrc"; do
    if [[ -e "${TARGET_DIR}/${editor_file}" ]]; then
        add_item "${TARGET_DIR}/${editor_file}" "Gitignored editor / environment config"
    fi
done

while IFS= read -r file; do
    add_item "${file}" "Editor swap / backup file"
done < <(find "${TARGET_DIR}" -type f \( -name '*.swp' -o -name '*.swo' -o -name '*~' -o -name '*.orig' -o -name '*.rej' \) 2>/dev/null || true)

# 8. Collective Toolbox workspace codegen files
while IFS= read -r file; do
    add_item "${file}" "Workspace codegen artifact"
done < <(find "${TARGET_DIR}" -type f \( -name '*.generated.*' -o -name '*.dtos.generated.rs' -o -name 'generated.rs' \) 2>/dev/null || true)

# 9. Doc database stubbing (crates/doc/src/data.inc.rs)
DOC_DATA_INC="${TARGET_DIR}/crates/doc/src/data.inc.rs"
DOC_STUB='// Auto-generated stub for offline/vendored build
pub static DB: phf::Map<&'\''static str, &'\''static str> = phf::phf_map! {};'

needs_doc_stub="false"
if [[ -d "${TARGET_DIR}/crates/doc/src" ]]; then
    if [[ ! -f "${DOC_DATA_INC}" ]] || ! grep -q 'pub static DB: phf::Map<&'\''static str, &'\''static str> = phf::phf_map! {};' "${DOC_DATA_INC}" 2>/dev/null; then
        needs_doc_stub="true"
        add_item "${DOC_DATA_INC}" "Generated doc DB (replace with empty stub)"
    fi
fi

# 10. Optional generated source files (--all)
if [[ "${INCLUDE_ALL}" == "true" ]]; then
    for gen_src in \
        "Lib/_opcode_metadata.py" \
        ".github/workflows/upgrade-pylib.lock.yml"
    do
        if [[ -f "${TARGET_DIR}/${gen_src}" ]]; then
            add_item "${TARGET_DIR}/${gen_src}" "Generated source / workflow lock"
        fi
    done
fi

# 11. Symlinks checked out as text files
KNOWN_SYMLINKS=(
    "crates/pylib/Lib:../../Lib"
    "crates/vm/Lib/core_modules/codecs.py:../../../../Lib/codecs.py"
    "crates/vm/Lib/core_modules/copyreg.py:../../../../Lib/copyreg.py"
    "crates/vm/Lib/core_modules/encodings_ascii.py:../../../../Lib/encodings/ascii.py"
    "crates/vm/Lib/core_modules/encodings_utf_8.py:../../../../Lib/encodings/utf_8.py"
    "crates/vm/Lib/python_builtins/__hello__.py:../../../../Lib/__hello__.py"
    "crates/vm/Lib/python_builtins/__phello__:../../../../Lib/__phello__"
    "crates/vm/Lib/python_builtins/_frozen_importlib.py:../../../../Lib/importlib/_bootstrap.py"
    "crates/vm/Lib/python_builtins/_frozen_importlib_external.py:../../../../Lib/importlib/_bootstrap_external.py"
    "crates/vm/Lib/python_builtins/_thread.py:../../../../Lib/_dummy_thread.py"
)

for entry in "${KNOWN_SYMLINKS[@]}"; do
    symlink_path="${entry%%:*}"
    full_path="${TARGET_DIR}/${symlink_path}"
    if [[ -f "${full_path}" && ! -L "${full_path}" ]]; then
        add_item "${full_path}" "Text symlink (restore actual symlink)"
    fi
done

if [[ ${count_found} -eq 0 ]]; then
    echo "No generated files found in ${TARGET_DIR}."
    exit 0
fi

echo "Found ${count_found} generated item(s) (~$((total_bytes / 1024)) KB total):"
echo

for i in "${!found_items[@]}"; do
    item="${found_items[$i]}"
    category="${found_categories[$i]}"
    rel_path="${item#"${TARGET_DIR}/"}"
    item_type="file"
    if [[ -d "${item}" ]]; then
        item_type="dir"
    fi

    if [[ "${VERBOSE}" == "true" ]]; then
        echo "  [${category}] (${item_type}) ${rel_path}"
    else
        echo "  ${rel_path} (${category})"
    fi
done

echo

if [[ "${DRY_RUN}" == "true" ]]; then
    echo "Dry run complete. No files were removed or modified."
    exit 0
fi

echo "Cleaning ${count_found} item(s)..."
cleaned_count=0
for item in "${found_items[@]}"; do
    rel_path="${item#"${TARGET_DIR}/"}"
    if [[ "${item}" == "${DOC_DATA_INC}" ]]; then
        printf '%s\n' "${DOC_STUB}" > "${DOC_DATA_INC}"
        cleaned_count=$((cleaned_count + 1))
        echo "  Stubbed: crates/doc/src/data.inc.rs (empty phf_map)"
    else
        is_symlink_restoration="false"
        symlink_target=""
        for entry in "${KNOWN_SYMLINKS[@]}"; do
            s_path="${entry%%:*}"
            s_target="${entry#*:}"
            if [[ "${rel_path}" == "${s_path}" ]]; then
                is_symlink_restoration="true"
                symlink_target="${s_target}"
                break
            fi
        done

        if [[ "${is_symlink_restoration}" == "true" ]]; then
            remove_item "${item}"
            ln -s "${symlink_target}" "${item}" || {
                echo "Error: Failed to create symlink: ${item} -> ${symlink_target}" >&2
                exit 1
            }
            cleaned_count=$((cleaned_count + 1))
            echo "  Restored symlink: ${rel_path} -> ${symlink_target}"
        elif [[ -e "${item}" || -L "${item}" ]]; then
            remove_item "${item}"
            cleaned_count=$((cleaned_count + 1))
            if [[ "${VERBOSE}" == "true" ]]; then
                echo "  Removed: ${rel_path}"
            fi
        fi
    fi
done

echo "Successfully cleaned/stubbed ${cleaned_count} generated item(s)."
