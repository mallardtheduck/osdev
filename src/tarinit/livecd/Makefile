init.tar: Makefile data/config.ini data/boot.sys data/ata.sys data/spawn.elx data/iso9660.sys data/eloader.elx data/stdpc.sys data/pcrtc.sys
	find data/ -name \*.elx -not -name eloader.elx -exec strip {} \;
	strip -K loaded_modules -K loaded_module_count data/eloader.elx
	strip -g data/*.sys
	tar -cvf $@ -C data/ `ls data/`

data/boot.sys: ../../modules/boot/boot.sys
	cp $< $@

data/pcrtc.sys: ../../modules/hwpnp/pcrtc/pcrtc.sys
	cp $< $@
	
data/stdpc.sys: ../../modules/hwpnp/stdpc/stdpc.sys
	cp $< $@

data/ata.sys: ../../modules/hwpnp/ata/ata.sys
	cp $< $@

data/spawn.elx: ../../user/system/spawn/spawn.elx
	cp $< $@

data/iso9660.sys: ../../modules/fs/iso9660/iso9660.sys
	cp $< $@

data/eloader.elx: ../../user/system/eloader/eloader.elx
	cp $< $@

clean: dummy.file
	find data/ -not -name config.ini -type f -exec rm {} \;
	-rm init.tar

dummy.file:
