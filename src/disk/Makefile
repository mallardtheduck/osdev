disk-files:= $(shell find diskfiles -type f)

import-files:= \
 data/tests.pkf \

all: ~/.mtoolsrc btos.img

data/tests.pkf: ../packages/tests.pkf
	cp $< $@
	
create.directories:
	mkdir -p data
	touch $@

btos.img: create.directories $(shell find data -type f) ../packages/base.pkf $(disk-files) $(import-files)
	if [ ! -e btos.img ] ; \
	then \
		gunzip -k btos.img.gz ; \
	fi;
	tar xf ../packages/base.pkf -C data
	cp -Rv diskfiles/* data
	mcopy -i btos.img@@1M data/* ::/ -s -o

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

clean:
	-rm btos.img
	-rm -rf data/*
