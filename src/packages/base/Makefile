import-files:=\
 data/btos/tests/ctest.elx \
 data/btos/tests/cpptest.elx \
 data/btos/cmd/cmd.elx \
 data/btos/system/terminal.sys \
 data/btos/cmd/cls.elx \
 data/btos/cmd/termctl.elx \
 data/btos/system/switcher.elx \
 data/btos/cmd/spawn.elx \
 data/btos/cmd/kill.elx \
 data/btos/drivers/pci.sys \
 data/btos/cmd/load.elx \
 data/btos/tests/test.sys \
 data/btos/cmd/mount.elx \
 data/btos/tests/msgtest.elx \
 data/btos/tests/mousetest.elx \
 data/btos/drivers/vga.sys \
 data/btos/tests/vgatest.elx \
 data/btos/tests/fputest.elx \
 data/btos/system/gds.elx \
 data/btos/bin/debug.elx \
 data/btos/tests/crash.elx \
 data/btos/tests/gdstest.elx \
 data/btos/system/wm.elx \
 data/btos/tests/wmtest.elx \
 data/btos/bin/wmmenu.elx \
 data/btos/bin/startwm.elx \
 data/btos/bin/termwin.elx \
 data/btos/bin/breakout.elx \
 data/btos/cmd/sleep.elx \
 data/btos/cmd/tar.elx \
 data/btos/drivers/iso9660.sys \
 data/btos/drivers/fat.sys \
 data/btos/cmd/iconv.elx \
 data/btos/cmd/parted.elx \
 data/btos/cmd/format.elx \
 data/btos/bin/install.elx \
 data/btos/tests/shmtest.elx \
 data/btos/tests/elltest.elx \
 data/btos/tests/testlib.ell \
 data/btos/lib/libc.ell \
 data/btos/lib/libm.ell \
 data/btos/lib/stdc++.ell \
 data/btos/lib/libgcc_s.ell \
 data/btos/lib/libg.ell \
 data/btos/lib/gds.ell \
 data/btos/lib/wm.ell \
 data/btos/lib/libelf.ell \
 data/btos/lib/iconv.ell \
 data/btos/lib/uuid.ell \
 data/btos/lib/parted.ell \
 data/btos/tests/elldtest.elx \
 data/btos/lib/eloader.ell \
 data/btos/lib/udis86.ell \
 data/btos/cmd/kilo.elx \
 data/btos/lib/ansi.ell \
 data/btos/tests/nctest.elx \
 data/btos/share/terminfo \
 data/btos/lib/ncurses.ell \
 data/btos/lib/ncurses++.ell \
 data/btos/lib/gd.ell \
 data/btos/lib/freetype.ell \
 data/btos/fonts \
 data/btos/config/wm.ini \
 data/btos/lib/btoscore.ell \
 data/btos/lib/btoslib.ell \
 data/btos/system/session.elx \
 data/btos/config/sessions \
 
pkg-files:= $(shell find pkgfiles -type f)

.SUFFIXES:

all: ../base.tar

data/btos/tests/ctest.elx: ../../user/tests/ctest/ctest.elx create.directories
	cp $< $@

data/btos/tests/cpptest.elx: ../../user/tests/cpptest/cpptest.elx create.directories
	cp $< $@

data/btos/cmd/cmd.elx: ../../user/cmds/cmd/cmd.elx create.directories
	cp $< $@

data/btos/system/terminal.sys: ../../modules/terminal/terminal.sys create.directories
	cp $< $@

data/btos/cmd/cls.elx: ../../user/cmds/cls/cls.elx create.directories
	cp $< $@

data/btos/cmd/termctl.elx: ../../user/cmds/termctl/termctl.elx create.directories
	cp $< $@

data/btos/system/switcher.elx: ../../user/system/switcher/switcher.elx create.directories
	cp $< $@

data/btos/cmd/spawn.elx: ../../user/system/spawn/spawn.elx create.directories
	cp $< $@

data/btos/cmd/kill.elx: ../../user/cmds/kill/kill.elx create.directories
	cp $< $@

data/btos/drivers/pci.sys: ../../modules/pci/pci.sys create.directories
	cp $< $@

