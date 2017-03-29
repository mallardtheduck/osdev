make -C .. &&
qemu-system-i386 -s -cdrom ../iso/test/test.iso -m 128 -serial file:serial.out -hda ../disk/btos.img -boot order=d -curses
#-d int,cpu_reset
