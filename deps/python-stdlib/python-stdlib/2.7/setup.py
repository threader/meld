# Autodetecting setup.py script for building the Python extensions
#

__version__ = "$Revision: 82272 $"

import sys, os, imp, re, optparse
from glob import glob
from platform import machine as platform_machine
import sysconfig

from distutils import log
from distutils import text_file
from distutils.errors import *
from distutils.core import Extension, setup
from distutils.command.build_ext import build_ext
from distutils.command.install import install
from distutils.command.install_lib import install_lib
from distutils.spawn import find_executable

# Were we compiled --with-pydebug or with #define Py_DEBUG?
COMPILED_WITH_PYDEBUG = hasattr(sys, 'gettotalrefcount')

# This global variable is used to hold the list of modules to be disabled.
disabled_module_list = []

def add_dir_to_list(dirlist, dir):
    """Add the directory 'dir' to the list 'dirlist' (at the front) if
    1) 'dir' is not already in 'dirlist'
    2) 'dir' actually exists, and is a directory."""
    if dir is not None and os.path.isdir(dir) and dir not in dirlist:
        dirlist.insert(0, dir)

def find_file(filename, std_dirs, paths):
    """Searches for the directory where a given file is located,
    and returns a possibly-empty list of additional directories, or None
    if the file couldn't be found at all.

    'filename' is the name of a file, such as readline.h or libcrypto.a.
    'std_dirs' is the list of standard system directories; if the
        file is found in one of them, no additional directives are needed.
    'paths' is a list of additional locations to check; if the file is
        found in one of them, the resulting list will contain the directory.
    """
    if sys.platform == 'darwin':
        # Honor the MacOSX SDK setting when one was specified.
        # An SDK is a directory with the same structure as a real
        # system, but with only header files and libraries.
        sysroot = macosx_sdk_root()

    # Check the standard locations
    for dir in std_dirs:
        f = os.path.join(dir, filename)

        if sys.platform == 'darwin' and is_macosx_sdk_path(dir):
            f = os.path.join(sysroot, dir[1:], filename)

        if os.path.exists(f): return []

    # Check the additional directories
    for dir in paths:
        f = os.path.join(dir, filename)

        if sys.platform == 'darwin' and is_macosx_sdk_path(dir):
            f = os.path.join(sysroot, dir[1:], filename)

        if os.path.exists(f):
            return [dir]

    # Not found anywhere
    return None

def find_library_file(compiler, libname, std_dirs, paths):
    result = compiler.find_library_file(std_dirs + paths, libname)
    if result is None:
        return None

    if sys.platform == 'darwin':
        sysroot = macosx_sdk_root()

    # Check whether the found file is in one of the standard directories
    dirname = os.path.dirname(result)
    for p in std_dirs:
        # Ensure path doesn't end with path separator
        p = p.rstrip(os.sep)

        if sys.platform == 'darwin' and is_macosx_sdk_path(p):
            if os.path.join(sysroot, p[1:]) == dirname:
                return [ ]

        if p == dirname:
            return [ ]

    # Otherwise, it must have been in one of the additional directories,
    # so we have to figure out which one.
    for p in paths:
        # Ensure path doesn't end with path separator
        p = p.rstrip(os.sep)

        if sys.platform == 'darwin' and is_macosx_sdk_path(p):
            if os.path.join(sysroot, p[1:]) == dirname:
                return [ p ]

        if p == dirname:
            return [p]
    else:
        assert False, "Internal error: Path not found in std_dirs or paths"

def module_enabled(extlist, modname):
    """Returns whether the module 'modname' is present in the list
    of extensions 'extlist'."""
    extlist = [ext for ext in extlist if ext.name == modname]
    return len(extlist)

def find_module_file(module, dirlist):
    """Find a module in a set of possible folders. If it is not found
    return the unadorned filename"""
    list = find_file(module, [], dirlist)
    if not list:
        return module
    if len(list) > 1:
        log.info("WARNING: multiple copies of %s found"%module)
    return os.path.join(list[0], module)

