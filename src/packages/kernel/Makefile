output-name := kernel.pkf

import-files:= \
  data/content/btos.bin \
  data/content/initfs/boot.sys \
  data/content/initfs/pcrtc.sys \
  data/content/initfs/stdpc.sys \
  data/content/initfs/ata.sys \
  data/content/initfs/spawn.elx \
  data/content/initfs/fatfs.sys \
  data/content/initfs/eloader.elx \
  data/content/grub/splash.tga \
  data/content/grub/grub.pf2 \

pkg-files:= $(shell find pkgfiles -type f)

all: ../$(output-name)

data/content/btos.bin: ../../kernel/btos.bin create.directories
	cp $< $@

data/content/initfs/boot.sys: ../../modules/boot/boot.sys create.directories
	cp $< $@

data/content/initfs/pcrtc.sys: ../../modules/hwpnp/pcrtc/pcrtc.sys create.directories
	cp $< $@

data/content/initfs/stdpc.sys: ../../modules/hwpnp/stdpc/stdpc.sys create.directories
	cp $< $@

data/content/initfs/ata.sys: ../../modules/hwpnp/ata/ata.sys create.directories
	cp $< $@

data/content/initfs/spawn.elx: ../../user/system/spawn/spawn.elx create.directories
	cp $< $@

data/content/initfs/fatfs.sys: ../../modules/fs/fatfs/fatfs.sys create.directories
	cp $< $@

data/content/initfs/eloader.elx: ../../user/system/eloader/eloader.elx create.directories
	cp $< $@
	
data/content/grub/splash.tga: ../../../other/art/splash.tga copy.grub
	cp $< $@

data/content/grub/grub.pf2: ../../../other/art/grub.pf2 copy.grub
	cp $< $@

create.directories:
	mkdir -p data/content/initfs
	touch create.directories

copy.grub: ../../3rdparty/install/btos/sbin/grub-bios-setup.elx ../../3rdparty/install/btos/bin/grub-mkimage.elx ../../3rdparty/install/btos/bin/grub-mklayout.elx ../../3rdparty/install/btos/bin/grub-mkrelpath.elx
	mkdir -p data/content/grub/
	cp -R ../../3rdparty/install/btos/lib/grub/i386-pc data/content/grub
	cp ../../3rdparty/install/btos/sbin/grub-bios-setup.elx data/content/grub/grubbios.elx
	cp ../../3rdparty/install/btos/bin/grub-mkimage.elx data/content/grub/grubmkim.elx
	cp ../../3rdparty/install/btos/bin/grub-mklayout.elx data/content/grub/grubmkla.elx
	cp ../../3rdparty/install/btos/bin/grub-mkrelpath.elx data/content/grub/grubmkrp.elx
	touch copy.grub

../$(output-name): $(import-files) $(pkg-files) copy.grub
	-cp -R pkgfiles/* data
	find data/content/initfs/ -name \*.elx -not -name eloader.elx -exec strip {} \;
	strip -K loaded_modules -K loaded_module_count data/content/initfs/eloader.elx
	strip -g data/content/initfs/*.sys
	tar cf ../$(output-name) -C data .

clean:
	-rm -rf data
	-rm ../$(output-name)
	-rm create.directories
	-rm copy.grub