data/btos/cmd/load.elx: ../../user/cmds/load/load.elx create.directories
	cp $< $@

data/btos/tests/test.sys: ../../modules/test/test.sys create.directories
	cp $< $@

data/btos/cmd/mount.elx: ../../user/cmds/mount/mount.elx create.directories
	cp $< $@

data/btos/tests/msgtest.elx: ../../user/tests/msgtest/msgtest.elx create.directories
	cp $< $@

data/btos/tests/mousetest.elx: ../../user/tests/mousetest/mousetest.elx create.directories
	cp $< $@

data/btos/drivers/vga.sys: ../../modules/vga/vga.sys create.directories
	cp $< $@

data/btos/tests/vgatest.elx: ../../user/tests/vgatest/vgatest.elx create.directories
	cp $< $@

data/btos/bin/debug.elx: ../../user/bin/debug/debug.elx create.directories
	cp $< $@

data/btos/tests/crash.elx: ../../user/tests/crash/crash.elx create.directories
	cp $< $@

data/btos/system/gds.elx: ../../user/system/gds/gds.elx create.directories
	cp $< $@
	
data/btos/tests/gdstest.elx: ../../user/libs/libgds/gdstest.elx create.directories
	cp $< $@

data/btos/tests/fputest.elx: ../../user/tests/fputest/fputest.elx create.directories
	cp $< $@
	
data/btos/system/wm.elx: ../../user/system/wm/wm.elx create.directories
	cp $< $@
	
data/btos/tests/wmtest.elx: ../../user/libs/libwm/wmtest.elx create.directories
	cp $< $@
	
data/btos/bin/wmmenu.elx: ../../user/wmapps/wmmenu/wmmenu.elx create.directories
	cp $< $@

data/btos/bin/startwm.elx: ../../user/bin/startwm/startwm.elx create.directories
	cp $< $@

data/btos/bin/termwin.elx: ../../user/wmapps/termwin/termwin.elx create.directories
	cp $< $@

data/btos/bin/breakout.elx: ../../user/wmapps/breakout/breakout.elx create.directories
	cp $< $@

data/btos/cmd/sleep.elx: ../../user/cmds/sleep/sleep.elx create.directories
	cp $< $@

data/btos/cmd/tar.elx: ../../user/cmds/tar/tar.elx create.directories
	cp $< $@

data/btos/drivers/iso9660.sys: ../../modules/iso9660/iso9660.sys create.directories
	cp $< $@

data/btos/drivers/fat.sys: ../../modules/fat/fat.sys create.directories
	cp $< $@

data/btos/cmd/iconv.elx: ../../3rdparty/install/btos/bin/iconv.elx create.directories
	cp $< $@

data/btos/cmd/parted.elx: ../../3rdparty/install/btos/sbin/parted.elx create.directories
	cp $< $@

data/btos/cmd/format.elx: ../../user/cmds/format/format.elx create.directories
	cp $< $@
	
data/btos/bin/install.elx: ../../user/bin/install/install.elx create.directories
	cp $< $@
	
data/btos/tests/shmtest.elx: ../../user/tests/shmtest/shmtest.elx create.directories
	cp $< $@

data/btos/tests/elltest.elx: ../../user/tests/elltest/elltest.elx create.directories
	cp $< $@

data/btos/tests/testlib.ell: ../../user/tests/elltest/testlib.ell create.directories
	cp $< $@

data/btos/lib/libc.ell: ../../user/libs/newlib/libc/libc.ell
	cp $< $@

data/btos/lib/libm.ell: ../../user/libs/newlib/libm/libm.ell
	cp $< $@

data/btos/lib/stdc++.ell: ../../../cross/i686-pc-btos/lib/stdc++.ell
	cp $< $@

data/btos/lib/libgcc_s.ell: ../../../cross/i686-pc-btos/lib/libgcc_s.ell
	cp $< $@

data/btos/lib/libg.ell: ../../user/libs/newlib/libc/libg.ell
	cp $< $@
	
data/btos/lib/gds.ell: ../../user/libs/libgds/gds.ell
	cp $< $@

data/btos/lib/wm.ell: ../../user/libs/libwm/wm.ell
	cp $< $@