class PyBuildExt(build_ext):

    def __init__(self, dist):
        build_ext.__init__(self, dist)
        self.failed = []

    def build_extensions(self):

        # Detect which modules should be compiled
        missing = self.detect_modules()

        # Remove modules that are present on the disabled list
        extensions = [ext for ext in self.extensions
                      if ext.name not in disabled_module_list]
        # move ctypes to the end, it depends on other modules
        ext_map = dict((ext.name, i) for i, ext in enumerate(extensions))
        if "_ctypes" in ext_map:
            ctypes = extensions.pop(ext_map["_ctypes"])
            extensions.append(ctypes)
        self.extensions = extensions

        # Fix up the autodetected modules, prefixing all the source files
        # with Modules/ and adding Python's include directory to the path.
        (srcdir,) = sysconfig.get_config_vars('srcdir')
        if not srcdir:
            # Maybe running on Windows but not using CYGWIN?
            raise ValueError("No source directory; cannot proceed.")
        srcdir = os.path.abspath(srcdir)
        moddirlist = [os.path.join(srcdir, 'Modules')]

        # Platform-dependent module source and include directories
        incdirlist = []
        platform = self.get_platform()
        if platform == 'darwin' and ("--disable-toolbox-glue" not in
            sysconfig.get_config_var("CONFIG_ARGS")):
            # Mac OS X also includes some mac-specific modules
            macmoddir = os.path.join(srcdir, 'Mac/Modules')
            moddirlist.append(macmoddir)
            incdirlist.append(os.path.join(srcdir, 'Mac/Include'))

        # Fix up the paths for scripts, too
        self.distribution.scripts = [os.path.join(srcdir, filename)
                                     for filename in self.distribution.scripts]

        # Python header files
        headers = [sysconfig.get_config_h_filename()]
        headers += glob(os.path.join(sysconfig.get_path('platinclude'), "*.h"))
        for ext in self.extensions[:]:
            ext.sources = [ find_module_file(filename, moddirlist)
                            for filename in ext.sources ]
            if ext.depends is not None:
                ext.depends = [find_module_file(filename, moddirlist)
                               for filename in ext.depends]
            else:
                ext.depends = []
            # re-compile extensions if a header file has been changed
            ext.depends.extend(headers)

            # platform specific include directories
            ext.include_dirs.extend(incdirlist)

            # If a module has already been built statically,
            # don't build it here
            if ext.name in sys.builtin_module_names:
                self.extensions.remove(ext)

        # Parse Modules/Setup and Modules/Setup.local to figure out which
        # modules are turned on in the file.
        remove_modules = []
        for filename in ('Modules/Setup', 'Modules/Setup.local'):
            input = text_file.TextFile(filename, join_lines=1)
            while 1:
                line = input.readline()
                if not line: break
                line = line.split()
                remove_modules.append(line[0])
            input.close()

        for ext in self.extensions[:]:
            if ext.name in remove_modules:
                self.extensions.remove(ext)

        # When you run "make CC=altcc" or something similar, you really want
        # those environment variables passed into the setup.py phase.  Here's
        # a small set of useful ones.
        compiler = os.environ.get('CC')
        args = {}
        # unfortunately, distutils doesn't let us provide separate C and C++
        # compilers
        if compiler is not None:
            (ccshared,cflags) = sysconfig.get_config_vars('CCSHARED','CFLAGS')
            args['compiler_so'] = compiler + ' ' + ccshared + ' ' + cflags
        self.compiler.set_executables(**args)

        build_ext.build_extensions(self)

        longest = max([len(e.name) for e in self.extensions])
        if self.failed:
            longest = max(longest, max([len(name) for name in self.failed]))

        def print_three_column(lst):
            lst.sort(key=str.lower)
            # guarantee zip() doesn't drop anything
            while len(lst) % 3:
                lst.append("")
            for e, f, g in zip(lst[::3], lst[1::3], lst[2::3]):
                print "%-*s   %-*s   %-*s" % (longest, e, longest, f,
                                              longest, g)

        if missing:
            print
            print ("Python build finished, but the necessary bits to build "
                   "these modules were not found:")
            print_three_column(missing)
            print ("To find the necessary bits, look in setup.py in"
                   " detect_modules() for the module's name.")
            print

        if self.failed:
            failed = self.failed[:]
            print
            print "Failed to build these modules:"
            print_three_column(failed)
            print

    def build_extension(self, ext):

        if ext.name == '_ctypes':
            if not self.configure_ctypes(ext):
                return

        try:
            build_ext.build_extension(self, ext)
        except (CCompilerError, DistutilsError), why:
            self.announce('WARNING: building of extension "%s" failed: %s' %
                          (ext.name, sys.exc_info()[1]))
            self.failed.append(ext.name)
            return
        # Workaround for Mac OS X: The Carbon-based modules cannot be
        # reliably imported into a command-line Python
        if 'Carbon' in ext.extra_link_args:
            self.announce(
                'WARNING: skipping import check for Carbon-based "%s"' %
                ext.name)
            return

        if self.get_platform() == 'darwin' and (
                sys.maxint > 2**32 and '-arch' in ext.extra_link_args):
            # Don't bother doing an import check when an extension was
            # build with an explicit '-arch' flag on OSX. That's currently
            # only used to build 32-bit only extensions in a 4-way
            # universal build and loading 32-bit code into a 64-bit
            # process will fail.
            self.announce(
                'WARNING: skipping import check for "%s"' %
                ext.name)
            return

        # Workaround for Cygwin: Cygwin currently has fork issues when many
        # modules have been imported
        if self.get_platform() == 'cygwin':
            self.announce('WARNING: skipping import check for Cygwin-based "%s"'
                % ext.name)
            return
        ext_filename = os.path.join(
            self.build_lib,
            self.get_ext_filename(self.get_ext_fullname(ext.name)))
        try:
            imp.load_dynamic(ext.name, ext_filename)
        except ImportError, why:
            self.failed.append(ext.name)
            self.announce('*** WARNING: renaming "%s" since importing it'
                          ' failed: %s' % (ext.name, why), level=3)
            assert not self.inplace
            basename, tail = os.path.splitext(ext_filename)
            newname = basename + "_failed" + tail
            if os.path.exists(newname):
                os.remove(newname)
            os.rename(ext_filename, newname)

            # XXX -- This relies on a Vile HACK in
            # distutils.command.build_ext.build_extension().  The
            # _built_objects attribute is stored there strictly for
            # use here.
            # If there is a failure, _built_objects may not be there,
            # so catch the AttributeError and move on.
            try:
                for filename in self._built_objects:
                    os.remove(filename)
            except AttributeError:
                self.announce('unable to remove files (ignored)')
        except:
            exc_type, why, tb = sys.exc_info()
            self.announce('*** WARNING: importing extension "%s" '
                          'failed with %s: %s' % (ext.name, exc_type, why),
                          level=3)
            self.failed.append(ext.name)

    def get_platform(self):
        # Get value of sys.platform
        for platform in ['cygwin', 'beos', 'darwin', 'atheos', 'osf1']:
            if sys.platform.startswith(platform):
                return platform
        return sys.platform

    def detect_modules(self):
        # Ensure that /usr/local is always used
        # On Debian /usr/local is always used, so we don't include it twice
        #add_dir_to_list(self.compiler.library_dirs, '/usr/local/lib')
        #add_dir_to_list(self.compiler.include_dirs, '/usr/local/include')

        # Add paths specified in the environment variables LDFLAGS and
        # CPPFLAGS for header and library files.
        # We must get the values from the Makefile and not the environment
        # directly since an inconsistently reproducible issue comes up where
        # the environment variable is not set even though the value were passed
        # into configure and stored in the Makefile (issue found on OS X 10.3).
        for env_var, arg_name, dir_list in (
                ('LDFLAGS', '-R', self.compiler.runtime_library_dirs),
                ('LDFLAGS', '-L', self.compiler.library_dirs),
                ('CPPFLAGS', '-I', self.compiler.include_dirs)):
            env_val = sysconfig.get_config_var(env_var)
            if env_val:
                # To prevent optparse from raising an exception about any
                # options in env_val that it doesn't know about we strip out
                # all double dashes and any dashes followed by a character
                # that is not for the option we are dealing with.
                #
                # Please note that order of the regex is important!  We must
                # strip out double-dashes first so that we don't end up with
                # substituting "--Long" to "-Long" and thus lead to "ong" being
                # used for a library directory.
                env_val = re.sub(r'(^|\s+)-(-|(?!%s))' % arg_name[1],
                                 ' ', env_val)
                parser = optparse.OptionParser()
                # Make sure that allowing args interspersed with options is
                # allowed
                parser.allow_interspersed_args = True
                parser.error = lambda msg: None
                parser.add_option(arg_name, dest="dirs", action="append")
                options = parser.parse_args(env_val.split())[0]
                if options.dirs:
                    for directory in reversed(options.dirs):
                        add_dir_to_list(dir_list, directory)

        if os.path.normpath(sys.prefix) != '/usr':
            add_dir_to_list(self.compiler.library_dirs,
                            sysconfig.get_config_var("LIBDIR"))
            add_dir_to_list(self.compiler.include_dirs,
                            sysconfig.get_config_var("INCLUDEDIR"))

        try:
            have_unicode = unicode
        except NameError:
            have_unicode = 0

        # lib_dirs and inc_dirs are used to search for files;
        # if a file is found in one of those directories, it can
        # be assumed that no additional -I,-L directives are needed.
        gnu_triplet = os.popen('dpkg-architecture -qDEB_HOST_MULTIARCH 2>/dev/null || dpkg-architecture -qDEB_HOST_GNU_TYPE').readline()[:-1]
        lib_dirs = self.compiler.library_dirs + [
            os.path.join('/lib', gnu_triplet),
            os.path.join('/usr/lib', gnu_triplet),
            '/lib', '/usr/lib',
            ]
        inc_dirs = self.compiler.include_dirs + ['/usr/include']
        inc_dirs.append(os.path.join('/usr/include', gnu_triplet))
        exts = []
        missing = []

        config_h = sysconfig.get_config_h_filename()
        config_h_vars = sysconfig.parse_config_h(open(config_h))

        platform = self.get_platform()
        srcdir = sysconfig.get_config_var('srcdir')

        # Check for AtheOS which has libraries in non-standard locations
        if platform == 'atheos':
            lib_dirs += ['/system/libs', '/atheos/autolnk/lib']
            lib_dirs += os.getenv('LIBRARY_PATH', '').split(os.pathsep)
            inc_dirs += ['/system/include', '/atheos/autolnk/include']
            inc_dirs += os.getenv('C_INCLUDE_PATH', '').split(os.pathsep)

        # OSF/1 and Unixware have some stuff in /usr/ccs/lib (like -ldb)
        if platform in ['osf1', 'unixware7', 'openunix8']:
            lib_dirs += ['/usr/ccs/lib']

        if platform == 'darwin':
            # This should work on any unixy platform ;-)
            # If the user has bothered specifying additional -I and -L flags
            # in OPT and LDFLAGS we might as well use them here.
            #   NOTE: using shlex.split would technically be more correct, but
            # also gives a bootstrap problem. Let's hope nobody uses directories
            # with whitespace in the name to store libraries.
            cflags, ldflags = sysconfig.get_config_vars(
                    'CFLAGS', 'LDFLAGS')
            for item in cflags.split():
                if item.startswith('-I'):
                    inc_dirs.append(item[2:])

            for item in ldflags.split():
                if item.startswith('-L'):
                    lib_dirs.append(item[2:])

        # Check for MacOS X, which doesn't need libm.a at all
        math_libs = ['m']
        if platform in ['darwin', 'beos']:
            math_libs = []

        # XXX Omitted modules: gl, pure, dl, SGI-specific modules

        #
        # The following modules are all pretty straightforward, and compile
        # on pretty much any POSIXish platform.
        #

        dbm_order = ['gdbm']
        # Anthony Baxter's gdbm module.  GNU dbm(3) will require -lgdbm:
        if ('gdbm' in dbm_order and
            self.compiler.find_library_file(lib_dirs, 'gdbm')):
            exts.append( Extension('gdbm', ['Modules/gdbmmodule.c'],
                                   libraries = ['gdbm'] ) )
        else:
            missing.append('gdbm')

        self.extensions.extend(exts)

        # Call the method for detecting whether _tkinter can be compiled
        self.detect_tkinter(inc_dirs, lib_dirs)

        if '_tkinter' not in [e.name for e in self.extensions]:
            missing.append('_tkinter')

        return missing

    def detect_tkinter_darwin(self, inc_dirs, lib_dirs):
        # The _tkinter module, using frameworks. Since frameworks are quite
        # different the UNIX search logic is not sharable.
        from os.path import join, exists
        framework_dirs = [
            '/Library/Frameworks',
            '/System/Library/Frameworks/',
            join(os.getenv('HOME'), '/Library/Frameworks')
        ]

        sysroot = macosx_sdk_root()

        # Find the directory that contains the Tcl.framework and Tk.framework
        # bundles.
        # XXX distutils should support -F!
        for F in framework_dirs:
            # both Tcl.framework and Tk.framework should be present


            for fw in 'Tcl', 'Tk':
                if is_macosx_sdk_path(F):
                    if not exists(join(sysroot, F[1:], fw + '.framework')):
                        break
                else:
                    if not exists(join(F, fw + '.framework')):
                        break
            else:
                # ok, F is now directory with both frameworks. Continure
                # building
                break
        else:
            # Tk and Tcl frameworks not found. Normal "unix" tkinter search
            # will now resume.
            return 0

        # For 8.4a2, we must add -I options that point inside the Tcl and Tk
        # frameworks. In later release we should hopefully be able to pass
        # the -F option to gcc, which specifies a framework lookup path.
        #
        include_dirs = [
            join(F, fw + '.framework', H)
            for fw in 'Tcl', 'Tk'
            for H in 'Headers', 'Versions/Current/PrivateHeaders'
        ]

        # For 8.4a2, the X11 headers are not included. Rather than include a
        # complicated search, this is a hard-coded path. It could bail out
        # if X11 libs are not found...
        include_dirs.append('/usr/X11R6/include')
        frameworks = ['-framework', 'Tcl', '-framework', 'Tk']

        # All existing framework builds of Tcl/Tk don't support 64-bit
        # architectures.
        cflags = sysconfig.get_config_vars('CFLAGS')[0]
        archs = re.findall('-arch\s+(\w+)', cflags)

        if is_macosx_sdk_path(F):
            fp = os.popen("file %s/Tk.framework/Tk | grep 'for architecture'"%(os.path.join(sysroot, F[1:]),))
        else:
            fp = os.popen("file %s/Tk.framework/Tk | grep 'for architecture'"%(F,))

        detected_archs = []
        for ln in fp:
            a = ln.split()[-1]
            if a in archs:
                detected_archs.append(ln.split()[-1])
        fp.close()

        for a in detected_archs:
            frameworks.append('-arch')
            frameworks.append(a)

        ext = Extension('_tkinter', ['_tkinter.c', 'tkappinit.c'],
                        define_macros=[('WITH_APPINIT', 1)],
                        include_dirs = include_dirs,
                        libraries = [],
                        extra_compile_args = frameworks[2:],
                        extra_link_args = frameworks,
                        )
        self.extensions.append(ext)
        return 1


    def detect_tkinter(self, inc_dirs, lib_dirs):
        # The _tkinter module.

        # Rather than complicate the code below, detecting and building
        # AquaTk is a separate method. Only one Tkinter will be built on
        # Darwin - either AquaTk, if it is found, or X11 based Tk.
        platform = self.get_platform()
        if (platform == 'darwin' and
            self.detect_tkinter_darwin(inc_dirs, lib_dirs)):
            return

        # Assume we haven't found any of the libraries or include files
        # The versions with dots are used on Unix, and the versions without
        # dots on Windows, for detection by cygwin.
        tcllib = tklib = tcl_includes = tk_includes = None
        for version in ['8.6', '86', '8.5', '85', '8.4', '84', '8.3', '83',
                        '8.2', '82', '8.1', '81', '8.0', '80']:
            tklib = self.compiler.find_library_file(lib_dirs,
                                                        'tk' + version)
            tcllib = self.compiler.find_library_file(lib_dirs,
                                                         'tcl' + version)
            if tklib and tcllib:
                # Exit the loop when we've found the Tcl/Tk libraries
                break

        # Now check for the header files
        if tklib and tcllib:
            # Check for the include files on Debian and {Free,Open}BSD, where
            # they're put in /usr/include/{tcl,tk}X.Y
            dotversion = version
            if '.' not in dotversion and "bsd" in sys.platform.lower():
                # OpenBSD and FreeBSD use Tcl/Tk library names like libtcl83.a,
                # but the include subdirs are named like .../include/tcl8.3.
                dotversion = dotversion[:-1] + '.' + dotversion[-1]
            tcl_include_sub = []
            tk_include_sub = []
            for dir in inc_dirs:
                tcl_include_sub += [dir + os.sep + "tcl" + dotversion]
                tk_include_sub += [dir + os.sep + "tk" + dotversion]
            tk_include_sub += tcl_include_sub
            tcl_includes = find_file('tcl.h', inc_dirs, tcl_include_sub)
            tk_includes = find_file('tk.h', inc_dirs, tk_include_sub)

        if (tcllib is None or tklib is None or
            tcl_includes is None or tk_includes is None):
            self.announce("INFO: Can't locate Tcl/Tk libs and/or headers", 2)
            return

        # OK... everything seems to be present for Tcl/Tk.

        include_dirs = [] ; libs = [] ; defs = [] ; added_lib_dirs = []
        for dir in tcl_includes + tk_includes:
            if dir not in include_dirs:
                include_dirs.append(dir)

        # Check for various platform-specific directories
        if platform == 'sunos5':
            include_dirs.append('/usr/openwin/include')
            added_lib_dirs.append('/usr/openwin/lib')
        elif os.path.exists('/usr/X11R6/include'):
            include_dirs.append('/usr/X11R6/include')
            added_lib_dirs.append('/usr/X11R6/lib64')
            added_lib_dirs.append('/usr/X11R6/lib')
        elif os.path.exists('/usr/X11R5/include'):
            include_dirs.append('/usr/X11R5/include')
            added_lib_dirs.append('/usr/X11R5/lib')
        else:
            # Assume default location for X11
            include_dirs.append('/usr/X11/include')
            added_lib_dirs.append('/usr/X11/lib')

        # If Cygwin, then verify that X is installed before proceeding
        if platform == 'cygwin':
            x11_inc = find_file('X11/Xlib.h', [], include_dirs)
            if x11_inc is None:
                return

        # Check for BLT extension
        if self.compiler.find_library_file(lib_dirs + added_lib_dirs,
                                               'BLT8.0'):
            defs.append( ('WITH_BLT', 1) )
            libs.append('BLT8.0')
        elif self.compiler.find_library_file(lib_dirs + added_lib_dirs,
                                                'BLT85'):
            defs.append( ('WITH_BLT', 1) )
            libs.append('BLT85')
        elif self.compiler.find_library_file(lib_dirs + added_lib_dirs,
                                                'BLT86'):
            defs.append( ('WITH_BLT', 1) )
            libs.append('BLT86')
        elif self.compiler.find_library_file(lib_dirs + added_lib_dirs,
                                                'BLT'):
            defs.append( ('WITH_BLT', 1) )
            libs.append('BLT')

        # Add the Tcl/Tk libraries
        libs.append('tk'+ version)
        libs.append('tcl'+ version)

        if platform in ['aix3', 'aix4']:
            libs.append('ld')

        # Finally, link with the X11 libraries (not appropriate on cygwin)
        if platform != "cygwin":
            libs.append('X11')

        ext = Extension('_tkinter', ['Modules/_tkinter.c', 'Modules/tkappinit.c'],
                        define_macros=[('WITH_APPINIT', 1)] + defs,
                        include_dirs = include_dirs,
                        libraries = libs,
                        library_dirs = added_lib_dirs,
                        )
        self.extensions.append(ext)

