Format: 3.0 (quilt)
Source: pycairo
Binary: python3-cairo, python3-cairo-dev, python3-cairo-doc
Architecture: any all
Version: 1.26.1-2
Maintainer: Debian Python Team <team+python@tracker.debian.org>
Uploaders: Torsten Marek <shlomme@debian.org>
Homepage: https://cairographics.org/pycairo/
Standards-Version: 4.6.2
Vcs-Browser: https://salsa.debian.org/python-team/packages/pycairo
Vcs-Git: https://salsa.debian.org/python-team/packages/pycairo.git
Testsuite: autopkgtest
Testsuite-Triggers: python3-pytest
Build-Depends: debhelper-compat (= 13), dh-exec, dh-python, libcairo2-dev (>= 1.18.2), meson, python3-all-dev, python3-pytest <!nocheck>, python3-sphinx, python3-sphinx-rtd-theme, sphinx-common
Package-List:
 python3-cairo deb python optional arch=any
 python3-cairo-dev deb python optional arch=all
 python3-cairo-doc deb doc optional arch=all
Checksums-Sha1:
 c9cf03f1197ea2222828c8f7a996ad4ed7209e98 664191 pycairo_1.26.1.orig.tar.gz
 be90e76d740aba2c94a1bbd53982d2b6903f0289 15640 pycairo_1.26.1-2.debian.tar.xz
Checksums-Sha256:
 771900e37a54c8f109d69cd8faf5e0dd5df8c90b17465e9c436c9f1cef5b4c8f 664191 pycairo_1.26.1.orig.tar.gz
 854f83296a8c4b3a8202607a270867c0f802948d61e77fc4fb8f643fb91dc6c6 15640 pycairo_1.26.1-2.debian.tar.xz
Files:
 d30852b81e7f78955b9e5d451bfab956 664191 pycairo_1.26.1.orig.tar.gz
 16a02ddbff8e56098158b40b341b124c 15640 pycairo_1.26.1-2.debian.tar.xz
