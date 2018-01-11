output-name := install.pkf

all: ../$(output-name)
pkg-files:= $(shell find pkgfiles -type f)

create.directories:
	mkdir -p data/btos
	touch create.directories

../$(output-name): $(pkg-files) create.directories
	-cp -R pkgfiles/* data
	tar cf ../$(output-name) -C data .

clean:
	-rm -rf data
	-rm ../$(output-name)
	-rm create.directories
