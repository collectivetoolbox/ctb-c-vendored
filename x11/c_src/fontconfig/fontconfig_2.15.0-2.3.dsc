-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Format: 3.0 (quilt)
Source: fontconfig
Binary: fontconfig, fontconfig-config, fontconfig-udeb, libfontconfig-dev, libfontconfig1-dev, libfontconfig1, libfontconfig-doc
Architecture: any all
Version: 2.15.0-2.3
Maintainer: Debian freedesktop.org maintainers <pkg-freedesktop-maintainers@lists.alioth.debian.org>
Uploaders: Keith Packard <keithp@debian.org>, Emilio Pozuelo Monfort <pochu@debian.org>,
Homepage: https://www.freedesktop.org/wiki/Software/fontconfig/
Standards-Version: 4.6.2
Vcs-Browser: https://salsa.debian.org/freedesktop-team/fontconfig
Vcs-Git: https://salsa.debian.org/freedesktop-team/fontconfig.git
Build-Depends: debhelper-compat (= 13), libfreetype-dev (>= 2.8.1), libexpat1-dev, uuid-dev, pkgconf, python3:any, gperf, po-debconf
Build-Depends-Indep: docbook <!nodoc>, docbook-utils <!nodoc>, texlive-formats-extra <!nodoc>
Package-List:
 fontconfig deb fonts optional arch=any
 fontconfig-config deb fonts optional arch=any
 fontconfig-udeb udeb debian-installer optional arch=any profile=!noudeb
 libfontconfig-dev deb libdevel optional arch=any
 libfontconfig-doc deb doc optional arch=all profile=!nodoc
 libfontconfig1 deb libs optional arch=any
 libfontconfig1-dev deb oldlibs optional arch=any
Checksums-Sha1:
 b6137ee5d542c0fe5c96a7724884f2e8e212d275 1447820 fontconfig_2.15.0.orig.tar.xz
 4f1ffd89cebe8528d946bb66fe0584a66f7a6484 59516 fontconfig_2.15.0-2.3.debian.tar.xz
Checksums-Sha256:
 63a0658d0e06e0fa886106452b58ef04f21f58202ea02a94c39de0d3335d7c0e 1447820 fontconfig_2.15.0.orig.tar.xz
 af8e98e3801427f8957f86dc18303fcfbae329c0fab5bc06b5d5a0d26a53295f 59516 fontconfig_2.15.0-2.3.debian.tar.xz
Files:
 5bb3a2829aecb22ae553c39099bd0d6a 1447820 fontconfig_2.15.0.orig.tar.xz
 3252989d2d0163fb9536234364c7a849 59516 fontconfig_2.15.0-2.3.debian.tar.xz

-----BEGIN PGP SIGNATURE-----

iQIzBAEBCgAdFiEEfncpR22H1vEdkazLwpPntGGCWs4FAmfv494ACgkQwpPntGGC
Ws44Pg/+OVUTDlNrU/pKrwLMU7WIOM6M2jaD2CmXoedP24+YWKf8ryKTaDwWrySu
Y9h1dC20IAL5T3JzFJee+5XcALxddNwem//xKPzTnaAUclXsXjCQ0wqLp49Kq3zu
aNqaSxtnaSpnPUMhKVM4KE7JGDBa+SRj8gwR3DdTfkAQO9pROwsW3ozZP7Z1MTB7
xQehdyOfah2N4TkvYsHg4xVmqMjpk9atGcBR2C4UKQN4mG7RgDy7LgqZ0r5tEdVc
sVRzdpSz0hBd8QmQ8JjqdpwoZmzR3W/HmJMgcW6jhBDUZnwf6ihm449jWkA8phxu
3Mhh917jM1KcFUORMVsI24efJKiSMi9yGmH7p6IsMZpNZrw9Nweb1dSQXVe9V0K2
YRvWjBO8JgR0hql9dqC5Vg/slQ9DwypUDM/naCP7IFYxZcOrkzOcxldj/priB8Kh
tk14lHKxRwLUZJ+xQEvCKmjeQsY/MewBz6pznS6a01k1BLjsgV37K9VhfDIlfLkz
pRx06Yb4VB2hFZTLtRtamuh6kIHJEnE9yRjFRWe6rJKKJQHuFutFV6ci83sZ/mqj
+EP738eeyOiSM5Tm2eQAzxxrnUMH64l1BDluwj8beIbrFU7rUbXNTP8x/hfeYBmw
NT5y26wxff8hMfMZxl1DQJ5/y2no7HsAK2HlecT3efgJLbHxSiA=
=PJ53
-----END PGP SIGNATURE-----
