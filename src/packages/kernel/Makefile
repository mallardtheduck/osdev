import-files:=data/btos/boot/btos.bin data/btos/boot/initfs/boot.sys data/btos/boot/initfs/rtc.sys data/btos/boot/initfs/ps2.sys data/btos/boot/initfs/ata.sys data/btos/boot/initfs/spawn.elx data/btos/boot/initfs/fat.sys data/btos/boot/initfs/eloader.elx
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

data/btos/boot/initfs/spawn.elx: ../../user/system/spawn/spawn.elx create.directories
	cp $< $@

data/btos/boot/initfs/fat.sys: ../../modules/fat/fat.sys create.directories
	cp $< $@

data/btos/boot/initfs/eloader.elx: ../../user/system/eloader/eloader.elx create.directories
	cp $< $@

create.directories:
	mkdir -p data/btos/boot/initfs
	touch create.directories

../kernel.tar: $(import-files) $(pkg-files)
	-cp -R pkgfiles/* data
	find data/btos/boot/initfs/ -name \*.elx -not -name eloader.elx -exec strip {} \;
	strip -K loaded_modules -K loaded_module_count data/btos/boot/initfs/eloader.elx
	strip -g data/btos/boot/initfs/*.sys
	tar cf ../kernel.tar -C data .

clean:
	-rm -rf data
	-rm ../kernel.tar
	-rm create.directories
