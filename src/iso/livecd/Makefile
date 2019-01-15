all: livecd.iso
packages:= $(shell find ../../packages/ -name \*.pkf)

livecd.iso: ../../kernel/btos.bin ../../tarinit/livecd/init.tar ../../packages/base.pkf initreg.cmd $(packages)
	mkdir -p isodir
	tar xf ../../packages/base.pkf -C isodir
	rm -rf isodir/btos/share/terminfo
	mkdir -p isodir/btos/share/terminfo/b
	cp ../../3rdparty/install/btos/share/terminfo/b/btosansi isodir/btos/share/terminfo/b
	mkdir -p isodir/packages
	cp ../../packages/*.pkf isodir/packages
	mkdir -p isodir/boot
	cp ../../kernel/btos.bin isodir/boot/btos.bin
	cp ../../tarinit/livecd/init.tar isodir/boot/init.tar
	cp initreg.cmd isodir
	mkdir -p isodir/boot/grub
	cp grub.cfg isodir/boot/grub/grub.cfg
	cp ../../../other/art/splash.tga isodir/boot/splash.tga
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