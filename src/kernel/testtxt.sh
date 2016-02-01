make &&
qemu-system-i386 -s -cdrom ../iso/test/test.iso -curses -m 128 -serial file:serial.out
