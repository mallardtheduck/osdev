find . -name \*.original | sed 's/.original//g' | xargs -I{} cp -v --parents {} toolchain
find binutils-2.23 -name \*btos\* | xargs -I {} cp -v --parents {} toolchain
find gcc-4.8.1 -name \*btos\* | xargs -I {} cp -v --parents {} toolchain
find newlib-2.1.0/newlib/libc/sys/btos/ -maxdepth 1 -type f | xargs -I {} cp -v --parents {} toolchain
