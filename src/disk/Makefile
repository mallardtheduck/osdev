import-files:=data/ctest.elx data/cpptest.elx

all: btos.img

btos.img: data $(shell find data -type f) $(import-files)
	if [ ! -e btos.img ] ; \
	then \
		qemu-img create btos.img 100M ; \
		parted btos.img mklabel msdos ; \
		parted btos.img mkpartfs primary fat16 1 100 ; \
	fi;
	mcopy -i btos.img@@1M data/* ::/ -s -o

data/ctest.elx:
	cp ../user/ctest/ctest.elx data/ctest.elx

data/cpptest.elx:
	cp ../user/cpptest/cpptest.elx data/cpptest.elx