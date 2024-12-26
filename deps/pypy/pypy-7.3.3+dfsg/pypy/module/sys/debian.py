import os
import sys

_multiarch = getattr(getattr(sys, 'implementation', sys), '_multiarch', None)
# Support building under the Debian buildsystem, on older releases
if not _multiarch:
    _multiarch = os.environ['DEB_HOST_MULTIARCH']
del os, sys


def get_multiarch_tuple(space):
    return space.wrap(_multiarch)
