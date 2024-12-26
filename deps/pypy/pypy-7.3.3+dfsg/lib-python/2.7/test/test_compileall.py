import compileall
import imp
import os
import py_compile
import shutil
import struct
import sys
import subprocess
import tempfile
from test import test_support
import unittest


class CompileallTests(unittest.TestCase):

    def setUp(self):
        self.directory = tempfile.mkdtemp()
        self.source_path = os.path.join(self.directory, '_test.py')
        self.bc_path = imp.cache_from_source(self.source_path)
        with open(self.source_path, 'w') as file:
            file.write('x = 123\n')
        self.source_path2 = os.path.join(self.directory, '_test2.py')
        self.bc_path2 = imp.cache_from_source(self.source_path2)
        shutil.copyfile(self.source_path, self.source_path2)

    def tearDown(self):
        shutil.rmtree(self.directory)

    def data(self):
        with open(self.bc_path, 'rb') as file:
            data = file.read(8)
        mtime = int(os.stat(self.source_path).st_mtime)
        compare = struct.pack('<4sl', imp.get_magic(), mtime)
        return data, compare

    @unittest.skipUnless(hasattr(os, 'stat'), 'test needs os.stat()')
    def recreation_check(self, metadata):
        """Check that compileall recreates bytecode when the new metadata is
        used."""
        py_compile.compile(self.source_path)
        self.assertEqual(*self.data())
        with open(self.bc_path, 'rb') as file:
            bc = file.read()[len(metadata):]
        with open(self.bc_path, 'wb') as file:
            file.write(metadata)
            file.write(bc)
        self.assertNotEqual(*self.data())
        compileall.compile_dir(self.directory, force=False, quiet=True)
        self.assertTrue(*self.data())

    def test_mtime(self):
        # Test a change in mtime leads to a new .pyc.
        self.recreation_check(struct.pack('<4sl', imp.get_magic(), 1))

    def test_magic_number(self):
        # Test a change in mtime leads to a new .pyc.
        self.recreation_check(b'\0\0\0\0')

    def test_compile_files(self):
        # Test compiling a single file, and complete directory
        for fn in (self.bc_path, self.bc_path2):
            try:
                os.unlink(fn)
            except:
                pass
        compileall.compile_file(self.source_path, force=False, quiet=True)
        self.assertTrue(os.path.isfile(self.bc_path) \
                        and not os.path.isfile(self.bc_path2))
        os.unlink(self.bc_path)
        compileall.compile_dir(self.directory, force=False, quiet=True)
        self.assertTrue(os.path.isfile(self.bc_path) \
                        and os.path.isfile(self.bc_path2))
        os.unlink(self.bc_path)
        os.unlink(self.bc_path2)

class CommandLineTests(unittest.TestCase):
    """Test some aspects of compileall's CLI."""

    def setUp(self):
        self.addCleanup(self._cleanup)
        self.directory = tempfile.mkdtemp()
        self.pkgdir = os.path.join(self.directory, 'foo')
        os.mkdir(self.pkgdir)
        # Touch the __init__.py and a package module.
        with open(os.path.join(self.pkgdir, '__init__.py'), 'w'):
            pass
        with open(os.path.join(self.pkgdir, 'bar.py'), 'w'):
            pass
        sys.path.insert(0, self.directory)

    def _cleanup(self):
        test_support.rmtree(self.directory)
        assert sys.path[0] == self.directory, 'Missing path'
        del sys.path[0]

    def test_pep3147_paths(self):
        # Ensure that the default behavior of compileall's CLI is to create
        # PEP 3147 pyc/pyo files.
        retcode = subprocess.call(
            (sys.executable, '-m', 'compileall', '-q', self.pkgdir))
        self.assertEqual(retcode, 0)
        # Verify the __pycache__ directory contents.
        cachedir = os.path.join(self.pkgdir, '__pycache__')
        self.assertTrue(os.path.exists(cachedir))
        ext = ('pyc' if __debug__ else 'pyo')
        expected = sorted(base.format(imp.get_tag(), ext) for base in
                          ('__init__.{}.{}', 'bar.{}.{}'))
        self.assertEqual(sorted(os.listdir(cachedir)), expected)
        # Make sure there are no .pyc files in the source directory.
        self.assertFalse([pyc_file for pyc_file in os.listdir(self.pkgdir)
                          if pyc_file.endswith(ext)])

    def test_legacy_paths(self):
        # Ensure that with the proper switch, compileall leaves legacy
        # pyc/pyo files, and no __pycache__ directory.
        retcode = subprocess.call(
            (sys.executable, '-m', 'compileall', '-b', '-q', self.pkgdir))
        self.assertEqual(retcode, 0)
        # Verify the __pycache__ directory contents.
        cachedir = os.path.join(self.pkgdir, '__pycache__')
        self.assertFalse(os.path.exists(cachedir))
        ext = ('pyc' if __debug__ else 'pyo')
        expected = [base.format(ext) for base in ('__init__.{}', 'bar.{}')]
        expected.extend(['__init__.py', 'bar.py'])
        expected.sort()
        self.assertEqual(sorted(os.listdir(self.pkgdir)), expected)


def test_main():
    test_support.run_unittest(CommandLineTests, CompileallTests)


if __name__ == "__main__":
    test_main()
