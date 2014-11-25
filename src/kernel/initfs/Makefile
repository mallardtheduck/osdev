xxd_data.inc: data/config.ini data/boot.sys data/rtc.sys data/keyboard.sys data/ata.sys data/fat.sys data/spawn.elx
	strip data/*.elx
	strip -g data/*.sys
	./make_inc.sh

data/boot.sys: ../../modules/boot/boot.sys
	cp $< $@

data/rtc.sys: ../../modules/rtc/rtc.sys
	cp $< $@

data/fat.sys: ../../modules/fat/fat.sys
	cp $< $@

data/keyboard.sys: ../../modules/keyboard/keyboard.sys
	cp $< $@

data/ata.sys: ../../modules/ata/ata.sys
	cp $< $@

data/spawn.elx: ../../user/spawn/spawn.elx
	cp $< $@

clean: dummy.file
	find data/ -not -name config.ini -type f -exec rm {} \;

dummy.file:
