export PREFIX="$HOME/Projects/os/cross"
export TARGET=i686-pc-btos
export PATH="$PREFIX/bin:$PATH"

cp -Rv toolchain/newlib-2.1.0 .  && \
\
pushd newlib-2.1.0/newlib/libc/sys && \
autoconf && \
cd btos && \
autoreconf && \
i686-pc-btos-as crti.S -o crti.o && \
i686-pc-btos-as crtn.S -o crtn.o && \
cp crti.o $PREFIX/$TARGET/lib/ && \
cp crtn.o $PREFIX/$TARGET/lib/ && \

popd && \
\
cd $HOME/Projects/os/src && \
cd build-newlib && \
../newlib-2.1.0/configure --enable-newlib-io-long-long --target=$TARGET --prefix=$PREFIX && \
make && \
make install
