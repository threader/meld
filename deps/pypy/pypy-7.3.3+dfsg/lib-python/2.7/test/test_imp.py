import imp
import os
import shutil
import sys
import unittest
from test import test_support

try:
    import thread
except ImportError:
    thread = None

@unittest.skipUnless(thread, 'threading not available')
class LockTests(unittest.TestCase):

    """Very basic test of import lock functions."""

    def verify_lock_state(self, expected):
        self.assertEqual(imp.lock_held(), expected,
                             "expected imp.lock_held() to be %r" % expected)
    def testLock(self):
        LOOPS = 50

        # The import lock may already be held, e.g. if the test suite is run
        # via "import test.autotest".
        lock_held_at_start = imp.lock_held()
        self.verify_lock_state(lock_held_at_start)

        for i in range(LOOPS):
            imp.acquire_lock()
            self.verify_lock_state(True)

        for i in range(LOOPS):
            imp.release_lock()

        # The original state should be restored now.
        self.verify_lock_state(lock_held_at_start)

        if not lock_held_at_start:
            try:
                imp.release_lock()
            except RuntimeError:
                pass
            else:
                self.fail("release_lock() without lock should raise "
                            "RuntimeError")

class ReloadTests(unittest.TestCase):

    """Very basic tests to make sure that imp.reload() operates just like
    reload()."""

    def test_source(self):
        # XXX (ncoghlan): It would be nice to use test_support.CleanImport
        # here, but that breaks because the os module registers some
        # handlers in copy_reg on import. Since CleanImport doesn't
        # revert that registration, the module is left in a broken
        # state after reversion. Reinitialising the module contents
        # and just reverting os.environ to its previous state is an OK
        # workaround
        with test_support.EnvironmentVarGuard():
            import os
            imp.reload(os)

    def test_extension(self):
        with test_support.CleanImport('time'):
            import time
            imp.reload(time)

    def test_builtin(self):
        with test_support.CleanImport('marshal'):
            import marshal
            imp.reload(marshal)


