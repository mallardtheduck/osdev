output-name := gui.pkf

all: ../$(output-name)
pkg-files:= $(shell find pkgfiles -type f)

import-files:= \
 data/btos/calc.elx \
 data/btos/folder.elx \
 data/btos/notepad.elx \
 
data/btos/calc.elx: ../../user/wmapps/calc/calc.elx
	cp $< $@

data/btos/folder.elx: ../../user/wmapps/folder/folder.elx
	cp $< $@

data/btos/notepad.elx: ../../user/wmapps/notepad/notepad.elx
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
