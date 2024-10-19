-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Format: 3.0 (quilt)
Source: at-spi2-core
Binary: at-spi2-core, at-spi2-common, at-spi2-core-udeb, libatspi2.0-0t64, libatspi0-udeb, libatspi2.0-dev, gir1.2-atspi-2.0, at-spi2-doc, libatk-adaptor, libatk-adaptor-udeb, libatk-bridge2.0-0t64, libatk-bridge-2.0-0-udeb, libatk-bridge2.0-dev, libatk1.0-0t64, libatk1.0-udeb, libatk1.0-dev, libatk1.0-doc, gir1.2-atk-1.0
Architecture: any all
Version: 2.54.0-1
Maintainer: Debian Accessibility Team <pkg-a11y-devel@alioth-lists.debian.net>
Uploaders: Samuel Thibault <sthibault@debian.org>, Jordi Mallach <jordi@debian.org>
Homepage: https://wiki.gnome.org/Accessibility
Standards-Version: 4.6.2
Vcs-Browser: https://salsa.debian.org/a11y-team/at-spi2-core
Vcs-Git: https://salsa.debian.org/a11y-team/at-spi2-core.git
Testsuite: autopkgtest
Testsuite-Triggers: @builddeps@, build-essential, dbus, dbus-daemon, xauth, xvfb
Build-Depends: dpkg-dev (>= 1.22.5), debhelper-compat (= 13), dbus, libdbus-1-dev, dbus-broker [linux-any], libsystemd-dev [linux-any], libglib2.0-dev (>= 2.62), libxml2-dev, libx11-dev, libxtst-dev, meson (>= 0.63.0), pkgconf, gtk-doc-tools, gi-docgen, python3-sphinx, gir1.2-dbus-1.0-dev, gir1.2-glib-2.0-dev, gir1.2-gobject-2.0-dev, gobject-introspection | dh-sequence-gir, xauth <!nocheck>, xvfb <!nocheck>, at-spi2-core <!nocheck>
Build-Depends-Indep: docbook-xml <!nodoc>, libglib2.0-doc <!nodoc>, libglib2.0-dev-bin <!nodoc>
Package-List:
 at-spi2-common deb misc optional arch=all
 at-spi2-core deb misc optional arch=any
 at-spi2-core-udeb udeb debian-installer optional arch=any
 at-spi2-doc deb doc optional arch=all
 gir1.2-atk-1.0 deb introspection optional arch=any
 gir1.2-atspi-2.0 deb introspection optional arch=any
 libatk-adaptor deb misc optional arch=any
 libatk-adaptor-udeb udeb debian-installer optional arch=any
 libatk-bridge-2.0-0-udeb udeb debian-installer optional arch=any
 libatk-bridge2.0-0t64 deb libs optional arch=any
 libatk-bridge2.0-dev deb libdevel optional arch=any
 libatk1.0-0t64 deb libs optional arch=any
 libatk1.0-dev deb libdevel optional arch=any
 libatk1.0-doc deb doc optional arch=all profile=!nodoc
 libatk1.0-udeb udeb debian-installer optional arch=any
 libatspi0-udeb udeb debian-installer optional arch=any
 libatspi2.0-0t64 deb libs optional arch=any
 libatspi2.0-dev deb libdevel optional arch=any
Checksums-Sha1:
 80853857a516b5e533ec82d916f6edd60c618b39 575368 at-spi2-core_2.54.0.orig.tar.xz
 75607b951591f2156c49b19ab2f1a925c4e5e741 20068 at-spi2-core_2.54.0-1.debian.tar.xz
Checksums-Sha256:
 d7eee7e75beddcc272cedc2b60535600f3aae6e481589ebc667afc437c0a6079 575368 at-spi2-core_2.54.0.orig.tar.xz
 0ac0bd122ce3cf26f82f2aed55e155a1af5f1723e521de7f77deca924b37f24f 20068 at-spi2-core_2.54.0-1.debian.tar.xz
Files:
 21a200a6f76673a7178e1669272e8ecf 575368 at-spi2-core_2.54.0.orig.tar.xz
 9a251f4c7634c066a27d965123f4e42d 20068 at-spi2-core_2.54.0-1.debian.tar.xz

-----BEGIN PGP SIGNATURE-----

iQIzBAEBCgAdFiEETQvhLw5HdtiqzpaW5mx3Wuv+bH0FAmboF+gACgkQ5mx3Wuv+
bH1jTA//aHZPBmCA8AqTKQXgeldFr35bQ/EWpsllQIrkPwdwvu1oVJK9tSGNlOqA
qmHqWjS1zfUgK4OeVtkejc4c5tpayz3zZEpRYPWlp4ZyK3n4JUxk739Nda7LJVw8
NQJ5hk4RSij3DsXLLRyWeeX+jMRM8/V5GqJbhDR7J4kspxo9qEeN/TpWhcQfKr6Q
UGcsxb2bPfwy+l1ON4vn0ydOlnkkUEHlmp4r7nm2M0xm1rF/HAJ/r+6nH5A9ljR0
ULb9oEYezjHYcuaIG/v3Xs7RPOdUI+clmRZ9ftVpELmBPGF1y5AL4CRPuOJ48XhB
RTtLcbIyJ1Au1AQ1dm8qb+k36w8w+7Ev8+Kqnu90/GH6j9WSNYfGB5PtU5k+GrTk
1aSiC09QkA4i0DN2Ac7cEV45Fofmw3YbpZFklA8O5RSjS2zVRVWX4Kaayh+S6MNl
7gWmtdOEfhBnBYg4QNGvyVnT3g+bgmX4AeQMITHglvAUpElqppHHhnI+Yij3m084
QXKrZqcCIynSXQ60prbbhLXUuQw7RBYqYQpQvIEiivLVHTZJgJLA9FLie0Vm2ohb
KQd32a161o2HwCASna1x2hd2ioJwRSLQSnWam9skqbqYMyi/JpEsIfZMThJs8c0P
UAGliypMCD32cn5lIuX0VuEmNLTN2jCvJFohD0iO92ook2BLVSY=
=cm2g
-----END PGP SIGNATURE-----
