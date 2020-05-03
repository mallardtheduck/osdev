BUILD-AS := i686-pc-btos-as
BUILD-AS-OPTIONS := -g
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c
BUILD-CPP-OPTIONS := -ffreestanding -Og -Wall -Wextra -Werror -fno-exceptions -fno-rtti -g -I../include -DKERNEL -std=gnu++11
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c
BUILD-C-OPTIONS := -ffreestanding -Og -Wall -Wextra -Werror -g -I../include -DKERNEL
LINK := i686-pc-btos-gcc
LINK-FLAGS := -T linker.ld -o btos.bin -ffreestanding -Og -nostdlib -g
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

all: btos.bin Makefile

-include $(CDEPFILES) $(CPPDEPFILES)

clean: dummy.delete

rebuild: clean all

dummy.delete:
	-@$(RM) *.o
	-@$(RM) mm2/*.o
	-@$(RM) hwpnp/*.o
	-@$(RM) rtc/*.o
	-@$(RM) btos.bin

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

buildid.c: ../../.git/HEAD ../../.git/index
	./buildid.sh

dummy.file:
