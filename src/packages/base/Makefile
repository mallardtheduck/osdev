import-files:= data/btos/tests/ctest.elx data/btos/tests/cpptest.elx data/btos/cmd/cmd.elx data/btos/system/terminal.sys data/btos/cmd/cls.elx data/btos/cmd/termctl.elx data/btos/system/switcher.elx data/btos/cmd/spawn.elx data/btos/cmd/kill.elx data/btos/drivers/pci.sys data/btos/cmd/load.elx data/btos/tests/test.sys data/btos/tests/test.elx data/btos/cmd/mount.elx data/btos/tests/msgtest.elx data/btos/tests/mousetest.elx data/btos/drivers/vga.sys data/btos/tests/vgatest.elx data/btos/tests/fputest.elx data/btos/system/gds.elx data/btos/bin/debug.elx data/btos/tests/crash.elx data/btos/tests/gdstest.elx data/btos/system/wm.elx data/btos/tests/wmtest.elx data/btos/bin/wmmenu.elx data/btos/bin/startwm.elx data/btos/bin/termwin.elx data/btos/bin/breakout.elx data/btos/cmd/sleep.elx data/btos/cmd/tar.elx data/btos/drivers/iso9660.sys data/btos/drivers/fat.sys data/btos/cmd/iconv.elx data/btos/cmd/parted.elx data/btos/cmd/format.elx data/btos/bin/install.elx data/btos/tests/shmtest.elx
pkg-files:= $(shell find pkgfiles -type f)


all: ../base.tar

data/btos/tests/ctest.elx: ../../user/ctest/ctest.elx create.directories
	cp $< $@

data/btos/tests/cpptest.elx: ../../user/cpptest/cpptest.elx create.directories
	cp $< $@

data/btos/cmd/cmd.elx: ../../user/cmd/cmd.elx create.directories
	cp $< $@

data/btos/system/terminal.sys: ../../modules/terminal/terminal.sys create.directories
	cp $< $@

data/btos/cmd/cls.elx: ../../user/cls/cls.elx create.directories
	cp $< $@

data/btos/cmd/termctl.elx: ../../user/termctl/termctl.elx create.directories
	cp $< $@

data/btos/system/switcher.elx: ../../user/switcher/switcher.elx create.directories
	cp $< $@

data/btos/cmd/spawn.elx: ../../user/spawn/spawn.elx create.directories
	cp $< $@

data/btos/cmd/kill.elx: ../../user/kill/kill.elx create.directories
	cp $< $@

data/btos/drivers/pci.sys: ../../modules/pci/pci.sys create.directories
	cp $< $@

data/btos/cmd/load.elx: ../../user/load/load.elx create.directories
	cp $< $@

data/btos/tests/test.sys: ../../modules/test/test.sys create.directories
	cp $< $@

data/btos/tests/test.elx: ../../user/test/test.elx create.directories
	cp $< $@

data/btos/cmd/mount.elx: ../../user/mount/mount.elx create.directories
	cp $< $@

data/btos/tests/msgtest.elx: ../../user/msgtest/msgtest.elx create.directories
	cp $< $@

data/btos/tests/mousetest.elx: ../../user/mousetest/mousetest.elx create.directories
	cp $< $@

data/btos/drivers/vga.sys: ../../modules/vga/vga.sys create.directories
	cp $< $@

data/btos/tests/vgatest.elx: ../../user/vgatest/vgatest.elx create.directories
	cp $< $@

data/btos/bin/debug.elx: ../../user/debug/debug.elx create.directories
	cp $< $@

data/btos/tests/crash.elx: ../../user/crash/crash.elx create.directories
	cp $< $@

data/btos/system/gds.elx: ../../user/gds/gds.elx create.directories
	cp $< $@
	
data/btos/tests/gdstest.elx: ../../user/libgds/gdstest.elx create.directories
	cp $< $@

data/btos/tests/fputest.elx: ../../user/fputest/fputest.elx create.directories
	cp $< $@
	
data/btos/system/wm.elx: ../../user/wm/wm.elx create.directories
	cp $< $@
	
data/btos/tests/wmtest.elx: ../../user/libwm/wmtest.elx create.directories
	cp $< $@
	
data/btos/bin/wmmenu.elx: ../../user/wmmenu/wmmenu.elx create.directories
	cp $< $@

data/btos/bin/startwm.elx: ../../user/startwm/startwm.elx create.directories
	cp $< $@

data/btos/bin/termwin.elx: ../../user/termwin/termwin.elx create.directories
	cp $< $@

data/btos/bin/breakout.elx: ../../user/breakout/breakout.elx create.directories
	cp $< $@

data/btos/cmd/sleep.elx: ../../user/sleep/sleep.elx create.directories
	cp $< $@

data/btos/cmd/tar.elx: ../../user/tar/tar.elx create.directories
	cp $< $@

data/btos/drivers/iso9660.sys: ../../modules/iso9660/iso9660.sys create.directories
	cp $< $@

data/btos/drivers/fat.sys: ../../modules/fat/fat.sys create.directories
	cp $< $@

data/btos/cmd/iconv.elx: ../../3rdparty/install/btos/bin/iconv.elx create.directories
	cp $< $@

data/btos/cmd/parted.elx: ../../3rdparty/install/btos/sbin/parted.elx create.directories
	cp $< $@

data/btos/cmd/format.elx: ../../user/format/format.elx create.directories
	cp $< $@
	
data/btos/bin/install.elx: ../../user/install/install.elx create.directories
	cp $< $@
	
data/btos/tests/shmtest.elx: ../../user/shmtest/shmtest.elx create.directories
	cp $< $@

copy.grub: ../../3rdparty/install/btos/sbin/grub-bios-setup.elx ../../3rdparty/install/btos/bin/grub-mkimage.elx ../../3rdparty/install/btos/bin/grub-mklayout.elx ../../3rdparty/install/btos/bin/grub-mkrelpath.elx
	mkdir -p data/btos/boot/grub/
	cp -R ../../3rdparty/install/btos/lib/grub/i386-pc data/btos/boot/grub
	cp ../../3rdparty/install/btos/sbin/grub-bios-setup.elx data/btos/boot/grub/grubbios.elx
	cp ../../3rdparty/install/btos/bin/grub-mkimage.elx data/btos/boot/grub/grubmkim.elx
	cp ../../3rdparty/install/btos/bin/grub-mklayout.elx data/btos/boot/grub/grubmkla.elx
	cp ../../3rdparty/install/btos/bin/grub-mkrelpath.elx data/btos/boot/grub/grubmkrp.elx
	touch copy.grub

create.directories:
	mkdir -p data/btos/cmd
	mkdir -p data/btos/temp
	mkdir -p data/btos/tests
	mkdir -p data/btos/bin
	mkdir -p data/btos/system
	mkdir -p data/btos/drivers
	touch create.directories

../base.tar: $(import-files) $(pkg-files) copy.grub
	-cp -R pkgfiles/* data
	tar cf ../base.tar -C data .

clean:
	-rm -rf data
	-rm ../base.tar
	-rm create.directories