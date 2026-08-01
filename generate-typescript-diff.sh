#!/usr/bin/env bash

packages=(
  "TypeScript"
)

find diff-ts-tmp -exec chmod u+w {} \;
rm -r diff-ts-tmp
mkdir diff-ts-tmp
cd diff-ts-tmp || exit 1

[[ -f ../vendor-ts.diff ]] && rm ../vendor-ts.diff
for pkg in "${packages[@]}"; do
    cp -r ../upstream-for-reference/"$pkg" ./original-"$pkg"
    cp -r ../"$pkg" ./"$pkg"
    find . -exec chmod u+w {} \;
    diff -uraN original-"$pkg" ./"$pkg"  >> ../vendor-ts.diff || true
done
cd .. || exit 1
rm -r diff-ts-tmp
