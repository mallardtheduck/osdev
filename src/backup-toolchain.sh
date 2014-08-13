find . -name \*.original | sed 's/.original//g' | xargs -I{} cp --parents {} toolchain
find binutils-2.23 -name \*btos\* | xargs -I {} cp --parents {} toolchain
find gcc-4.8.1 -name \*btos\* | xargs -I {} cp --parents {} toolchain
