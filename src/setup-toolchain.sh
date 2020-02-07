#!/bin/bash -x
export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

if [ "$1" != "buildonly" ]; 
then

	rm -rf binutils-2.23
	if [ ! -f binutils-2.23.tar.gz ];
	then
		wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/binutils-2.23.tar.gz
	fi
	tar xvfz binutils-2.23.tar.gz
	
	rm -rf gcc-9.2.0
	if [ ! -f gcc-9.2.0.tar.xz ];
	then
		wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/gcc-9.2.0.tar.xz
	fi
	tar xvf gcc-9.2.0.tar.xz
	
	cp -Rv toolchain/binutils-2.23/* ./binutils-2.23  && \
	cd gcc-9.2.0/ &&
	patch -p1 < ../toolchain/gcc-9.2.0/gcc-9.2.0.patch & \
	cd ..
	if [ "$1" == "download" ];  
	then 
		exit
	fi
	
fi

case "$2" in
	stage1)
	run=1
	;;
	
	stage2)
	run=2
	;;
	
	stage3)
	run=3
	;;
	
	stage4)
	run=4
	;;
	
	*)
	run=1234
	;;
esac

case "$run" in
	*1*)

	cd $HOME/Projects/os/src
	rm -rf build-binutils
	mkdir build-binutils && \
	cd build-binutils && \
	../binutils-2.23/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-werror && \
	make && \
	make install && \
	\
	rm -rf "$PREFIX/lib/gcc/i686-pc-btos/9.2.0" && \
	cd $HOME/Projects/os/src && \
	rm -rf build-gcc
	mkdir build-gcc && \
	cd build-gcc && \
	../gcc-9.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --with-newlib --disable-multilib --enable-shared=libgcc,libstdc++ --enable-initfini-array && \
	make all-gcc && \
	make install-gcc && \
	cd $HOME/Projects/os/src
	;;
esac

case "$run" in
	*2*)

	cd build-gcc && \
	make -C ../user/libs/newlib/libc startfiles && \
	make all-target-libgcc && \
	cp i686-pc-btos/libgcc/libgcc.a "$PREFIX/i686-pc-btos/lib" && \
	SHLIB_LINK="i686-pc-btos-gcc -O2 -fPIC -shared @shlib_objs@ -o @shlib_base_name@.ell" make all-target-libgcc && \
	make install-target-libgcc && \
	find i686-pc-btos/libgcc -name \*.ell -exec cp {} ../../cross/i686-pc-btos/lib \;
	cd ..
	;;
esac

case "$run" in
	*3*)
	
	make -C user/libs/newlib/libc copy-includes && \
	make newlib
	;;
esac

case "$run" in
	*4*)
	
	cd build-gcc && \
	cd $HOME/Projects/os/src/build-gcc && \
	mkdir -p i686-pc-btos/libstdc++-v3 && \
	cp ../toolchain/misc/libtool i686-pc-btos/libstdc++-v3 && \
	make
	cp ../toolchain/misc/libtool i686-pc-btos/libstdc++-v3 && \
	make && \
	make install
	;;
esac
