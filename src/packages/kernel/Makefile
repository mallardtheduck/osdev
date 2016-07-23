import-files:=data/btos/boot/btos.bin data/btos/boot/initfs/boot.sys data/btos/boot/initfs/rtc.sys data/btos/boot/initfs/ps2.sys data/btos/boot/initfs/ata.sys data/btos/boot/initfs/spawn.elx data/btos/boot/initfs/fat.sys
pkg-files:= $(shell find pkgfiles -type f)

all: ../kernel.tar

data/btos/boot/btos.bin: ../../kernel/btos.bin create.directories
	cp $< $@

data/btos/boot/initfs/boot.sys: ../../modules/boot/boot.sys create.directories
	cp $< $@

data/btos/boot/initfs/rtc.sys: ../../modules/rtc/rtc.sys create.directories
	cp $< $@

data/btos/boot/initfs/ps2.sys: ../../modules/ps2/ps2.sys create.directories
	cp $< $@

data/btos/boot/initfs/ata.sys: ../../modules/ata/ata.sys create.directories
	cp $< $@

data/btos/boot/initfs/spawn.elx: ../../user/spawn/spawn.elx create.directories
	cp $< $@

data/btos/boot/initfs/fat.sys: ../../modules/fat/fat.sys create.directories
	cp $< $@

create.directories:
	mkdir -p data/btos/boot/initfs
	touch create.directories

../kernel.tar: $(import-files) $(pkg-files)
	-cp -R pkgfiles/* data
	strip data/btos/boot/initfs/*.elx
	strip -g data/btos/boot/initfs/*.sys
	tar cf ../kernel.tar -C data .

clean:
	-rm -rf data
	-rm ../kernel.tar
	-rm create.directories
