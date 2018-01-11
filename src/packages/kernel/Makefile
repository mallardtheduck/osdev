output-name := kernel.pkf

import-files:= \
  data/btos/boot/btos.bin \
  data/btos/boot/initfs/boot.sys \
  data/btos/boot/initfs/rtc.sys \
  data/btos/boot/initfs/ps2.sys \
  data/btos/boot/initfs/ata.sys \
  data/btos/boot/initfs/spawn.elx \
  data/btos/boot/initfs/fat.sys \
  data/btos/boot/initfs/eloader.elx \

pkg-files:= $(shell find pkgfiles -type f)

all: ../$(output-name)

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

copy.grub: ../../3rdparty/install/btos/sbin/grub-bios-setup.elx ../../3rdparty/install/btos/bin/grub-mkimage.elx ../../3rdparty/install/btos/bin/grub-mklayout.elx ../../3rdparty/install/btos/bin/grub-mkrelpath.elx
	mkdir -p data/btos/boot/grub/
	cp -R ../../3rdparty/install/btos/lib/grub/i386-pc data/btos/boot/grub
	cp ../../3rdparty/install/btos/sbin/grub-bios-setup.elx data/btos/boot/grub/grubbios.elx
	cp ../../3rdparty/install/btos/bin/grub-mkimage.elx data/btos/boot/grub/grubmkim.elx
	cp ../../3rdparty/install/btos/bin/grub-mklayout.elx data/btos/boot/grub/grubmkla.elx
	cp ../../3rdparty/install/btos/bin/grub-mkrelpath.elx data/btos/boot/grub/grubmkrp.elx
	touch copy.grub

../$(output-name): $(import-files) $(pkg-files) copy.grub
	-cp -R pkgfiles/* data
	find data/btos/boot/initfs/ -name \*.elx -not -name eloader.elx -exec strip {} \;
	strip -K loaded_modules -K loaded_module_count data/btos/boot/initfs/eloader.elx
	strip -g data/btos/boot/initfs/*.sys
	tar cf ../$(output-name) -C data .

clean:
	-rm -rf data
	-rm ../$(output-name)
	-rm create.directories