##         # Uncomment these lines if you want to play with xxmodule.c
##         ext = Extension('xx', ['xxmodule.c'])
##         self.extensions.append(ext)

        # XXX handle these, but how to detect?
        # *** Uncomment and edit for PIL (TkImaging) extension only:
        #       -DWITH_PIL -I../Extensions/Imaging/libImaging  tkImaging.c \
        # *** Uncomment and edit for TOGL extension only:
        #       -DWITH_TOGL togl.c \
        # *** Uncomment these for TOGL extension only:
        #       -lGL -lGLU -lXext -lXmu \

    def configure_ctypes_darwin(self, ext):
        # Darwin (OS X) uses preconfigured files, in
        # the Modules/_ctypes/libffi_osx directory.
        srcdir = sysconfig.get_config_var('srcdir')
        ffi_srcdir = os.path.abspath(os.path.join(srcdir, 'Modules',
                                                  '_ctypes', 'libffi_osx'))
        sources = [os.path.join(ffi_srcdir, p)
                   for p in ['ffi.c',
                             'x86/darwin64.S',
                             'x86/x86-darwin.S',
                             'x86/x86-ffi_darwin.c',
                             'x86/x86-ffi64.c',
                             'powerpc/ppc-darwin.S',
                             'powerpc/ppc-darwin_closure.S',
                             'powerpc/ppc-ffi_darwin.c',
                             'powerpc/ppc64-darwin_closure.S',
                             ]]

        # Add .S (preprocessed assembly) to C compiler source extensions.
        self.compiler.src_extensions.append('.S')

        include_dirs = [os.path.join(ffi_srcdir, 'include'),
                        os.path.join(ffi_srcdir, 'powerpc')]
        ext.include_dirs.extend(include_dirs)
        ext.sources.extend(sources)
        return True

    def configure_ctypes(self, ext):
        if not self.use_system_libffi:
            if sys.platform == 'darwin':
                return self.configure_ctypes_darwin(ext)

            srcdir = sysconfig.get_config_var('srcdir')
            ffi_builddir = os.path.join(self.build_temp, 'libffi')
            ffi_srcdir = os.path.abspath(os.path.join(srcdir, 'Modules',
                                         '_ctypes', 'libffi'))
            ffi_configfile = os.path.join(ffi_builddir, 'fficonfig.py')

            from distutils.dep_util import newer_group

            config_sources = [os.path.join(ffi_srcdir, fname)
                              for fname in os.listdir(ffi_srcdir)
                              if os.path.isfile(os.path.join(ffi_srcdir, fname))]
            if self.force or newer_group(config_sources,
                                         ffi_configfile):
                from distutils.dir_util import mkpath
                mkpath(ffi_builddir)
                config_args = []

                # Pass empty CFLAGS because we'll just append the resulting
                # CFLAGS to Python's; -g or -O2 is to be avoided.
                cmd = "cd %s && env CFLAGS='' '%s/configure' %s" \
                      % (ffi_builddir, ffi_srcdir, " ".join(config_args))

                res = os.system(cmd)
                if res or not os.path.exists(ffi_configfile):
                    print "Failed to configure _ctypes module"
                    return False

            fficonfig = {}
            with open(ffi_configfile) as f:
                exec f in fficonfig

            # Add .S (preprocessed assembly) to C compiler source extensions.
            self.compiler.src_extensions.append('.S')

            include_dirs = [os.path.join(ffi_builddir, 'include'),
                            ffi_builddir,
                            os.path.join(ffi_srcdir, 'src')]
            extra_compile_args = fficonfig['ffi_cflags'].split()

            ext.sources.extend(os.path.join(ffi_srcdir, f) for f in
                               fficonfig['ffi_sources'])
            ext.include_dirs.extend(include_dirs)
            ext.extra_compile_args.extend(extra_compile_args)
        return True

    def detect_ctypes(self, inc_dirs, lib_dirs):
        self.use_system_libffi = False
        include_dirs = []
        extra_compile_args = []
        extra_link_args = []
        sources = ['_ctypes/_ctypes.c',
                   '_ctypes/callbacks.c',
                   '_ctypes/callproc.c',
                   '_ctypes/stgdict.c',
                   '_ctypes/cfield.c',
                   '_ctypes/malloc_closure.c']
        depends = ['_ctypes/ctypes.h']

        if sys.platform == 'darwin':
            sources.append('_ctypes/darwin/dlfcn_simple.c')
            extra_compile_args.append('-DMACOSX')
            include_dirs.append('_ctypes/darwin')
