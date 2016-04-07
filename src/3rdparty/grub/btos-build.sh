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

export CFLAGS="-g -O2 -I$HOME/Projects/os/src/include"
export CPPFLAGS="-I$HOME/Projects/os/src/include"
export CXXFLAGS="-I$HOME/Projects/os/src/include"

export LDFLAGS=""

autoconf
PATH=$BASE_PATH/bin:$PATH
./configure \
	--host=$ARCH \
	--prefix=$PREFIX \
	--disable-grub-mkfont

make
make DESTDIR=$PWD/../install install
find ../install -path ../install/btos/lib/grub -prune -o -executable -not -name "*.elx" -type f -exec rm {}.elx \;
find ../install -path ../install/btos/lib/grub -prune -o -executable -not -name "*.elx" -type f -exec mv {} {}.elx \;
