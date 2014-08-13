BUILD-AS := i686-elf-as
BUILD-AS-OPTIONS := -g
BUILD-CPP := i686-elf-g++
BUILD-CPP-FLAGS :=  -c
BUILD-CPP-OPTIONS := -ffreestanding -O2 -Wall -Wextra -Werror -fno-exceptions -fno-rtti -g -I../include -DKERNEL
BUILD-C := i686-elf-gcc
BUILD-C-FLAGS := -c
BUILD-C-OPTIONS := -ffreestanding -O2 -Wall -Wextra -Werror -g -I../include -DKERNEL
LINK := i686-elf-gcc
LINK-FLAGS := -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib -g
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

all: myos.iso Makefile

-include $(CDEPFILES) $(CPPDEPFILES)

clean: dummy.delete

rebuild: clean all

dummy.delete:
	-@$(RM) *.o
	-@$(RM) myos.iso
	-@$(RM) myos.bin
	-@$(RM) initfs/xxd_data.inc
	make -C initfs clean

myos.iso: myos.bin
	@mkdir -p isodir
	@mkdir -p isodir/boot
	@cp myos.bin isodir/boot/myos.bin
	@mkdir -p isodir/boot/grub
	@cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir

initfs/initfs_data.cpp: initfs/initfs_data.inc

initfs/initfs_data.inc:
	$(MAKE) -C initfs

myos.bin: boot.o $(ASOBJS) $(COBJS) $(CPPOBJS) linker.ld
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