# XXX Is this still needed?
##            extra_link_args.extend(['-read_only_relocs', 'warning'])

        elif sys.platform == 'sunos5':
            # XXX This shouldn't be necessary; it appears that some
            # of the assembler code is non-PIC (i.e. it has relocations
            # when it shouldn't. The proper fix would be to rewrite
            # the assembler code to be PIC.
            # This only works with GCC; the Sun compiler likely refuses
            # this option. If you want to compile ctypes with the Sun
            # compiler, please research a proper solution, instead of
            # finding some -z option for the Sun compiler.
            extra_link_args.append('-mimpure-text')

        elif sys.platform.startswith('hp-ux'):
            extra_link_args.append('-fPIC')

        ext = Extension('_ctypes',
                        include_dirs=include_dirs,
                        extra_compile_args=extra_compile_args,
                        extra_link_args=extra_link_args,
                        libraries=[],
                        sources=sources,
                        depends=depends)
        ext_test = Extension('_ctypes_test',
                             sources=['_ctypes/_ctypes_test.c'])
        self.extensions.extend([ext, ext_test])

        if not '--with-system-ffi' in sysconfig.get_config_var("CONFIG_ARGS"):
            return

        if sys.platform == 'darwin':
            # OS X 10.5 comes with libffi.dylib; the include files are
            # in /usr/include/ffi
            inc_dirs.append('/usr/include/ffi')

        ffi_inc = [sysconfig.get_config_var("LIBFFI_INCLUDEDIR")]
        if not ffi_inc or ffi_inc[0] == '':
            ffi_inc = find_file('ffi.h', [], inc_dirs)
        if ffi_inc is not None:
            ffi_h = ffi_inc[0] + '/ffi.h'
            fp = open(ffi_h)
            while 1:
                line = fp.readline()
                if not line:
                    ffi_inc = None
                    break
                if line.startswith('#define LIBFFI_H'):
                    break
        ffi_lib = None
        if ffi_inc is not None:
            for lib_name in ('ffi_convenience', 'ffi_pic', 'ffi'):
                if (self.compiler.find_library_file(lib_dirs, lib_name)):
                    ffi_lib = lib_name
                    break

        if ffi_inc and ffi_lib:
            ext.include_dirs.extend(ffi_inc)
            ext.libraries.append(ffi_lib)
            self.use_system_libffi = True


