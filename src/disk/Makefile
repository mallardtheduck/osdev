all: ~/.mtoolsrc btos.img copy.always

btos.img: 
	if [ ! -e btos.img ] ; \
	then \
		gunzip -k btos.img.gz ; \
	fi;

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

copy.always: $(shell find data -type f) ../packages/base.tar
	mkdir -p data
	tar xf ../packages/base.tar -C data
	mcopy -i btos.img@@1M data/* ::/ -s -o

clean:
	-rm btos.img
	-rm -rf data/*
