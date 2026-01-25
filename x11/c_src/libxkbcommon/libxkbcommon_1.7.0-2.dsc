-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Format: 3.0 (quilt)
Source: libxkbcommon
Binary: libxkbcommon0, libxkbcommon0-udeb, libxkbcommon-dev, libxkbcommon-doc, libxkbcommon-tools, libxkbcommon-x11-0, libxkbcommon-x11-dev, libxkbregistry0, libxkbregistry-dev
Architecture: any all
Version: 1.7.0-2
Maintainer: Debian X Strike Force <debian-x@lists.debian.org>
Uploaders: Michael Stapelberg <stapelberg@debian.org>
Homepage: https://www.xkbcommon.org/
Standards-Version: 4.6.1
Vcs-Browser: https://salsa.debian.org/xorg-team/lib/libxkbcommon
Vcs-Git: https://salsa.debian.org/xorg-team/lib/libxkbcommon.git
Testsuite: autopkgtest
Testsuite-Triggers: build-essential, pkg-config
Build-Depends: debhelper-compat (= 13), bison, dh-exec, doxygen, flex, graphviz, meson, pkgconf, quilt, libwayland-dev [linux-any], libxcb-xkb-dev, libxml2-dev, wayland-protocols [linux-any], x11-xkb-utils <!nocheck>, x11proto-dev, xkb-data <!nocheck>, xvfb <!nocheck>
Package-List:
 libxkbcommon-dev deb libdevel optional arch=any
 libxkbcommon-doc deb doc optional arch=all
 libxkbcommon-tools deb graphics optional arch=any
 libxkbcommon-x11-0 deb libs optional arch=any
 libxkbcommon-x11-dev deb libdevel optional arch=any
 libxkbcommon0 deb libs optional arch=any
 libxkbcommon0-udeb udeb debian-installer optional arch=any
 libxkbregistry-dev deb libdevel optional arch=any
 libxkbregistry0 deb libs optional arch=any
Checksums-Sha1:
 6c9b00437feb6389470bb6dbce66f6f7d16f09bc 534312 libxkbcommon_1.7.0.orig.tar.xz
 361645b91d7ff5cb838929a756165a5e2ea46512 8464 libxkbcommon_1.7.0-2.debian.tar.xz
Checksums-Sha256:
 65782f0a10a4b455af9c6baab7040e2f537520caa2ec2092805cdfd36863b247 534312 libxkbcommon_1.7.0.orig.tar.xz
 fcf3db4a281477b93a3bd2ae00bbbd8ea2e589e12301112547779a17ec7c6b80 8464 libxkbcommon_1.7.0-2.debian.tar.xz
Files:
 b05b1a0d473189efb2dd995dd944f152 534312 libxkbcommon_1.7.0.orig.tar.xz
 5ce30b0a2fbe4852a1f398a2be3572d6 8464 libxkbcommon_1.7.0-2.debian.tar.xz

-----BEGIN PGP SIGNATURE-----

iQIzBAEBCgAdFiEEdS3ifE3rFwGbS2Yjy3AxZaiJhNwFAmdf+4kACgkQy3AxZaiJ
hNx2UA/+NXVOm9a/2qygijyl8YONns5BbMKIbQAZ39GXOvzC8lIb6B+jRdb/BbZo
h1/t97fdSz6EsvpLgt2lS5DOu4MZ9zcY6sZhR933zJpDaZ4r0y0+/1oetChnPcIA
QssdXEJtMjAuwPFGV1++dMTWAFJ8KPg78VvOnaUqN9YjkfOQXG+fKLjbM+HmhN3U
5CSxupSIdybgFuYVoZdI/UyjOx7CE3utjjudGWSjvbD4g6DnhQq00PlP10CV/QiS
AFvmUbVkR9n+dFyma8icA3G/NF4di9tjaz0PoVhI8soO9PrX2OUw90hg78OPHcya
HoYHSW6iI2/mEKI3qGnbXl//zbMwqlvE4UAJNaBF6LeGgjkGa7f/V7x1GqlPpaBj
tXOv1i++B3i3nJyfUbmTbtCBvW0jTsypZOEKU3KxjPSxp+7EyxL/VLIkUJaV3p0X
GC2YDQOe0YM399eUq/421yiAluUaQaLREIEd3TkwKS1KSyuq/VgQr9Rm+l6IxNw+
coJY5iqsqHlzDt/xJJgOayYJAafpPbObtq+RjiXePP2L12hyR98euto7XO6Bt0L9
qnv1lub8qymeCUojWiQKJeQTYr6g46cqIVuNx5nie+VV14nflpFXDiiUE9tzwJ3m
cqLGRxHdl+T0rMXRHG7ei+9n2ziPW0syW0UMUgA6NwnXHpFEkzY=
=gQbw
-----END PGP SIGNATURE-----
