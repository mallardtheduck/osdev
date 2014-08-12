make -C .. &&
qemu-system-i386 -s -cdrom myos.iso -m 128 -serial stdio -hda test.img
#-d int,cpu_reset
