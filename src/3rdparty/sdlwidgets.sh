#!/bin/bash

rm -rf SDL2-widgets-2.1
if [ ! -f SDL2-widgets-2.1.tar.gz ];
then
	wget http://members.chello.nl/w.boeke/SDL-widgets/SDL2-widgets-2.1.tar.gz
fi
tar xf SDL2-widgets-2.1.tar.gz
mkdir -p originals
tar xf SDL2-widgets-2.1.tar.gz -C originals

cd SDL2-widgets-2.1
patch -p1 -R < ../sdlwidgets/sdlwidgets.patch
make

cp SDL2_widgets.ell ../install/btos/lib
cp sdl-widgets.h ../install/btos/include/SDL2_widgets.h
