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
../gcc-4.8.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --with-newlib --disable-multilib --enable-shared=libgcc,libstdc++ --enable-initfini-array
make all-gcc
SHLIB_LINK="i686-pc-btos-gcc -O2 -fPIC -shared @shlib_objs@ -o @shlib_base_name@.ell" make all-target-libgcc
make install-gcc
make install-target-libgcc
find i686-pc-btos/libgcc -name \*.ell -exec cp {} ../../cross/i686-pc-btos/lib \;