class PyBuildInstall(install):
    # Suppress the warning about installation into the lib_dynload
    # directory, which is not in sys.path when running Python during
    # installation:
    def initialize_options (self):
        install.initialize_options(self)
        self.warn_dir=0

class PyBuildInstallLib(install_lib):
    # Do exactly what install_lib does but make sure correct access modes get
    # set on installed directories and files. All installed files with get
    # mode 644 unless they are a shared library in which case they will get
    # mode 755. All installed directories will get mode 755.

    so_ext = sysconfig.get_config_var("SO")

    def install(self):
        outfiles = install_lib.install(self)
        self.set_file_modes(outfiles, 0644, 0755)
        self.set_dir_modes(self.install_dir, 0755)
        return outfiles

    def set_file_modes(self, files, defaultMode, sharedLibMode):
        if not self.is_chmod_supported(): return
        if not files: return

        for filename in files:
            if os.path.islink(filename): continue
            mode = defaultMode
            if filename.endswith(self.so_ext): mode = sharedLibMode
            log.info("changing mode of %s to %o", filename, mode)
            if not self.dry_run: os.chmod(filename, mode)

    def set_dir_modes(self, dirname, mode):
        if not self.is_chmod_supported(): return
        os.path.walk(dirname, self.set_dir_modes_visitor, mode)

    def set_dir_modes_visitor(self, mode, dirname, names):
        if os.path.islink(dirname): return
        log.info("changing mode of %s to %o", dirname, mode)
        if not self.dry_run: os.chmod(dirname, mode)

    def is_chmod_supported(self):
        return hasattr(os, 'chmod')

