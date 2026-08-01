#!/usr/bin/env bash

packages=(
  "DefinitelyTyped-partial"
  "egui"
  "egui_software_backend"
  "egui-winit"
  "matchbox_socket"
  "seabios"
  "smithay-clipboard"
  "softbuffer"
  "tiny-xlib"
  "turso_sdk_kit"
#  "TypeScript" - see generate-typescript-diff.sh - separate file due to long time to generate
  "undici"
  "v86"
  "seabios"
  "warcat"
  "wayland-scanner"
  "winit"
  "x11rb"
  "xkbcommon-rs"
  "yaxi"
  "zbus_xml"
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
    if [[ "$pkg" == "egui_software_backend" ]] ; then
        rm -r ./original-egui_software_backend/examples
    fi
    diff -uraN original-"$pkg" ./"$pkg"  >> ../vendor.diff || true
done
cd .. || exit 1
rm -r diff-tmp
