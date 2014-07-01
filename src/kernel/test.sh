make &&
qemu-system-i386 -s -cdrom myos.iso -m 128 -serial stdio -d int,cpu_reset
