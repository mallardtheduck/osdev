#!/bin/bash

source ../../env-os.sh

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

export CFLAGS="-I$PWD/../../include -g -O2"
export CPPFLAGS=""
export CXXFLAGS=""

export LDFLAGS=""

PATH=$BASE_PATH/bin:$PATH
DESTDIR=$PWD/../install ./configure \
	--host=$ARCH \
	--prefix=$PREFIX \
	--with-zlib=no \
	--with-bzip2=no \
	--with-png=no \
	--with-harfbuzz=no

make
make DESTDIR=$PWD/../install install

find ../install -name "*.ell" -exec chmod -x {} \;
find ../install -name "*.la" -delete
