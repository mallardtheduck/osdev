import-files:=data/btos/tests/ctest.elx data/btos/tests/cpptest.elx data/btos/cmd/cmd.elx data/btos/system/terminal.sys data/btos/cmd/cls.elx data/btos/cmd/termctl.elx data/btos/system/switcher.elx data/btos/cmd/spawn.elx data/btos/cmd/kill.elx data/btos/drivers/pci.sys data/btos/cmd/load.elx data/btos/tests/test.sys data/btos/tests/test.elx data/btos/cmd/mount.elx data/btos/tests/msgtest.elx data/btos/tests/mousetest.elx data/btos/drivers/vga.sys data/btos/tests/vgatest.elx data/btos/tests/fputest.elx data/btos/system/gds.elx data/btos/bin/debug.elx data/btos/tests/crash.elx data/btos/tests/gdstest.elx data/btos/system/wm.elx data/btos/tests/wmtest.elx data/btos/bin/wmmenu.elx data/btos/bin/startwm.elx data/btos/bin/termwin.elx data/btos/bin/breakout.elx data/btos/cmd/sleep.elx data/btos/cmd/tar.elx data/btos/drivers/iso9660.sys data/btos/cmd/iconv.elx data/btos/cmd/parted.elx

all: ~/.mtoolsrc btos.img copy.always

btos.img: 
	if [ ! -e btos.img ] ; \
	then \
		gunzip -k btos.img.gz ; \
	fi;

data/btos/tests/ctest.elx: ../user/ctest/ctest.elx
	cp $< $@

data/btos/tests/cpptest.elx: ../user/cpptest/cpptest.elx
	cp $< $@

data/btos/cmd/cmd.elx: ../user/cmd/cmd.elx directories.always
	cp $< $@

data/btos/system/terminal.sys: ../modules/terminal/terminal.sys directories.always
	cp $< $@

data/btos/cmd/cls.elx: ../user/cls/cls.elx directories.always
	cp $< $@

data/btos/cmd/termctl.elx: ../user/termctl/termctl.elx directories.always
	cp $< $@

data/btos/system/switcher.elx: ../user/switcher/switcher.elx directories.always
	cp $< $@

data/btos/cmd/spawn.elx: ../user/spawn/spawn.elx directories.always
	cp $< $@

data/btos/cmd/kill.elx: ../user/kill/kill.elx directories.always
	cp $< $@

data/btos/drivers/pci.sys: ../modules/pci/pci.sys directories.always
	cp $< $@

data/btos/cmd/load.elx: ../user/load/load.elx directories.always
	cp $< $@

data/btos/tests/test.sys: ../modules/test/test.sys directories.always
	cp $< $@

data/btos/tests/test.elx: ../user/test/test.elx directories.always
	cp $< $@

data/btos/cmd/mount.elx: ../user/mount/mount.elx directories.always
	cp $< $@

data/btos/tests/msgtest.elx: ../user/msgtest/msgtest.elx directories.always
	cp $< $@

data/btos/tests/mousetest.elx: ../user/mousetest/mousetest.elx directories.always
	cp $< $@

data/btos/drivers/vga.sys: ../modules/vga/vga.sys directories.always
	cp $< $@

data/btos/tests/vgatest.elx: ../user/vgatest/vgatest.elx directories.always
	cp $< $@

data/btos/bin/debug.elx: ../user/debug/debug.elx directories.always
	cp $< $@

data/btos/tests/crash.elx: ../user/crash/crash.elx directories.always
	cp $< $@

data/btos/system/gds.elx: ../user/gds/gds.elx directories.always
	cp $< $@
	
data/btos/tests/gdstest.elx: ../user/libgds/gdstest.elx directories.always
	cp $< $@

data/btos/tests/fputest.elx: ../user/fputest/fputest.elx directories.always
	cp $< $@
	
data/btos/system/wm.elx: ../user/wm/wm.elx directories.always
	cp $< $@
	
data/btos/tests/wmtest.elx: ../user/libwm/wmtest.elx directories.always
	cp $< $@
	
data/btos/bin/wmmenu.elx: ../user/wmmenu/wmmenu.elx directories.always
	cp $< $@

data/btos/bin/startwm.elx: ../user/startwm/startwm.elx directories.always
	cp $< $@

data/btos/bin/termwin.elx: ../user/termwin/termwin.elx directories.always
	cp $< $@

data/btos/bin/breakout.elx: ../user/breakout/breakout.elx directories.always
	cp $< $@

data/btos/cmd/sleep.elx: ../user/sleep/sleep.elx directories.always
	cp $< $@

data/btos/cmd/tar.elx: ../user/tar/tar.elx directories.always
	cp $< $@

data/btos/drivers/iso9660.sys: ../modules/iso9660/iso9660.sys directories.always
	cp $< $@
	
data/btos/cmd/iconv.elx: ../3rdparty/install/btos/bin/iconv.elx directories.always
	cp $< $@

data/btos/cmd/parted.elx: ../3rdparty/install/btos/sbin/parted.elx directories.always
	cp $< $@

directories.always:
	mkdir -p data/btos/cmd
	mkdir -p data/btos/temp
	mkdir -p data/btos/tests
	mkdir -p data/btos/bin
	mkdir -p data/btos/system
	mkdir -p data/btos/drivers

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

copy.always: directories.always $(shell find data -type f) $(import-files)
	mcopy -i btos.img@@1M data/* ::/ -s -o

clean:
	-rm btos.img
	-rm -rf data/*
