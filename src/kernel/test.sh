make -C .. &&
qemu-system-i386 -s -cdrom btos.iso -m 128 -serial stdio -hda ../disk/btos.img -boot order=d
#-d int,cpu_reset
