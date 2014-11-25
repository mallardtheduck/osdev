import-files:=data/ctest.elx data/cpptest.elx data/btos/cmd.elx data/btos/terminal.sys data/btos/cmd/cls.elx data/btos/cmd/termctl.elx data/btos/switcher.elx data/btos/spawn.elx data/btos/cmd/kill.elx data/btos/pci.sys data/btos/cmd/load.elx

all: ~/.mtoolsrc btos.img copy.always

btos.img: 
	if [ ! -e btos.img ] ; \
	then \
		gunzip -k btos.img.gz ; \
	fi;

data/ctest.elx: ../user/ctest/ctest.elx
	cp ../user/ctest/ctest.elx data/ctest.elx

data/cpptest.elx: ../user/cpptest/cpptest.elx
	cp ../user/cpptest/cpptest.elx data/cpptest.elx

data/btos/cmd.elx: ../user/cmd/cmd.elx directories.always
	cp ../user/cmd/cmd.elx $@

data/btos/terminal.sys: ../modules/terminal/terminal.sys directories.always
	cp ../modules/terminal/terminal.sys $@

data/btos/cmd/cls.elx: ../user/cls/cls.elx directories.always
	cp ../user/cls/cls.elx $@

data/btos/cmd/termctl.elx: ../user/termctl/termctl.elx directories.always
	cp ../user/termctl/termctl.elx $@

data/btos/switcher.elx: ../user/switcher/switcher.elx directories.always
	cp ../user/switcher/switcher.elx $@

data/btos/spawn.elx: ../user/spawn/spawn.elx directories.always
	cp ../user/spawn/spawn.elx $@

data/btos/cmd/kill.elx: ../user/kill/kill.elx directories.always
	cp ../user/kill/kill.elx $@


data/btos/pci.sys: ../modules/pci/pci.sys directories.always
	cp ../modules/pci/pci.sys $@

data/btos/cmd/load.elx: ../user/load/load.elx directories.always
	cp ../user/load/load.elx $@

directories.always:
	mkdir -p data/btos/cmd
	mkdir -p data/btos/temp

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

copy.always: directories.always $(shell find data -type f) $(import-files)
	mcopy -i btos.img@@1M data/* ::/ -s -o

