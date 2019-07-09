OUTPUT-NAME := shelltest.elx
LIBRARY-NAME := shell.ell
RESC-TAR-NAME := shelltest_resc.tar
RESC-VAR-NAME := shelltest_resc
LIBRESC-TAR-NAME := shell_resc.tar
LIBRESC-VAR-NAME := shell_resc

DESTINATION := $(HOME)/Projects/os/cross/i686-pc-btos

BUILD-AS := i686-pc-btos-as
BUILD-AR := i686-pc-btos-ar
BUILD-AS-OPTIONS := -g -fPIC -c
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c -fPIC
BUILD-CPP-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu++11
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c -fPIC
BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu99
LINK := i686-pc-btos-gcc
LINK-FLAGS := -o $(OUTPUT-NAME) -O2 -L. -L../libgds
LIB-LINK-FLAGS := -o $(LIBRARY-NAME) -O2 -fPIC -shared -L. -L../libgds -L../libwm
AR-FLAGS := rcs -o $(LIBRARY-NAME)
LINK-OPTIONS := -Wl,-rpath-link,../../../3rdparty/install/btos/lib -lgds -lwm -lgui -lgcc_s -lstdc++ -lbtoscore -lm -lbtoslib -lresc -lshell
LIB-LINK-OPTIONS := -Wl,-rpath-link,../../../3rdparty/install/btos/lib -lgds -lwm -lgcc_s -lstdc++ -lbtoscore -lbtoslib -lm -lresc

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp" -not -name "main.cpp")
MAINCPP := main.cpp
RESCFILES := $(shell find resc -type f)
LIBRESCFILES := $(shell find libresc -type f)

ASOBJS := $(ASFILES:.s=.o)
COBJS := $(CFILES:.c=.o)
CPPOBJS := $(CPPFILES:.cpp=.o)
MAINOBJ := $(MAINCPP:.cpp=.o)

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))
MAINDEPFILE := $(patsubst %.cpp,%.d,$(MAINCPP))

all: $(OUTPUT-NAME) copy

include libresc.mk

-include $(CDEPFILES) $(CPPDEPFILES) $(MAINDEPFILE)

copy: $(LIBRARY-NAME)
	mkdir -p $(DESTINATION)/lib
	cp -u $(LIBRARY-NAME) $(DESTINATION)/lib

clean: dummy.delete

dummy.delete:
	-@$(RM) *.o
	-@$(RM) $(OUTPUT-NAME)

$(LIBRARY-NAME): $(ASOBJS) $(COBJS) $(CPPOBJS) $(LIBRESC-TAR-NAME).o Makefile
	$(LINK) $(LIB-LINK-FLAGS) $(ASOBJS) $(CPPOBJS) $(COBJS) $(LIBRESC-TAR-NAME).o $(LIB-LINK-OPTIONS)

$(OUTPUT-NAME): $(MAINOBJ) $(LIBRARY-NAME) $(RESC-TAR-NAME).o Makefile
	$(LINK) $(LINK-FLAGS) $(MAINOBJ) $(RESC-TAR-NAME).o $(LINK-OPTIONS)

.s.o: %.s
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

.cpp.o: %.cpp
	$(BUILD-CPP) -MMD -MP $(BUILD-CPP-FLAGS) $< -o $@ $(BUILD-CPP-OPTIONS)

$(CPPOBJS) $(COBJS) $(MAINOBJ) $(ASOBJS): Makefile
$(CPPOBJS) $(COBJS): $(LIBRESC-TAR-NAME).h
$(MAINOBJ): $(RESC-TAR-NAME).h

$(RESC-TAR-NAME).h $(RESC-TAR-NAME).o: $(RESC-TAR-NAME)
	../../../scripts/elfembed.sh $(RESC-TAR-NAME) resc $(RESC-VAR-NAME)
	
$(RESC-TAR-NAME): $(RESCFILES) Makefile
	tar cf $@ -C resc .
	
$(LIBRESC-TAR-NAME).h $(LIBRESC-TAR-NAME).o: $(LIBRESC-TAR-NAME)
	../../../scripts/elfembed.sh $(LIBRESC-TAR-NAME) resc $(LIBRESC-VAR-NAME)
	
$(LIBRESC-TAR-NAME): $(LIBRESCFILES) Makefile
	tar cf $@ -C libresc .
