export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

rm binutils-2.23.tar.gz
rm -rf binutils-2.23
wget http://ftp.gnu.org/gnu/binutils/binutils-2.23.tar.gz
tar xvfz binutils-2.23.tar.gz

cd $HOME/Projects/os/src
rm -rf build-binutils
mkdir build-binutils
cd build-binutils
../binutils-2.23/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-werror
make
make install
