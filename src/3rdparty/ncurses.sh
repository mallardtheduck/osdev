#!/bin/bash

rm -rf ncurses-6.0
if [ ! -f ncurses-6.0.tar.gz ];
then
	wget http://ftp.gnu.org/gnu/ncurses/ncurses-6.0.tar.gz
fi
tar xf ncurses-6.0.tar.gz
mkdir -p originals
tar xf ncurses-6.0.tar.gz -C originals

cd ncurses-6.0
#patch -p1 -R < ../ncurses/ncurses.patch
cp ../ncurses/btos-build.sh .
chmod +x btos-build.sh
mkdir -p install
./btos-build.sh
