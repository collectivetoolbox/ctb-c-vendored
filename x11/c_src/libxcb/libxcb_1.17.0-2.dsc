-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA256

Format: 1.0
Source: libxcb
Binary: libxcb1, libxcb1-udeb, libxcb1-dev, libxcb-doc, libxcb-composite0, libxcb-composite0-dev, libxcb-damage0, libxcb-damage0-dev, libxcb-dpms0, libxcb-dpms0-dev, libxcb-glx0, libxcb-glx0-dev, libxcb-randr0, libxcb-randr0-dev, libxcb-record0, libxcb-record0-dev, libxcb-render0, libxcb-render0-dev, libxcb-res0, libxcb-res0-dev, libxcb-screensaver0, libxcb-screensaver0-dev, libxcb-shape0, libxcb-shape0-dev, libxcb-shm0, libxcb-shm0-dev, libxcb-sync1, libxcb-sync-dev, libxcb-xf86dri0, libxcb-xf86dri0-dev, libxcb-xfixes0, libxcb-xfixes0-dev, libxcb-xinerama0, libxcb-xinerama0-dev, libxcb-xinput0, libxcb-xinput-dev, libxcb-xtest0, libxcb-xtest0-dev, libxcb-xv0, libxcb-xv0-dev, libxcb-xvmc0, libxcb-xvmc0-dev, libxcb-dri2-0, libxcb-dri2-0-dev, libxcb-present0, libxcb-present-dev, libxcb-dri3-0, libxcb-dri3-dev, libxcb-xkb1, libxcb-xkb-dev
Architecture: any all
Version: 1.17.0-2
Maintainer: Debian X Strike Force <debian-x@lists.debian.org>
Uploaders:  Julien Cristau <jcristau@debian.org>,
Homepage: https://xcb.freedesktop.org
Standards-Version: 4.6.2
Vcs-Browser: https://salsa.debian.org/xorg-team/lib/libxcb
Vcs-Git: https://salsa.debian.org/xorg-team/lib/libxcb.git
Testsuite: autopkgtest
Testsuite-Triggers: build-essential, pkg-config, xauth, xvfb
Build-Depends: libxau-dev, libxdmcp-dev, xcb-proto (>= 1.15), xcb-proto (<< 2.0), libpthread-stubs0-dev [!linux-any], debhelper-compat (= 13), pkgconf, xutils-dev, xsltproc <!nocheck>, check <!nocheck>, python3-xcbgen (>= 1.14), libtool, automake, python3:native
Build-Depends-Indep: doxygen, graphviz
Package-List:
 libxcb-composite0 deb libs optional arch=any
 libxcb-composite0-dev deb libdevel optional arch=any
 libxcb-damage0 deb libs optional arch=any
 libxcb-damage0-dev deb libdevel optional arch=any
 libxcb-doc deb doc optional arch=all
 libxcb-dpms0 deb libs optional arch=any
 libxcb-dpms0-dev deb libdevel optional arch=any
 libxcb-dri2-0 deb libs optional arch=any
 libxcb-dri2-0-dev deb libdevel optional arch=any
 libxcb-dri3-0 deb libs optional arch=any
 libxcb-dri3-dev deb libdevel optional arch=any
 libxcb-glx0 deb libs optional arch=any
 libxcb-glx0-dev deb libdevel optional arch=any
 libxcb-present-dev deb libdevel optional arch=any
 libxcb-present0 deb libs optional arch=any
 libxcb-randr0 deb libs optional arch=any
 libxcb-randr0-dev deb libdevel optional arch=any
 libxcb-record0 deb libs optional arch=any
 libxcb-record0-dev deb libdevel optional arch=any
 libxcb-render0 deb libs optional arch=any
 libxcb-render0-dev deb libdevel optional arch=any
 libxcb-res0 deb libs optional arch=any
 libxcb-res0-dev deb libdevel optional arch=any
 libxcb-screensaver0 deb libs optional arch=any
 libxcb-screensaver0-dev deb libdevel optional arch=any
 libxcb-shape0 deb libs optional arch=any
 libxcb-shape0-dev deb libdevel optional arch=any
 libxcb-shm0 deb libs optional arch=any
 libxcb-shm0-dev deb libdevel optional arch=any
 libxcb-sync-dev deb libdevel optional arch=any
 libxcb-sync1 deb libs optional arch=any
 libxcb-xf86dri0 deb libs optional arch=any
 libxcb-xf86dri0-dev deb libdevel optional arch=any
 libxcb-xfixes0 deb libs optional arch=any
 libxcb-xfixes0-dev deb libdevel optional arch=any
 libxcb-xinerama0 deb libs optional arch=any
 libxcb-xinerama0-dev deb libdevel optional arch=any
 libxcb-xinput-dev deb libdevel optional arch=any
 libxcb-xinput0 deb libs optional arch=any
 libxcb-xkb-dev deb libdevel optional arch=any
 libxcb-xkb1 deb libs optional arch=any
 libxcb-xtest0 deb libs optional arch=any
 libxcb-xtest0-dev deb libdevel optional arch=any
 libxcb-xv0 deb libs optional arch=any
 libxcb-xv0-dev deb libdevel optional arch=any
 libxcb-xvmc0 deb libs optional arch=any
 libxcb-xvmc0-dev deb libdevel optional arch=any
 libxcb1 deb libs optional arch=any
 libxcb1-dev deb libdevel optional arch=any
 libxcb1-udeb udeb debian-installer optional arch=any profile=!noudeb
