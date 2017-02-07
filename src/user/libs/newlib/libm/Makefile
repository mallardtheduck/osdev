LIBRARY-NAME := libm.ell
STATIC-NAME := libm.a

DESTINATION := $(HOME)/Projects/os/cross/i686-pc-btos

BUILD-AS := i686-pc-btos-gcc
BUILD-AR := i686-pc-btos-ar
BUILD-AS-OPTIONS := -g -c -fPIC -D_I386MACH_NEED_SOTYPE_FUNCTION
AR-FLAGS := rcs -o $(STATIC-NAME)
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c -fPIC -DINTERNAL_NEWLIB -D_COMPILING_NEWLIB -ffreestanding
BUILD-C-OPTIONS := -Wall -Wextra -g -c -I../../../../include -I../libc/include -I./common -std=gnu99
LINK := i686-pc-btos-gcc
LINK-FLAGS := -O2 -fPIC -shared -nodefaultlibs -ffreestanding
LINK-OPTIONS := -o $(LIBRARY-NAME)

FOLDERS := common complex machine mathfp
SKIP-FILES := mathfp/w_cabs.c mathfp/wf_cabs.c mathfp/sf_sin.c
SKIP-SPEC := $(shell printf "! -wholename %s " $(SKIP-FILES))

ASFILES := $(shell find $(FOLDERS) -type f -name "*.s" -or -name "*.S" $(SKIP-SPEC))
CFILES := $(shell find $(FOLDERS) -type f -name "*.c" $(SKIP-SPEC))

INCLUDE-FOLDERS := common

ASOBJS1 := $(ASFILES:.s=.o)
ASOBJS2 := $(ASOBJS1:.S=.o)
ASOBJS := $(ASOBJS2)
COBJS := $(CFILES:.c=.o)

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))

all: $(LIBRARY-NAME) $(STATIC-NAME) copy

-include $(CDEPFILES) $(CPPDEPFILES)

copy:
	mkdir -p $(DESTINATION)/lib
	cp -u $(LIBRARY-NAME) $(DESTINATION)/lib
	cp -u $(STATIC-NAME) $(DESTINATION)/lib

clean: dummy.delete

dummy.delete:
	-@find . -name \*.o -delete
	-@$(RM) $(LIBRARY-NAME)
	-@$(RM) $(STATIC-NAME)

$(LIBRARY-NAME): $(ASOBJS) $(COBJS) Makefile
	$(LINK) $(LINK-FLAGS) $(ASOBJS) $(COBJS) $(LINK-OPTIONS)

$(STATIC-NAME): $(ASOBJS) $(COBJS) Makefile
	$(BUILD-AR) $(AR-FLAGS) $(ASOBJS) $(COBJS)	

.s.o: %.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.S.o: %.S Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<)

