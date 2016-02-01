AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)

noinst_LIBRARIES = lib.a

if MAY_SUPPLY_SYSCALLS
extra_objs = $(lpfx)syscalls.o $(lpfx)crt_support.o
else
extra_objs =
endif

lib_a_SOURCES = dirent.c getenv.c
lib_a_LIBADD = $(extra_objs)
EXTRA_lib_a_SOURCES = syscalls.c crt_support.c crt0.S crtn.S crti.S
lib_a_DEPENDENCIES = $(extra_objs)
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS) -I ../../../../../../include

if MAY_SUPPLY_SYSCALLS
all: crt0.o
endif

ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host
