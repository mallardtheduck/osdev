output-name := base.pkf

import-files:=\
 data/btos/cmd/cmd.elx \
 data/btos/system/terminal.sys \
 data/btos/cmd/cls.elx \
 data/btos/cmd/termctl.elx \
 data/btos/system/switcher.elx \
 data/btos/cmd/spawn.elx \
 data/btos/cmd/kill.elx \
 data/btos/drivers/pci.sys \
 data/btos/cmd/load.elx \
 data/btos/cmd/mount.elx \
 data/btos/drivers/vga.sys \
 data/btos/system/gds.elx \
 data/btos/bin/debug.elx \
 data/btos/system/wm.elx \
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
 data/btos/lib/eloader.ell \
 data/btos/lib/udis86.ell \
 data/btos/cmd/kilo.elx \
 data/btos/lib/ansi.ell \
 data/btos/share/terminfo \
 data/btos/lib/ncurses.ell \
 data/btos/lib/ncurses++.ell \
 data/btos/lib/form.ell \
 data/btos/lib/panel.ell \
 data/btos/lib/menu.ell \
 data/btos/lib/gd.ell \
 data/btos/lib/freetype.ell \
 data/btos/fonts \
 data/btos/config/wm.ini \
 data/btos/lib/btoscore.ell \
 data/btos/lib/btoslib.ell \
 data/btos/system/session.elx \
 data/btos/system/sessions \
 data/btos/lib/sm.ell \
 data/btos/cmd/smutil.elx \
 data/btos/lib/cmd.ell \
 data/btos/lib/sqlite3.ell \
 data/btos/bin/sqlite.elx \
 data/btos/cmd/ini.elx \
 data/btos/system/registry.elx \
 data/btos/lib/registry.ell \
 data/btos/cmd/reg.elx \
 data/btos/cmd/package.elx \
 data/btos/lib/SDL2.ell \
 data/btos/lib/SDL2_ttf.ell \
 data/btos/lib/SDL2_image.ell \
 data/btos/lib/SDL2_ttf.ell \
 data/btos/lib/SDL2_widgets.ell \
 
pkg-files:= $(shell find pkgfiles -type f)

.SUFFIXES:

all: ../$(output-name)

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

data/btos/drivers/pci.sys: ../../modules/hwpnp/pci/pci.sys create.directories
	cp $< $@

data/btos/cmd/load.elx: ../../user/cmds/load/load.elx create.directories
	cp $< $@

data/btos/cmd/mount.elx: ../../user/cmds/mount/mount.elx create.directories
	cp $< $@

data/btos/drivers/vga.sys: ../../modules/vga/vga.sys create.directories
	cp $< $@

data/btos/bin/debug.elx: ../../user/bin/debug/debug.elx create.directories
	cp $< $@

data/btos/system/gds.elx: ../../user/system/gds/gds.elx create.directories
	cp $< $@
	
data/btos/system/wm.elx: ../../user/system/wm/wm.elx create.directories
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

data/btos/lib/udis86.ell: ../../3rdparty/install/btos/lib/udis86.ell
	cp $< $@

data/btos/cmd/redit.elx: ../../user/cmds/rockedit/redit.elx
	cp $< $@

data/btos/cmd/kilo.elx: ../../user/cmds/kilo/kilo.elx
	cp $< $@

data/btos/lib/ansi.ell: ../../user/libs/ansi/ansi.ell
	cp $< $@

data/btos/share/terminfo: ../../3rdparty/install/btos/share/terminfo
	mkdir -p $@
	cp -Rv $</* $@

data/btos/lib/ncurses.ell: ../../3rdparty/install/btos/lib/ncurses.ell
	cp $< $@

data/btos/lib/ncurses++.ell: ../../3rdparty/install/btos/lib/ncurses++.ell
	cp $< $@

data/btos/lib/form.ell: ../../3rdparty/install/btos/lib/form.ell
	cp $< $@

data/btos/lib/panel.ell: ../../3rdparty/install/btos/lib/panel.ell
	cp $< $@

data/btos/lib/menu.ell: ../../3rdparty/install/btos/lib/menu.ell
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

data/btos/system/sessions: ../../user/system/sm/sessions
	mkdir -p $@
	cp -Rv $</* $@

data/btos/lib/sm.ell : ../../user/libs/sm/sm.ell
	cp $< $@

data/btos/cmd/smutil.elx : ../../user/libs/sm/smutil.elx
	cp $< $@

data/btos/lib/cmd.ell: ../../user/libs/cmd/cmd.ell
	cp $< $@

data/btos/lib/sqlite3.ell: ../../3rdparty/install/btos/lib/sqlite3.ell
	cp $< $@

data/btos/bin/sqlite.elx: ../../3rdparty/install/btos/bin/sqlite.elx
	cp $< $@

data/btos/cmd/ini.elx: ../../user/cmds/ini/ini.elx
	cp $< $@

data/btos/system/registry.elx: ../../user/system/registry/registry.elx
	cp $< $@

data/btos/lib/registry.ell: ../../user/libs/registry/registry.ell
	cp $< $@

data/btos/cmd/reg.elx: ../../user/libs/registry/reg.elx
	cp $< $@

data/btos/cmd/package.elx: ../../user/cmds/package/package.elx
	cp $< $@

data/btos/lib/SDL2.ell: ../../3rdparty/install/btos/lib/SDL2.ell
	cp $< $@

data/btos/lib/SDL2_ttf.ell: ../../3rdparty/install/btos/lib/SDL2_ttf.ell
	cp $< $@

data/btos/lib/SDL2_image.ell: ../../3rdparty/install/btos/lib/SDL2_image.ell
	cp $< $@

data/btos/lib/SDL2_widgets.ell: ../../3rdparty/install/btos/lib/SDL2_widgets.ell
	cp $< $@

create.directories: Makefile
	mkdir -p data/btos/cmd
	mkdir -p data/btos/temp
	mkdir -p data/btos/bin
	mkdir -p data/btos/system
	mkdir -p data/btos/drivers
	mkdir -p data/btos/lib
	mkdir -p data/btos/share
	mkdir -p data/btos/config
	touch create.directories

../$(output-name): $(import-files) $(pkg-files)
	cp -Rv pkgfiles/* data
	tar cf ../$(output-name) -C data .

clean:
	-rm -rf data
	-rm ../$(output-name)
	-rm create.directories
	-rm copy.grub
