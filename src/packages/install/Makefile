all: ../install.tar

directories.always:
	mkdir -p data/btos

../install.tar: directories.always
	-cp -R pkgfiles/* data
	tar cf ../install.tar -C data .

clean:
	-rm -rf data
	-rm ../install.tar
