#!/bin/bash

rm -rf libelf-0.8.9
if [ ! -f libelf-0.8.9.tar.gz ];
then
	wget http://www.mr511.de/software/libelf-0.8.9.tar.gz
fi
tar xf libelf-0.8.9.tar.gz
mkdir -p originals
tar xf libelf-0.8.9.tar.gz -C originals

cd libelf-0.8.9
patch -p1 -R < ../libelf/libelf.patch
cp ../libelf/btos-build.sh .
mkdir -p install
./btos-build.sh
