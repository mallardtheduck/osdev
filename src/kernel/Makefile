BUILD-AS := i686-pc-btos-as
BUILD-AS-OPTIONS := -g
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c
BUILD-CPP-OPTIONS := -ffreestanding -O2 -Wall -Wextra -Werror -fno-exceptions -fno-rtti -g -I../include -DKERNEL -std=gnu++11
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c
BUILD-C-OPTIONS := -ffreestanding -O2 -Wall -Wextra -Werror -g -I../include -DKERNEL
LINK := i686-pc-btos-gcc
LINK-FLAGS := -T linker.ld -o btos.bin -ffreestanding -O2 -nostdlib -g
LINK-OPTIONS := -lgcc

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s" -not -name boot.s)
CFILES := $(shell find . -type f -name "*.c" -not -name buildid.c) buildid.c
CPPFILES := $(shell find . -type f -name "*.cpp")

ASOBJS := $(ASFILES:.s=.o)
COBJS := $(CFILES:.c=.o)
CPPOBJS := $(CPPFILES:.cpp=.o)

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))

all: btos.iso Makefile

-include $(CDEPFILES) $(CPPDEPFILES)

clean: dummy.delete

rebuild: clean all

dummy.delete:
	-@$(RM) *.o
	-@$(RM) btos.iso
	-@$(RM) btos.bin
	-@$(RM) initfs/xxd_data.inc
	make -C initfs clean

btos.iso: btos.bin
	@mkdir -p isodir
	@mkdir -p isodir/boot
	@cp btos.bin isodir/boot/btos.bin
	@mkdir -p isodir/boot/grub
	@cp grub.cfg isodir/boot/grub/grub.cfg
	@mkdir -p isodir/boot/grub/i386-pc
	cp -r /usr/lib/grub/i386-pc/* isodir/boot/grub/i386-pc
	rm isodir/boot/grub/i386-pc/*.img
	grub-mkimage -O i386-pc -d /usr/lib/grub/i386-pc -o core.img -c load_cfg --prefix=/boot/grub iso9660 biosdisk
	cat /usr/lib/grub/i386-pc/cdboot.img core.img > isodir/boot/grub/i386-pc/eltorito.img
	cat /usr/lib/grub/i386-pc/boot.img core.img > embedded.img
	xorriso -report_about HINT -as mkisofs -graft-points -b boot/grub/i386-pc/eltorito.img -no-emul-boot -boot-info-table --embedded-boot embedded.img --protective-msdos-label -o btos.iso -r isodir --sort-weight 0 / --sort-weight 1 /boot
	

initfs/initfs_data.cpp: initfs/initfs_data.inc

initfs/initfs_data.inc:
	$(MAKE) -C initfs

btos.bin: boot.o $(ASOBJS) $(COBJS) $(CPPOBJS) linker.ld
	$(LINK) $(LINK-FLAGS) boot.o $(ASOBJS) $(CPPOBJS) $(COBJS) $(LINK-OPTIONS)

boot.o: boot.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.s.o: %.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

.cpp.o: %.cpp Makefile
	$(BUILD-CPP) -MMD -MP $(BUILD-CPP-FLAGS) $< -o $@ $(BUILD-CPP-OPTIONS)

buildid.c: dummy.file
	./buildid.sh

dummy.file:
