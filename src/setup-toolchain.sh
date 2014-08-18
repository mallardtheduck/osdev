export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

rm binutils-2.23.tar.gz
rm -rf binutils-2.23
wget http://ftp.gnu.org/gnu/binutils/binutils-2.23.tar.gz && \
tar xvfz binutils-2.23.tar.gz

rm gcc-4.8.1.tar.bz2
rm -rf gcc-4.8.1
wget http://ftp.gnu.org/gnu/gcc/gcc-4.8.1/gcc-4.8.1.tar.bz2 && \
tar xvfj gcc-4.8.1.tar.bz2

rm newlib-2.1.0.tar.gz
rm -rf newlib-2.1.0
wget ftp://sourceware.org/pub/newlib/newlib-2.1.0.tar.gz && \
tar xvfz newlib-2.1.0.tar.gz

cp -Rv toolchain/* .  && \
\
pushd gcc-4.8.1/libstdc++-v3 && \
autoconf2.64 && \
popd && \
\
pushd newlib-2.1.0/newlib/libc/sys && \
autoconf && \
cd btos && \
autoreconf && \
popd && \
\
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
../gcc-4.8.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers && \
make all-gcc && \
make all-target-libgcc && \
make install-gcc && \
make install-target-libgcc && \
\
cd $HOME/Projects/os/src
rm -rf build-newlib
mkdir build-newlib && \
cd build-newlib && \
../newlib-2.1.0/configure --target=$TARGET --prefix=$PREFIX && \
make && \
make install && \ 
\
cd $HOME/Projects/os/src/build-gcc && \
make && \
make install
