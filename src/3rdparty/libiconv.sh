#!/bin/bash

rm -rf libiconv-1.14
if [ ! -f libiconv-1.14.tar.gz ];
then
	wget http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.14.tar.gz
fi
tar xf libiconv-1.14.tar.gz
mkdir -p originals
tar xf libiconv-1.14.tar.gz -C originals

cd libiconv-1.14
patch -p1 -R < ../libiconv/libiconv.patch
cp ../libiconv/btos-build.sh .
mkdir -p install
./btos-build.sh
