export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

rm gcc-4.8.1.tar.bz2
rm -rf gcc-4.8.1
wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.8.1/gcc-4.8.1.tar.bz2
tar xvfj gcc-4.8.1.tar.bz2

cd $HOME/Projects/os/src
rm -rf build-gcc
mkdir build-gcc
cd build-gcc
../gcc-4.8.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
