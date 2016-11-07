export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

rm -rf gcc-4.8.1
if [ ! -f gcc-4.8.1.tar.bz2 ];
then
	wget ftp://ftp.gnu.org/gnu/gcc/gcc-4.8.1/gcc-4.8.1.tar.bz2
fi
tar xvfj gcc-4.8.1.tar.bz2

cd $HOME/Projects/os/src
rm -rf build-gcc
mkdir build-gcc
cd build-gcc
cp -Rv ../toolchain/gcc-4.8.1 ..
../gcc-4.8.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
