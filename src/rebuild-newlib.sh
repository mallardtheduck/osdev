source ./env-os.sh
make newlib

# export PREFIX="$HOME/Projects/os/cross"
# export TOOLS="$HOME/Projects/os/tools"
# export TARGET=i686-pc-btos
# export PATH="$PREFIX/bin:$TOOLS/bin:$PATH"
# export LD="$TARGET-ld"

# cp -Rv toolchain/newlib-2.1.0 .  && \
# pushd newlib-2.1.0/newlib/libc/sys && \
# cd btos && \
# autoreconf && \
# i686-pc-btos-as crti.S -o crti.o && \
# i686-pc-btos-as crtn.S -o crtn.o && \
# cp crti.o $PREFIX/$TARGET/lib/ && \
# cp crtn.o $PREFIX/$TARGET/lib/ && \
# cd ../../.. && \
# find . -name configure -exec bash -c "(cd \$(dirname {}) && autoconf)" \; && \
# \
# cd ../libgloss && \
# find . -name configure -exec bash -c "(cd \$(dirname {}) && autoconf)" \; && \
# \
# popd && \
# \
# cd $HOME/Projects/os/src && \
# cd build-newlib && \
# ../newlib-2.1.0/configure --enable-shared --enable-newlib-io-long-long --target=$TARGET --prefix=$PREFIX  && \
# make
# find . -name libtool -exec cp -v $TOOLS/bin/$TARGET-libtool {} \; && \
# make && \
# make install
