#!/bin/bash

rm -rf ncurses-6.0
if [ ! -f SDL2-2.0.7.tar.gz ];
then
	wget https://www.libsdl.org/release/SDL2-2.0.7.tar.gz
fi
tar xf SDL2-2.0.7.tar.gz
mkdir -p originals
tar xf SDL2-2.0.7.tar.gz -C originals

cd SDL2-2.0.7
cp ../sdl/Makefile .
cp ../sdl/*.h include
cp -Rv ../sdl/src/* src
cp ../sdl/SDL_dynapi.h src/dynapi
cp ../sdl/btos-build.sh .
chmod +x btos-build.sh
mkdir -p ../install
./btos-build.sh
