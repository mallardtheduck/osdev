import-files:=data/ctest.elx data/cpptest.elx data/cmd.elx

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

data/cmd.elx: ../user/cmd/cmd.elx
	cp ../user/cmd/cmd.elx data/cmd.elx

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

copy.always: data $(shell find data -type f) $(import-files)
	mcopy -i btos.img@@1M data/* ::/ -s -o

