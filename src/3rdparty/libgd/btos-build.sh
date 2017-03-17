#!/bin/bash

# architecture prefix
ARCH="i686-pc-btos"

# cumulative toolchain prefix
PREFIX=/btos

export CC=$ARCH-gcc
export CXX=$ARCH-g++
export LD=$ARCH-ld
export NM="$ARCH-nm -B"
export AR=$ARCH-ar
export RANLIB=$ARCH-ranlib
export STRIP=$ARCH-strip
export OBJCOPY=$ARCH-objcopy
export LN_S="ln -s"

export CFLAGS="-g -O2 -I$PWD/../../include"
export CPPFLAGS=""
export CXXFLAGS=""

export LIBFREETYPE_CFLAGS="-I$PWD/../install/btos/include/freetype2"
export LIBFREETYPE_LIBS="-L$PWD/../install/btos/lib -lfreetype"

export LDFLAGS=""

PATH=$BASE_PATH/bin:$PATH
./configure \
	--host=$ARCH \
	--prefix=$PREFIX \
	--with-png=no \
	--with-jpeg=no \
	--with-freetype=yes \
	--with-fontconfig=no \
	--with-xpm=no

make
make DESTDIR=$PWD/../install install
find ../install -name "*.ell" -exec chmod -x {} \;
find ../install -name "*.la" -delete
find ../install -executable -not -name "*.elx" -type f -exec rm {}.elx \;
find ../install -executable -not -name "*.elx" -type f -exec mv {} {}.elx \;
