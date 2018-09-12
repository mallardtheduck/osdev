output-name := protogui.pkf

all: ../$(output-name)
pkg-files:= $(shell find pkgfiles -type f)

import-files:= \
 data/btos/protoclock.elx \
 data/btos/prototext.elx \
 data/btos/prototask.elx
 
data/btos/protoclock.elx: ../../user/wmapps/protoclock/protoclock.elx
	cp $< $@
	
data/btos/prototext.elx: ../../user/wmapps/prototext/prototext.elx
	cp $< $@
	
data/btos/prototask.elx: ../../user/wmapps/prototask/prototask.elx
	cp $< $@

create.directories:
	mkdir -p data/btos
	touch create.directories

../$(output-name): $(pkg-files) create.directories $(import-files)
	-cp -R pkgfiles/* data
	tar cf ../$(output-name) -C data .

clean:
	-rm -rf data
	-rm ../$(output-name)
	-rm create.directories
