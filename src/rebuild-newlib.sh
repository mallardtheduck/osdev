export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

cp -Rv toolchain/newlib-2.1.0 .  && \
\
pushd newlib-2.1.0/newlib/libc/sys && \
autoconf && \
cd btos && \
autoreconf && \
popd && \
\
cd $HOME/Projects/os/src && \
cd build-newlib && \
../newlib-2.1.0/configure --target=$TARGET --prefix=$PREFIX && \
make && \
make install
