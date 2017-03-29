all: ../install.tar
pkg-files:= $(shell find pkgfiles -type f)

create.directories:
	mkdir -p data/btos
	touch create.directories

../install.tar: $(pkg-files) create.directories
	-cp -R pkgfiles/* data
	tar cf ../install.tar -C data .

clean:
	-rm -rf data
	-rm ../install.tar
	-rm create.directories
