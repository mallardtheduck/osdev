cd build-gcc
find . -name libstdc++.la -exec rm {} \;
make
make install
