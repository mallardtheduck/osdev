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

export CFLAGS="-I$PWD/../../user/libs/ansi -I$PWD/../../include -g -O2"
export CPPFLAGS=""
export CXXFLAGS=""

export LDFLAGS="-L$PWD/../../user/libs/ansi -lansi"

PATH=$BASE_PATH/bin:$PATH
DESTDIR=$PWD/../install ac_cv_header_termios_h='no' ./configure \
	--host=$ARCH \
	--prefix=$PREFIX \
	--with-shared \
	--with-cxx-shared

make libs
make install.libs
make install.includes
make install.data
