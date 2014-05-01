make &&
qemu-system-i386 -s -cdrom myos.iso -curses -m 128 -serial file:serial.out