SUMMARY = """
Python is an interpreted, interactive, object-oriented programming
language. It is often compared to Tcl, Perl, Scheme or Java.

Python combines remarkable power with very clear syntax. It has
modules, classes, exceptions, very high level dynamic data types, and
dynamic typing. There are interfaces to many system calls and
libraries, as well as to various windowing systems (X11, Motif, Tk,
Mac, MFC). New built-in modules are easily written in C or C++. Python
is also usable as an extension language for applications that need a
programmable interface.

The Python implementation is portable: it runs on many brands of UNIX,
on Windows, DOS, OS/2, Mac, Amiga... If your favorite system isn't
listed here, it may still be supported, if there's a C compiler for
it. Ask around on comp.lang.python -- or just try compiling Python
yourself.
"""

CLASSIFIERS = """
Development Status :: 6 - Mature
License :: OSI Approved :: Python Software Foundation License
Natural Language :: English
Programming Language :: C
Programming Language :: Python
Topic :: Software Development
"""

def main():
    # turn off warnings when deprecated modules are imported
    import warnings
    warnings.filterwarnings("ignore",category=DeprecationWarning)
    setup(# PyPI Metadata (PEP 301)
          name = "Python",
          version = sys.version.split()[0],
          url = "http://www.python.org/%s" % sys.version[:3],
          maintainer = "Guido van Rossum and the Python community",
          maintainer_email = "python-dev@python.org",
          description = "A high-level object-oriented programming language",
          long_description = SUMMARY.strip(),
          license = "PSF license",
          classifiers = filter(None, CLASSIFIERS.split("\n")),
          platforms = ["Many"],

          # Build info
          cmdclass = {'build_ext':PyBuildExt, 'install':PyBuildInstall,
                      'install_lib':PyBuildInstallLib},
          # The struct module is defined here, because build_ext won't be
          # called unless there's at least one extension module defined.
          ext_modules=[Extension('_struct', ['_struct.c'])],

          # Scripts to install
          scripts = []
        )

# --install-platlib
if __name__ == '__main__':
    main()
