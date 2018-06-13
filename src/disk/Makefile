disk-files:= $(shell find diskfiles -type f)

import-files:= \
 data/tests.pkf \
 data/protogui.pkf

all: ~/.mtoolsrc btos.img

data/tests.pkf: ../packages/tests.pkf
	cp $< $@

data/protogui.pkf: ../packages/protogui.pkf
	cp $< $@

btos.img: $(shell find data -type f) ../packages/base.pkf $(disk-files) $(import-files)
	if [ ! -e btos.img ] ; \
	then \
		gunzip -k btos.img.gz ; \
	fi;
	mkdir -p data
	tar xf ../packages/base.pkf -C data
	cp -Rv diskfiles/* data
	mcopy -i btos.img@@1M data/* ::/ -s -o

~/.mtoolsrc:
	echo "mtools_skip_check=1" > ~/.mtoolsrc

clean:
	-rm btos.img
	-rm -rf data/*
