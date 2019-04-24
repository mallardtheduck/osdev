#!/bin/bash

rm -rf libuuid-1.0.3
if [ ! -f libuuid-1.0.3.tar.gz ];
then
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/libuuid-1.0.3.tar.gz
fi
tar xf libuuid-1.0.3.tar.gz
mkdir -p originals
tar xf libuuid-1.0.3.tar.gz -C originals

cd libuuid-1.0.3
patch -p1 -R < ../libuuid/libuuid.patch
cp ../libuuid/btos-build.sh .
mkdir -p install
./btos-build.sh
