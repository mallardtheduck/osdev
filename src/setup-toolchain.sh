export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

rm -rf binutils-2.23
if [ ! -f binutils-2.23.tar.gz ];
then
	wget http://ftp.gnu.org/gnu/binutils/binutils-2.23.tar.gz
fi
tar xvfz binutils-2.23.tar.gz

rm -rf gcc-4.8.1
if [ ! -f gcc-4.8.1.tar.bz2 ];
then
	wget http://ftp.gnu.org/gnu/gcc/gcc-4.8.1/gcc-4.8.1.tar.bz2
fi
tar xvfj gcc-4.8.1.tar.bz2

# rm -rf newlib-2.1.0
# if [ ! -f newlib-2.1.0.tar.gz ];
# then
# 	wget ftp://sourceware.org/pub/newlib/newlib-2.1.0.tar.gz
# fi
# tar xvfz newlib-2.1.0.tar.gz

cp -Rv toolchain/binutils-2.23/* ./binutils-2.23  && \
cp -Rv toolchain/gcc-4.8.1/* ./gcc-4.8.1  && \
\
pushd gcc-4.8.1/libstdc++-v3 && \
autoconf2.64 && \
popd && \
\
# pushd newlib-2.1.0/newlib/libc/sys && \
# autoconf && \
# cd btos && \
# autoreconf && \
# popd && \
# \
cd $HOME/Projects/os/src
rm -rf build-binutils
mkdir build-binutils && \
cd build-binutils && \
../binutils-2.23/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-werror && \
make && \
make install && \
\
cd $HOME/Projects/os/src
rm -rf build-gcc
mkdir build-gcc && \
cd build-gcc && \
../gcc-4.8.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --with-newlib --disable-multilib && \
make all-gcc && \
make all-target-libgcc && \
make install-gcc && \
make install-target-libgcc && \
\
cd $HOME/Projects/os/src && \
# pushd newlib-2.1.0/newlib/libc/sys/btos && \
# i686-pc-btos-as crti.S -o crti.o && \
# i686-pc-btos-as crtn.S -o crtn.o && \
# cp crti.o $PREFIX/$TARGET/lib/ && \
# cp crtn.o $PREFIX/$TARGET/lib/ && \
# popd
# rm -rf build-newlib
# mkdir build-newlib && \
# cd build-newlib && \
# ../newlib-2.1.0/configure --target=$TARGET --prefix=$PREFIX && \
# make && \
# make install && \ 
make newlib && \
\
cd $HOME/Projects/os/src/build-gcc && \
mkdir -p i686-pc-btos/libstdc++-v3 && \
cp ../toolchain/misc/libtool i686-pc-btos/libstdc++-v3 && \
make && \
make install
