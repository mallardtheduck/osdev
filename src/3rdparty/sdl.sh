#!/bin/bash

rm -rf SDL2-2.0.7
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
cp ../sdl/SDL_video.c src/video
cp ../sdl/SDL_sysvideo.h src/video
cp ../sdl/btos-build.sh .
chmod +x btos-build.sh
mkdir -p ../install
./btos-build.sh

cd ..
rm -rf SDL2_ttf-2.0.14
if [ ! -f SDL2_ttf-2.0.14.tar.gz ];
then
	wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
fi
tar xf SDL2_ttf-2.0.14.tar.gz
mkdir -p originals
tar xf SDL2_ttf-2.0.14.tar.gz -C originals
cd SDL2_ttf-2.0.14
cp ../sdl/ttf_Makefile Makefile
cp ../sdl/btos-build.sh .
chmod +x btos-build.sh
mkdir -p ../install
./btos-build.sh