data/btos/lib/libelf.ell: ../../3rdparty/install/btos/lib/libelf.ell
	cp $< $@

data/btos/lib/iconv.ell: ../../3rdparty/install/btos/lib/iconv.ell
	cp $< $@

data/btos/lib/uuid.ell: ../../3rdparty/install/btos/lib/uuid.ell
	cp $< $@

data/btos/lib/parted.ell: ../../3rdparty/install/btos/lib/parted.ell
	cp $< $@

data/btos/lib/eloader.ell: ../../user/libs/eloader/eloader.ell
	cp $< $@

data/btos/tests/elldtest.elx: ../../user/libs/eloader/elldtest.elx
	cp $< $@

data/btos/lib/udis86.ell: ../../3rdparty/install/btos/lib/udis86.ell
	cp $< $@

data/btos/cmd/redit.elx: ../../user/cmds/rockedit/redit.elx
	cp $< $@

data/btos/cmd/kilo.elx: ../../user/cmds/kilo/kilo.elx
	cp $< $@

data/btos/lib/ansi.ell: ../../user/libs/ansi/ansi.ell
	cp $< $@

data/btos/tests/nctest.elx: ../../user/tests/nctest/nctest.elx
	cp $< $@

data/btos/share/terminfo: ../../3rdparty/install/btos/share/terminfo
	mkdir -p $@
	cp -Rv $</* $@

data/btos/lib/ncurses.ell: ../../3rdparty/install/btos/lib/ncurses.ell
	cp $< $@

data/btos/lib/ncurses++.ell: ../../3rdparty/install/btos/lib/ncurses++.ell
	cp $< $@

data/btos/lib/gd.ell: ../../3rdparty/install/btos/lib/gd.ell
	cp $< $@

data/btos/lib/freetype.ell: ../../3rdparty/install/btos/lib/freetype.ell
	cp $< $@

data/btos/fonts: ../../user/system/gds/fonts
	mkdir -p $@
	cp -Rv $</* $@

data/btos/config/wm.ini: ../../user/system/wm/wm.ini
	cp $< $@

data/btos/lib/btoscore.ell: ../../user/libs/btoscore/btoscore.ell
	cp $< $@

data/btos/lib/btoslib.ell: ../../user/libs/btoslib/btoslib.ell
	cp $< $@

data/btos/system/session.elx: ../../user/system/sm/session.elx
	cp $< $@

data/btos/config/sessions: ../../user/system/sm/sessions
	mkdir -p $@
	cp -Rv $</* $@

copy.grub: ../../3rdparty/install/btos/sbin/grub-bios-setup.elx ../../3rdparty/install/btos/bin/grub-mkimage.elx ../../3rdparty/install/btos/bin/grub-mklayout.elx ../../3rdparty/install/btos/bin/grub-mkrelpath.elx
	mkdir -p data/btos/boot/grub/
	cp -R ../../3rdparty/install/btos/lib/grub/i386-pc data/btos/boot/grub
	cp ../../3rdparty/install/btos/sbin/grub-bios-setup.elx data/btos/boot/grub/grubbios.elx
	cp ../../3rdparty/install/btos/bin/grub-mkimage.elx data/btos/boot/grub/grubmkim.elx
	cp ../../3rdparty/install/btos/bin/grub-mklayout.elx data/btos/boot/grub/grubmkla.elx
	cp ../../3rdparty/install/btos/bin/grub-mkrelpath.elx data/btos/boot/grub/grubmkrp.elx
	touch copy.grub

create.directories: Makefile
	mkdir -p data/btos/cmd
	mkdir -p data/btos/temp
	mkdir -p data/btos/tests
	mkdir -p data/btos/bin
	mkdir -p data/btos/system
	mkdir -p data/btos/drivers
	mkdir -p data/btos/lib
	mkdir -p data/btos/share
	mkdir -p data/btos/config
	touch create.directories

../base.tar: $(import-files) $(pkg-files) copy.grub
	#cp -R pkgfiles/* data
	tar cf ../base.tar -C data .

clean:
	-rm -rf data
	-rm ../base.tar
	-rm create.directories
	-rm copy.grub
