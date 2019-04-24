#!/bin/bash

rm -rf grub-2.00
if [ ! -f udis86-1.7.2.tar.gz ];
then
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/udis86-1.7.2.tar.gz
fi
tar xf udis86-1.7.2.tar.gz
mkdir -p originals
tar xf udis86-1.7.2.tar.gz -C originals

mkdir -p install
cd udis86-1.7.2
patch -p1 -R < ../udis86/udis86.patch
cp ../udis86/btos-build.sh .
./btos-build.sh
