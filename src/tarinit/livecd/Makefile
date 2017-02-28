init.tar: Makefile data/config.ini data/boot.sys data/rtc.sys data/ps2.sys data/ata.sys data/spawn.elx data/iso9660.sys data/eloader.elx
	strip data/*.elx
	strip -g data/*.sys
	tar -cvf $@ -C data/ `ls data/`

data/boot.sys: ../../modules/boot/boot.sys
	cp $< $@

data/rtc.sys: ../../modules/rtc/rtc.sys
	cp $< $@

data/ps2.sys: ../../modules/ps2/ps2.sys
	cp $< $@

data/ata.sys: ../../modules/ata/ata.sys
	cp $< $@

data/spawn.elx: ../../user/system/spawn/spawn.elx
	cp $< $@

data/iso9660.sys: ../../modules/iso9660/iso9660.sys
	cp $< $@

data/eloader.elx: ../../user/system/eloader/eloader.elx
	cp $< $@

clean: dummy.file
	find data/ -not -name config.ini -type f -exec rm {} \;
	-rm init.tar

dummy.file:
