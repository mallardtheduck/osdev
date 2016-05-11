import-files:=data/btos/boot/btos.bin data/btos/boot/initfs/boot.sys data/btos/boot/initfs/rtc.sys data/btos/boot/initfs/ps2.sys data/btos/boot/initfs/ata.sys data/btos/boot/initfs/spawn.elx data/btos/boot/initfs/fat.sys

all: ../kernel.tar

data/btos/boot/btos.bin: ../../kernel/btos.bin directories.always
	cp $< $@

data/btos/boot/initfs/boot.sys: ../../modules/boot/boot.sys directories.always
	cp $< $@

data/btos/boot/initfs/rtc.sys: ../../modules/rtc/rtc.sys directories.always
	cp $< $@

data/btos/boot/initfs/ps2.sys: ../../modules/ps2/ps2.sys directories.always
	cp $< $@

data/btos/boot/initfs/ata.sys: ../../modules/ata/ata.sys directories.always
	cp $< $@

data/btos/boot/initfs/spawn.elx: ../../user/spawn/spawn.elx directories.always
	cp $< $@

data/btos/boot/initfs/fat.sys: ../../modules/fat/fat.sys directories.always
	cp $< $@

directories.always:
	mkdir -p data/btos/boot/initfs

../kernel.tar: $(import-files)
	-cp -R pkgfiles/* data
	strip data/btos/boot/initfs/*.elx
	strip -g data/btos/boot/initfs/*.sys
	tar cf ../kernel.tar -C data .

clean:
	-rm -rf data
	-rm ../kernel.tar
