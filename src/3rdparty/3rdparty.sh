#!/bin/bash -x

case "$1" in
	stage1)
	run=1
	;;
	
	stage2)
	run=2
	;;
	
	*)
	run=12
	;;
esac

source ../env-os.sh

case "$run" in
	*1*)
	./libiconv.sh && 
	./freetype.sh && 
	./libgd.sh && 
	./libuuid.sh && 
	./libelf.sh && 
	./grub.sh && 
	./parted.sh && 
	./udis86.sh &&
	./ncurses.sh &&
	./sqlite3.sh
	;;
esac

case "$run" in
	*2*)
	./sdl.sh &&
	./sdlwidgets.sh
	;;
esac

