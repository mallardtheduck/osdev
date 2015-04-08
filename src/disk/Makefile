import-files:=data/btos/ctest.elx data/btos/cpptest.elx data/btos/cmd.elx data/btos/terminal.sys data/btos/cmd/cls.elx data/btos/cmd/termctl.elx data/btos/switcher.elx data/btos/spawn.elx data/btos/cmd/kill.elx data/btos/pci.sys data/btos/cmd/load.elx data/btos/test.sys data/btos/test.elx data/btos/cmd/mount.elx data/btos/msgtest.elx data/btos/mousetest.elx data/btos/vga.sys data/btos/vgatest.elx data/btos/fputest.elx data/btos/gds.elx

all: ~/.mtoolsrc btos.img copy.always

btos.img: 
	if [ ! -e btos.img ] ; \
	then \
		gunzip -k btos.img.gz ; \
	fi;

data/btos/ctest.elx: ../user/ctest/ctest.elx
	cp $< $@

data/btos/cpptest.elx: ../user/cpptest/cpptest.elx
	cp $< $@

data/btos/cmd.elx: ../user/cmd/cmd.elx directories.always
	cp $< $@

data/btos/terminal.sys: ../modules/terminal/terminal.sys directories.always
	cp $< $@

data/btos/cmd/cls.elx: ../user/cls/cls.elx directories.always
	cp $< $@

data/btos/cmd/termctl.elx: ../user/termctl/termctl.elx directories.always
	cp $< $@

data/btos/switcher.elx: ../user/switcher/switcher.elx directories.always
	cp $< $@

data/btos/spawn.elx: ../user/spawn/spawn.elx directories.always
	cp $< $@

data/btos/cmd/kill.elx: ../user/kill/kill.elx directories.always
	cp $< $@

data/btos/pci.sys: ../modules/pci/pci.sys directories.always
	cp $< $@

data/btos/cmd/load.elx: ../user/load/load.elx directories.always
	cp $< $@

data/btos/test.sys: ../modules/test/test.sys directories.always
	cp $< $@

data/btos/test.elx: ../user/test/test.elx directories.always
	cp $< $@

data/btos/cmd/mount.elx: ../user/mount/mount.elx directories.always
	cp $< $@

data/btos/msgtest.elx: ../user/msgtest/msgtest.elx directories.always
	cp $< $@

data/btos/mousetest.elx: ../user/mousetest/mousetest.elx directories.always
	cp $< $@

data/btos/vga.sys: ../modules/vga/vga.sys directories.always
	cp $< $@

data/btos/vgatest.elx: ../user/vgatest/vgatest.elx directories.always
	cp $< $@

data/btos/fputest.elx: ../user/fputest/fputest.elx directories.always
	cp $< $@
	
data/btos/gds.elx: ../user/gds/gds.elx directories.always
	cp $< $@

directories.always:
	mkdir -p data/btos/cmd
	mkdir -p data/btos/temp

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

copy.always: directories.always $(shell find data -type f) $(import-files)
	mcopy -i btos.img@@1M data/* ::/ -s -o

clean:
	rm btos.img
	rm -rf data/*
