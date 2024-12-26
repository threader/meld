-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Format: 3.0 (quilt)
Source: pypy
Binary: pypy, pypy-tk, pypy-lib, pypy-lib-testsuite, pypy-doc, pypy-dev
Architecture: any all
Version: 7.3.3+dfsg-2
Maintainer: Stefano Rivera <stefanor@debian.org>
Homepage: https://www.pypy.org/
Standards-Version: 4.5.0
Vcs-Browser: https://salsa.debian.org/debian/pypy
Vcs-Git: https://salsa.debian.org/debian/pypy.git
Testsuite: autopkgtest
Testsuite-Triggers: build-essential, pypy-setuptools, shunit2, virtualenv
Build-Depends: debhelper (>= 9.20141010~), dh-exec, dpkg-dev (>= 1.17.14~), libbz2-dev, libexpat1-dev, libffi-dev, libgdbm-dev, libncurses-dev, libsqlite3-dev, libssl-dev, netbase, pkg-config, procps, pypy [any-amd64 any-i386 arm64 armhf ppc64 ppc64el s390x] <!stage1>, python-pycparser, python2, python2.7-dev, python3-sphinx (>= 1.0.7+dfsg), tcl-dev, tk-dev, valgrind [amd64 arm64 armhf i386 mips mips64el mipsel powerpc ppc64 ppc64el s390x], zlib1g-dev
Build-Depends-Indep: graphviz
Package-List:
 pypy deb python optional arch=any
 pypy-dev deb python optional arch=all
 pypy-doc deb doc optional arch=all
 pypy-lib deb python optional arch=any
 pypy-lib-testsuite deb python optional arch=all
 pypy-tk deb python optional arch=any
Checksums-Sha1:
 5670f82a826c1d8dfe16bf5944be3a03559212b1 13342204 pypy_7.3.3+dfsg.orig.tar.xz
 6473e3a7bac3e52aed2582abd690a6419f0a9fa3 77788 pypy_7.3.3+dfsg-2.debian.tar.xz
Checksums-Sha256:
 25fa3e419f4eee2d59bcb0308e4f4ffd7f520e2a576f85909355a969e02cc00c 13342204 pypy_7.3.3+dfsg.orig.tar.xz
 0dcd6ab186a5eb6dc6c3780d808a6a8fbf2b084f105cd8c4dae2984f4481fc3e 77788 pypy_7.3.3+dfsg-2.debian.tar.xz
Files:
 b1f0670bf7af7a2d379a5a5fd261505c 13342204 pypy_7.3.3+dfsg.orig.tar.xz
 1ffa055bc57e3e8ebe93ab29f163a919 77788 pypy_7.3.3+dfsg-2.debian.tar.xz

-----BEGIN PGP SIGNATURE-----

iHUEARYKAB0WIQTumtb5BSD6EfafSCRHew2wJjpU2AUCYI67AwAKCRBHew2wJjpU
2PScAQDPe6N5jFd7xXBH7K8D3xpbDUBje2ZY0WwtyKXCFyin8wEAo/jr+buGm0cw
7KJgFL5KWdC9yYU137P3tcS+dArm1gU=
=psla
-----END PGP SIGNATURE-----
