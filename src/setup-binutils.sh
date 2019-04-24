export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

rm -rf binutils-2.23
if [ ! -f binutils-2.23.tar.gz ];
then
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/binutils-2.23.tar.gz
fi
tar xvfz binutils-2.23.tar.gz

cd $HOME/Projects/os/src
rm -rf build-binutils
mkdir build-binutils
cd build-binutils
cp -Rv ../toolchain/binutils-2.23 ..
../binutils-2.23/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-werror
make
make install
