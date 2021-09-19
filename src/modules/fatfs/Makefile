OUTPUT := fatfs.sys

BUILD-AS := i686-pc-btos-as
BUILD-AS-OPTIONS := -g -fPIC -c
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c
BUILD-CPP-OPTIONS := -ffreestanding -Wall -Wextra -Werror -fno-exceptions -fno-rtti -std=gnu++11 -g -c -I../../include -DKERNEL_MODULE -std=gnu++17
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c
BUILD-C-OPTIONS := -ffreestanding -Wall -Wextra -Werror -g -c -I../../include -DKERNEL_MODULE
LINK := i686-pc-btos-gcc
LINK-FLAGS := -T linker.ld -o $(OUTPUT) -ffreestanding -O2 -nostdlib -fPIC -Xlinker -q
LINK-OPTIONS := -lgcc

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp")

ASOBJS := $(ASFILES:.s=.o)
COBJS := $(CFILES:.c=.o)
CPPOBJS := $(CPPFILES:.cpp=.o)

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))

all: $(OUTPUT)

-include $(CDEPFILES) $(CPPDEPFILES)

clean: dummy.delete

dummy.delete:
	-@$(RM) *.o
	-@$(RM) $(OUTPUT)

$(OUTPUT): $(ASOBJS) $(COBJS) $(CPPOBJS) linker.ld Makefile
	$(LINK) $(LINK-FLAGS) $(ASOBJS) $(CPPOBJS) $(COBJS) $(LINK-OPTIONS)

.s.o: %.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

.cpp.o: %.cpp Makefile
	$(BUILD-CPP) -MMD -MP $(BUILD-CPP-FLAGS) $< -o $@ $(BUILD-CPP-OPTIONS)
