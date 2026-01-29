#!/usr/bin/env bash

packages=(
  "egui_software_backend"
  "raw-window-handle"
  "smithay-clipboard"
  "softbuffer"
  "winit"
  "x11"
)

find diff-tmp -exec chmod u+w {} \;
rm -r diff-tmp
mkdir diff-tmp
cd diff-tmp || exit 1

[[ -f ../vendor.diff ]] && rm ../vendor.diff
for pkg in "${packages[@]}"; do
    cp -r ../upstream-for-reference/"$pkg" ./original-"$pkg"
    cp -r ../"$pkg" ./"$pkg"
    find . -exec chmod u+w {} \;
    if [[ "$pkg" == "x11" ]] ; then
        rm ./original-x11/build.rs
        rm -r ./x11/c_src
        rm ./x11/build.rs
        rm ./x11/build_support.rs
    elif [[ "$pkg" == "egui_software_backend" ]] ; then
        rm -r ./original-egui_software_backend/examples
    fi
    diff -uraN original-"$pkg" ./"$pkg"  >> ../vendor.diff || true
done
cd .. || exit 1
rm -r diff-tmp
