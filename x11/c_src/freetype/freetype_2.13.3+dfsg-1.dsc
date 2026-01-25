-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Format: 3.0 (quilt)
Source: freetype
Binary: libfreetype6, libfreetype-dev, freetype2-demos, freetype2-doc, libfreetype6-udeb
Architecture: any all
Version: 2.13.3+dfsg-1
Maintainer: Hugh McMaster <hmc@debian.org>
Uploaders: Anthony Fok <foka@debian.org>, Keith Packard <keithp@keithp.com>
Homepage: https://freetype.org
Standards-Version: 4.7.0
Vcs-Browser: https://salsa.debian.org/debian/freetype
Vcs-Git: https://salsa.debian.org/debian/freetype.git
Testsuite: autopkgtest
Testsuite-Triggers: build-essential, pkgconf
Build-Depends: debhelper-compat (= 13), autoconf, bzip2, gettext, libbrotli-dev, libbz2-dev, libpng-dev, libtool, libx11-dev <!pkg.freetype.nodemos>, pkgconf, x11proto-core-dev <!pkg.freetype.nodemos>, zlib1g-dev | libz-dev
Package-List:
 freetype2-demos deb utils optional arch=any profile=!pkg.freetype.nodemos
 freetype2-doc deb doc optional arch=all
 libfreetype-dev deb libdevel optional arch=any
 libfreetype6 deb libs optional arch=any
 libfreetype6-udeb udeb debian-installer optional arch=any profile=!noudeb
Checksums-Sha1:
 13772801af6b9341a20300ed89f36157f2506376 342404 freetype_2.13.3+dfsg.orig-ft2demos.tar.xz
 23ef17897819135ac8f6f99f57702ae7cd24c9a4 833 freetype_2.13.3+dfsg.orig-ft2demos.tar.xz.asc
 7e1c8bc2bba9425864c861438fce76db76fe33c2 2173852 freetype_2.13.3+dfsg.orig-ft2docs.tar.xz
 75a45eb7bd6ee570366654ecb14327f7e948e6ce 833 freetype_2.13.3+dfsg.orig-ft2docs.tar.xz.asc
 66e7e402e4f262f2dbb7577734717c98cfbeb59c 2201416 freetype_2.13.3+dfsg.orig.tar.xz
 aecd6530d68f0c7317232465e6e4931135e91b7f 43904 freetype_2.13.3+dfsg-1.debian.tar.xz
Checksums-Sha256:
 8775e5ffded1a885ba2ccb3ea0e82c73306a03b764080c3e4c79da15b5c9a28a 342404 freetype_2.13.3+dfsg.orig-ft2demos.tar.xz
 931bfa17e59c0ec7db391160f43977e0907f36ea3c39d7e6063731cd4612dd51 833 freetype_2.13.3+dfsg.orig-ft2demos.tar.xz.asc
 b7b66149bea769e226fd3d6d1eee6160e5b6beb4249b088071434fbe85fd1070 2173852 freetype_2.13.3+dfsg.orig-ft2docs.tar.xz
 65c66aec6244d247540430b21d3e80b677f1361906347a5be7fad371d46655da 833 freetype_2.13.3+dfsg.orig-ft2docs.tar.xz.asc
 686ec73cbf6783b245dd068a09ce807b729ac0f8a46dd70f7867923c32fdf4de 2201416 freetype_2.13.3+dfsg.orig.tar.xz
 e2de836c8bb52c5a59173465bfddbf476a277f3f065ba322d111c5046ef8b8c8 43904 freetype_2.13.3+dfsg-1.debian.tar.xz
Files:
 0e4e6017813b7d134a1029d336dbc38a 342404 freetype_2.13.3+dfsg.orig-ft2demos.tar.xz
 38aeeebd44429eda1da9ad6b21604572 833 freetype_2.13.3+dfsg.orig-ft2demos.tar.xz.asc
 6affe0d431939398cc3c7cdd58d824f8 2173852 freetype_2.13.3+dfsg.orig-ft2docs.tar.xz
 5b769f78b7daa734e94f2bb533ad662b 833 freetype_2.13.3+dfsg.orig-ft2docs.tar.xz.asc
 21d424a215ee12f59f133c218f5d456f 2201416 freetype_2.13.3+dfsg.orig.tar.xz
 acecf79a87998ecfc1ac0036e41c9d12 43904 freetype_2.13.3+dfsg-1.debian.tar.xz

-----BEGIN PGP SIGNATURE-----

iQJDBAEBCgAtFiEEOiCBPKV5RoaMUVIRWsYQdMXoG8QFAmbZotoPHGhtY0BkZWJp
YW4ub3JnAAoJEFrGEHTF6BvEOvAP/0JggH6b+Woh3U2oQpzZ0B/6pif9KEOGIOE3
xaI8IV/jhBEkHEh++oJ2xM1g5UpxoYe3AAmm73FeHqKnbvtXIsZ5NSN29Q2JfXBl
fA0Fan8V7pmkcWhsz4tYIKa3K8j/2FMKjDGJGj7JhHkslFqZCVhKwxCC663qH/HD
uWvULIjpzDQiDAaKBHnl5h8aEnTYjpRKqmSQahS+jCmCcPfd5BehcKM+TRYVN1Q2
ceQwsGlY4Q07Hch0s84oDkO6RmEJij4ruVti3r+SF1qhQPk9BqPo83trVrWsXMJg
0/sckq3IjTJ79qG8v3YeO0dP3WoogmVJM/UtaMNk6W8qIgNWGwJhhXDzVW/LBcee
KnpolCtiBhnGVPkFMe85yXL7UCN1aw95YWv4OWGCHa2cs3RInbCJBnZJex3DqA/W
vDFEPcSjs6Lftv2w028NqQCXVZeQgJarM855CHxACCy7CFXG/Y2P9sBCyz8h0e7L
okq5YRTjJnBbYTtwwsYpCUj+h+C+bzPkUbyxlx9oA0EZ7h5ttHptIaZp5cwa2L5P
OwQfGdcXxvreLZTpajEihOIH6vLBVbTiOlR/CJhXxW1QAa9vH5nlEZghf3RsLbvf
VrQxlA+KUWot+jr41Vvo6RfyRum6DpffYUAYAdLFm1lpNz2RF4EFo6RtexvXWrjF
MmwwTCy0
=7ghr
-----END PGP SIGNATURE-----
