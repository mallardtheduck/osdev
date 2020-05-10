#!/bin/bash

rm -rf libelf-0.8.9
if [ ! -f libelf-0.8.9.tar.gz ];
then
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/libelf-0.8.13.tar.gz
fi
tar xf libelf-0.8.13.tar.gz
mkdir -p originals
tar xf libelf-0.8.13.tar.gz -C originals

cd libelf-0.8.13
patch -p1 -R < ../libelf/libelf.patch
cp ../libelf/btos-build.sh .
mkdir -p install
./btos-build.sh
