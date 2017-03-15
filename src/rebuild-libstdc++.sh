export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

cd build-gcc
#make clean-target-libstdc++-v3
make all-target-libstdc++-v3
make install-target-libstdc++-v3
