all: ../install.tar

directories.always:
	mkdir -p data/btos/boot/initfs

../install.tar:
	-cp -R pkgfiles/* data
	tar cf ../install.tar -C data .

clean:
	-rm -rf data
	-rm ../install.tar