Checksums-Sha1:
 220ec81181bcd8bf5a8367610858673e8de6e705 661593 libxcb_1.17.0.orig.tar.gz
 365b0f86925e0bb58f8ea27a6090a12d0278c516 28069 libxcb_1.17.0-2.diff.gz
Checksums-Sha256:
 2c69287424c9e2128cb47ffe92171e10417041ec2963bceafb65cb3fcf8f0b85 661593 libxcb_1.17.0.orig.tar.gz
 c5b33b67a61d0d1c1b624bf88a8150f4be1ba9b46e855e38f03a8f73858af558 28069 libxcb_1.17.0-2.diff.gz
Files:
 186c67e4fdc867dd7372f04b4dfa7c03 661593 libxcb_1.17.0.orig.tar.gz
 ac9e4b4c051a32f274de9a97ed21e212 28069 libxcb_1.17.0-2.diff.gz

-----BEGIN PGP SIGNATURE-----

iQIzBAEBCAAdFiEEcJymx+vmJZxd92Q+nUbEiOQ2gwIFAmZMYYwACgkQnUbEiOQ2
gwJEqw//e9eEcg/ely76NIjaRz3ugFlVhDUD8Ux6L8KaHRFxVLuqoPuj6d9AIMi8
VZDqbJiLqX8jMfzvgGpEkOf5Wk95G+4XV8dS9/qHsvVHpNQs8of1Tk9fk/WFvz2b
l4M8sOubmp3+jLN9TDXiIucFS28TO+/9W8ylZ3UPvZ3k5KSYuhBVJXInXg0bO9ge
Mltw8KuX3C8z8wk1QGpzE5juqwV1YKZKZjHji6qYaZxoCiQzATL5zVoLB3kf3v+g
WE38myEgfORXjvgppgb4U0pTZwZO+K5yOHBx/LCYyvKR5+PNtRmhcBdZYroRBrdv
RzO7OPvIsSmXJXelGYTD8E7LUY7GISFPdDtitU4khUDSLJOsBgH3rX/K7+aOS3Ib
uR//8jcY4ep/9ooiinnP8/30cvcgIET+tUcN8aRLDET1wTpptW5b7Ew/G5AuuLgr
obKJXHFQHLW46IwtOmhyA/izoSK2E/vuyrEWps4BS53glhIL5+5SWW/a8V9H87TG
TlMx+fqXa1RYiFtgdo0qiOamlMXTPnuX3c8uQAq+141Om9e1x52QyPfgR7+jyWBg
PMpMjHkcQRuiMhGPV+qGiOf8Yq7AL0Hxlgp8LMDQr7G2p728Hkmw08iouBr5aMrA
pB9pANjDQZmjBXFYStX8YhQuqtjv6fTlMLnogPrfYv3mabiNaU0=
=lC8D
-----END PGP SIGNATURE-----
