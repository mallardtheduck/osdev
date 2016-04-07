#!/bin/bash

rm -rf grub-2.00
if [ ! -f grub-2.00.tar.xz ];
then
	wget ftp://ftp.gnu.org/gnu/grub/grub-2.00.tar.xz
fi
tar xf grub-2.00.tar.xz
mkdir -p originals
tar xf grub-2.00.tar.xz -C originals

mkdir -p install
cd grub-2.00
patch -p1 -R < ../grub/grub.patch
cp ../grub/btos-build.sh .
./btos-build.sh
