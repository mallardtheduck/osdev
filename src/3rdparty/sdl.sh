#!/bin/bash

rm -rf SDL2-2.0.7
if [ ! -f SDL2-2.0.7.tar.gz ];
then
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/SDL2-2.0.7.tar.gz
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
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/SDL2_ttf-2.0.14.tar.gz
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

cd ..
rm -rf SDL2_image-2.0.3
if [ ! -f SDL2_image-2.0.3.tar.gz ];
then
	wget https://github.com/mallardtheduck/btos-3rdparty-prereqs/raw/master/SDL2_image-2.0.3.tar.gz
fi
tar xf SDL2_image-2.0.3.tar.gz
mkdir -p originals
tar xf SDL2_image-2.0.3.tar.gz -C originals
cd SDL2_image-2.0.3
cp ../sdl/image_Makefile Makefile
cp ../sdl/IMG_svg.c .
cp ../sdl/btos-build.sh .
chmod +x btos-build.sh
mkdir -p ../install
./btos-build.sh
