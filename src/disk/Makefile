disk-files:= $(shell find diskfiles -type f)

all: ~/.mtoolsrc btos.img

btos.img: $(shell find data -type f) ../packages/base.tar $(disk-files)
	if [ ! -e btos.img ] ; \
	then \
		gunzip -k btos.img.gz ; \
	fi;
	mkdir -p data
	tar xf ../packages/base.tar -C data
	cp -Rv diskfiles/* data
	mcopy -i btos.img@@1M data/* ::/ -s -o

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

clean:
	-rm btos.img
	-rm -rf data/*
