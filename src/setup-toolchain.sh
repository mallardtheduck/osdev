export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

rm binutils-2.23.tar.gz
rm -rf binutils-2.23
wget http://ftp.gnu.org/gnu/binutils/binutils-2.23.tar.gz
tar xvfz binutils-2.23.tar.gz

rm gcc-4.8.1.tar.bz2
rm -rf gcc-4.8.1
wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.8.1/gcc-4.8.1.tar.bz2
tar xvfj gcc-4.8.1.tar.bz2

cp -Rv toolchain/* .

cd $HOME/Projects/os/src
rm -rf build-binutils
mkdir build-binutils
cd build-binutils
../binutils-2.23/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-werror
make
make install

cd $HOME/Projects/os/src
rm -rf build-gcc
mkdir build-gcc
cd build-gcc
../gcc-4.8.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc

