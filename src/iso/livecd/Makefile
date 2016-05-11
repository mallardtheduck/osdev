all: livecd.iso
	
btos-files: ../../packages/base.tar
	mkdir -p isodir
	tar xf ../../packages/base.tar -C isodir
	cp ../../packages/base.tar isodir
	cp ../../packages/kernel.tar isodir

livecd.iso: ../../kernel/btos.bin ../../tarinit/livecd/init.tar btos-files
	mkdir -p isodir
	mkdir -p isodir/boot
	cp ../../kernel/btos.bin isodir/boot/btos.bin
	cp ../../tarinit/livecd/init.tar isodir/boot/init.tar
	mkdir -p isodir/boot/grub
	cp grub.cfg isodir/boot/grub/grub.cfg
	mkdir -p isodir/boot/grub/i386-pc
	cp -r /usr/lib/grub/i386-pc/* isodir/boot/grub/i386-pc
	rm isodir/boot/grub/i386-pc/*.img
	grub-mkimage -O i386-pc -d /usr/lib/grub/i386-pc -o core.img -c load_cfg --prefix=/boot/grub iso9660 biosdisk
	cat /usr/lib/grub/i386-pc/cdboot.img core.img > isodir/boot/grub/i386-pc/eltorito.img
	cat /usr/lib/grub/i386-pc/boot.img core.img > embedded.img
	xorriso -report_about HINT -as mkisofs -graft-points -b boot/grub/i386-pc/eltorito.img -no-emul-boot -boot-info-table --embedded-boot embedded.img --protective-msdos-label -o $@ -r isodir --sort-weight 0 / --sort-weight 1 /boot
 
clean:
	-rm core.img
	-rm embedded.img
	-rm -rf isodir
	-rm livecd.iso