class PEP3147Tests(unittest.TestCase):
    """Tests of PEP 3147."""

    tag = imp.get_tag()

    def test_cache_from_source(self):
        # Given the path to a .py file, return the path to its PEP 3147
        # defined .pyc file (i.e. under __pycache__).
        self.assertEqual(
            imp.cache_from_source('/foo/bar/baz/qux.py', True),
            '/foo/bar/baz/__pycache__/qux.{}.pyc'.format(self.tag))

    def test_cache_from_source_optimized(self):
        # Given the path to a .py file, return the path to its PEP 3147
        # defined .pyo file (i.e. under __pycache__).
        if test_support.check_impl_detail(pypy=True):
            # PyPy doesn't support .pyo, so we expect .pyc
            extension = 'pyc'
        else:
            extension = 'pyo'
        self.assertEqual(
            imp.cache_from_source('/foo/bar/baz/qux.py', False),
            '/foo/bar/baz/__pycache__/qux.{}.{}'.format(self.tag, extension))

    def test_cache_from_source_cwd(self):
        self.assertEqual(imp.cache_from_source('foo.py', True),
                         os.sep.join(('__pycache__',
                                      'foo.{}.pyc'.format(self.tag))))

    def test_cache_from_source_override(self):
        # When debug_override is not None, it can be any true-ish or false-ish
        # value.
        if test_support.check_impl_detail(pypy=True):
            # PyPy doesn't support .pyo, so we expect .pyc
            extension = 'pyc'
        else:
            extension = 'pyo'
        self.assertEqual(
            imp.cache_from_source('/foo/bar/baz.py', []),
            '/foo/bar/__pycache__/baz.{}.pyc'.format(self.tag))
        self.assertEqual(
            imp.cache_from_source('/foo/bar/baz.py', [17]),
            '/foo/bar/__pycache__/baz.{}.{}'.format(self.tag, extension))
        # However if the bool-ishness can't be determined, the exception
        # propagates.
        class Bearish:
            def __bool__(self): raise RuntimeError

        if test_support.check_impl_detail(pypy=True):
            # Pypy doesn't even determine bool-ishness
            try:
                imp.cache_from_source('/foo/bar/baz.py', Bearish())
            except RuntimeError:
                pass
        else:
            self.assertRaises(
                RuntimeError,
                imp.cache_from_source, '/foo/bar/baz.py', Bearish())

    @unittest.skipIf(os.altsep is None,
                     'test meaningful only where os.altsep is defined')
    def test_altsep_cache_from_source(self):
        # Windows path and PEP 3147.
        self.assertEqual(
            imp.cache_from_source('\\foo\\bar\\baz\\qux.py', True),
            '\\foo\\bar\\baz\\__pycache__\\qux.{}.pyc'.format(self.tag))

    @unittest.skipIf(os.altsep is None,
                     'test meaningful only where os.altsep is defined')
    def test_altsep_and_sep_cache_from_source(self):
        # Windows path and PEP 3147 where altsep is right of sep.
        self.assertEqual(
            imp.cache_from_source('\\foo\\bar/baz\\qux.py', True),
            '\\foo\\bar/baz\\__pycache__\\qux.{}.pyc'.format(self.tag))

    @unittest.skipIf(os.altsep is None,
                     'test meaningful only where os.altsep is defined')
    def test_sep_altsep_and_sep_cache_from_source(self):
        # Windows path and PEP 3147 where sep is right of altsep.
        self.assertEqual(
            imp.cache_from_source('\\foo\\bar\\baz/qux.py', True),
            '\\foo\\bar\\baz/__pycache__/qux.{}.pyc'.format(self.tag))

    def test_source_from_cache(self):
        # Given the path to a PEP 3147 defined .pyc file, return the path to
        # its source.  This tests the good path.
        self.assertEqual(imp.source_from_cache(
            '/foo/bar/baz/__pycache__/qux.{}.pyc'.format(self.tag)),
            '/foo/bar/baz/qux.py')

    def test_source_from_cache_bad_path(self):
        # When the path to a pyc file is not in PEP 3147 format, a ValueError
        # is raised.
        self.assertRaises(
            ValueError, imp.source_from_cache, '/foo/bar/bazqux.pyc')

    def test_source_from_cache_no_slash(self):
        # No slashes at all in path -> ValueError
        self.assertRaises(
            ValueError, imp.source_from_cache, 'foo.cpython-32.pyc')

    def test_source_from_cache_too_few_dots(self):
        # Too few dots in final path component -> ValueError
        self.assertRaises(
            ValueError, imp.source_from_cache, '__pycache__/foo.pyc')

    def test_source_from_cache_too_many_dots(self):
        # Too many dots in final path component -> ValueError
        self.assertRaises(
            ValueError, imp.source_from_cache,
            '__pycache__/foo.cpython-32.foo.pyc')

    def test_source_from_cache_no__pycache__(self):
        # Another problem with the path -> ValueError
        self.assertRaises(
            ValueError, imp.source_from_cache,
            '/foo/bar/foo.cpython-32.foo.pyc')

    def test_package___file__(self):
        # Test that a package's __file__ points to the right source directory.
        os.mkdir('pep3147')
        sys.path.insert(0, os.curdir)
        def cleanup():
            if sys.path[0] == os.curdir:
                del sys.path[0]
            shutil.rmtree('pep3147')
        self.addCleanup(cleanup)
        # Touch the __init__.py file.
        with open('pep3147/__init__.py', 'w'):
            pass
        m = __import__('pep3147')
        # Ensure we load the pyc file.
        test_support.forget('pep3147')
        m = __import__('pep3147')
        self.assertEqual(m.__file__,
                         os.sep.join(('.', 'pep3147', '__init__.py')))


def test_main():
    tests = [
        PEP3147Tests,
        ReloadTests,
        LockTests,
    ]
    test_support.run_unittest(*tests)

if __name__ == "__main__":
    test_main()
