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

export CFLAGS="-g -O2 -I$HOME/Projects/os/src/3rdparty/install/btos/include -I$HOME/Projects/os/src/include"
export CPPFLAGS=""
export CXXFLAGS=""

export LDFLAGS="-L$HOME/Projects/os/src/3rdparty/install/btos/lib -liconv"

cp configure configure.bak
autoconf
PATH=$BASE_PATH/bin:$PATH
./configure \
	--host=$ARCH \
	--prefix=$PREFIX \
	--disable-dynamic-loading \
	--disable-device-mapper \
	--without-readline

make
cp configure.bak configure
./configure \
	--host=$ARCH \
	--prefix=$PREFIX \
	--disable-dynamic-loading \
	--disable-device-mapper \
	--without-readline
find . -name "*.o" -delete
find . -name "*.lo" -delete
make

make DESTDIR=$PWD/../install install
find ../install -name "*.ell" -exec chmod -x {} \;
find ../install -executable -not -name "*.elx" -type f -exec rm {}.elx \;
find ../install -executable -not -name "*.elx" -type f -exec mv {} {}.elx \;
