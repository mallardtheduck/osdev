AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)

extra_objs = $(lpfx)syscalls.lo $(lpfx)crt_support.lo $(lpfx)dirent.lo $(lpfx)getenv.lo $(lpfx)setjmp.lo $(lpfx)signal.lo
extra_srcs = dirent.c getenv.c setjmp.c signal.c syscalls.c crt_support.c crt0.S crtn.S crti.S

if USE_LIBTOOL
noinst_LTLIBRARIES = libbtos.la
libbtos_la_SOURCES = $(extra_srcs)
#libbtos_la_LIBADD = $(extra_objs)
#libbtos_la_DEPENDENCIES = $(extra_objs)
libbtos_la_CCASFLAGS = $(AM_CCASFLAGS)
libbtos_la_CFLAGS = $(AM_CFLAGS) -I ../../../../../../include
LIBC_COMPILE = $(LTCOMPILE)
else
noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(extra_srcs)
#lib_a_LIBADD = $(extra_objs)
#lib_a_DEPENDENCIES = $(extra_objs)
lib_a_CFLAGS = $(AM_CFLAGS) -I ../../../../../../include
LIBC_COMPILE = $(COMPILE)
endif

all-local: crt0.o

ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
