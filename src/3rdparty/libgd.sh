#!/bin/bash

rm -rf libgd-2.1.0
if [ ! -f libgd-2.1.0.tar.gz ];
then
	wget https://bitbucket.org/libgd/gd-libgd/downloads/libgd-2.1.0.tar.gz
fi
tar xf libgd-2.1.0.tar.gz
mkdir -p originals
tar xf libgd-2.1.0.tar.gz -C originals

cd libgd-2.1.0
patch -p1 -R < ../libgd/libgd.patch
cp ../libgd/btos-build.sh .
mkdir -p install
./btos-build.sh
