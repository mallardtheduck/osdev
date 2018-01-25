make -C .. &&
qemu-system-i386 -s -cdrom ../iso/test/test.iso -m 128 -serial stdio -drive file=../disk/btos.img,format=raw -boot order=d $(head -n 1 ../qemu-launch-opts.txt)
#qemu-system-i386 -s -m 128 -serial stdio -drive file=../disk/btos.img,format=raw $(head -n 1 ../qemu-launch-opts.txt)
#-d int,cpu_reset
