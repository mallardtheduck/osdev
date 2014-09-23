import-files:=data/ctest.elx data/cpptest.elx data/btos/cmd.elx data/btos/terminal.sys

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

data/btos/cmd.elx: ../user/cmd/cmd.elx data/btos
	cp ../user/cmd/cmd.elx $@

data/btos/terminal.sys: ../modules/terminal/terminal.sys data/btos
	cp ../modules/terminal/terminal.sys $@

data/btos:
	mkdir data/btos

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

copy.always: data $(shell find data -type f) $(import-files)
	mcopy -i btos.img@@1M data/* ::/ -s -o

