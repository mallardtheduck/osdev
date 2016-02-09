import-files:= isodir/btos/tests/ctest.elx isodir/btos/tests/cpptest.elx isodir/btos/cmd/cmd.elx isodir/btos/system/terminal.sys isodir/btos/cmd/cls.elx isodir/btos/cmd/termctl.elx isodir/btos/system/switcher.elx isodir/btos/cmd/spawn.elx isodir/btos/cmd/kill.elx isodir/btos/drivers/pci.sys isodir/btos/cmd/load.elx isodir/btos/tests/test.sys isodir/btos/tests/test.elx isodir/btos/cmd/mount.elx isodir/btos/tests/msgtest.elx isodir/btos/tests/mousetest.elx isodir/btos/drivers/vga.sys isodir/btos/tests/vgatest.elx isodir/btos/tests/fputest.elx isodir/btos/system/gds.elx isodir/btos/bin/debug.elx isodir/btos/tests/crash.elx isodir/btos/tests/gdstest.elx isodir/btos/system/wm.elx isodir/btos/tests/wmtest.elx isodir/btos/bin/wmmenu.elx isodir/btos/bin/startwm.elx isodir/btos/bin/termwin.elx isodir/btos/bin/breakout.elx isodir/btos/cmd/sleep.elx isodir/btos/cmd/tar.elx isodir/btos/drivers/iso9660.sys

all: livecd.iso

isodir/btos/tests/ctest.elx: ../../user/ctest/ctest.elx directories.always
	cp $< $@

isodir/btos/tests/cpptest.elx: ../../user/cpptest/cpptest.elx directories.always
	cp $< $@

isodir/btos/cmd/cmd.elx: ../../user/cmd/cmd.elx directories.always
	cp $< $@

isodir/btos/system/terminal.sys: ../../modules/terminal/terminal.sys directories.always
	cp $< $@

isodir/btos/cmd/cls.elx: ../../user/cls/cls.elx directories.always
	cp $< $@

isodir/btos/cmd/termctl.elx: ../../user/termctl/termctl.elx directories.always
	cp $< $@

isodir/btos/system/switcher.elx: ../../user/switcher/switcher.elx directories.always
	cp $< $@

isodir/btos/cmd/spawn.elx: ../../user/spawn/spawn.elx directories.always
	cp $< $@

isodir/btos/cmd/kill.elx: ../../user/kill/kill.elx directories.always
	cp $< $@

isodir/btos/drivers/pci.sys: ../../modules/pci/pci.sys directories.always
	cp $< $@

isodir/btos/cmd/load.elx: ../../user/load/load.elx directories.always
	cp $< $@

isodir/btos/tests/test.sys: ../../modules/test/test.sys directories.always
	cp $< $@

isodir/btos/tests/test.elx: ../../user/test/test.elx directories.always
	cp $< $@

isodir/btos/cmd/mount.elx: ../../user/mount/mount.elx directories.always
	cp $< $@

isodir/btos/tests/msgtest.elx: ../../user/msgtest/msgtest.elx directories.always
	cp $< $@

isodir/btos/tests/mousetest.elx: ../../user/mousetest/mousetest.elx directories.always
	cp $< $@

isodir/btos/drivers/vga.sys: ../../modules/vga/vga.sys directories.always
	cp $< $@

isodir/btos/tests/vgatest.elx: ../../user/vgatest/vgatest.elx directories.always
	cp $< $@

isodir/btos/bin/debug.elx: ../../user/debug/debug.elx directories.always
	cp $< $@

isodir/btos/tests/crash.elx: ../../user/crash/crash.elx directories.always
	cp $< $@

isodir/btos/system/gds.elx: ../../user/gds/gds.elx directories.always
	cp $< $@
	
isodir/btos/tests/gdstest.elx: ../../user/libgds/gdstest.elx directories.always
	cp $< $@

isodir/btos/tests/fputest.elx: ../../user/fputest/fputest.elx directories.always
	cp $< $@
	
isodir/btos/system/wm.elx: ../../user/wm/wm.elx directories.always
	cp $< $@
	
isodir/btos/tests/wmtest.elx: ../../user/libwm/wmtest.elx directories.always
	cp $< $@
	
isodir/btos/bin/wmmenu.elx: ../../user/wmmenu/wmmenu.elx directories.always
	cp $< $@

isodir/btos/bin/startwm.elx: ../../user/startwm/startwm.elx directories.always
	cp $< $@

isodir/btos/bin/termwin.elx: ../../user/termwin/termwin.elx directories.always
	cp $< $@

isodir/btos/bin/breakout.elx: ../../user/breakout/breakout.elx directories.always
	cp $< $@

isodir/btos/cmd/sleep.elx: ../../user/sleep/sleep.elx directories.always
	cp $< $@

isodir/btos/cmd/tar.elx: ../../user/tar/tar.elx directories.always
	cp $< $@

isodir/btos/drivers/iso9660.sys: ../../modules/iso9660/iso9660.sys directories.always
	cp $< $@

directories.always:
	mkdir -p isodir/btos/cmd
	mkdir -p isodir/btos/temp
	mkdir -p isodir/btos/tests
	mkdir -p isodir/btos/bin
	mkdir -p isodir/btos/system
	mkdir -p isodir/btos/drivers

livecd.iso: ../../kernel/btos.bin ../../tarinit/livecd/init.tar $(import-files)
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