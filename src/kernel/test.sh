make -C .. &&
qemu-system-i386 -s -cdrom ../iso/test/test.iso -m 128 -serial stdio -hda ../disk/btos.img -boot order=d -display sdl
#-d int,cpu_reset
