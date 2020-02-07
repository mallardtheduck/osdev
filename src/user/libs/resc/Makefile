OUTPUT-NAME := resctest.elx
LIBRARY-NAME := resc.ell
RESC-TAR-NAME := resctest_resc.tar
RESC-VAR-NAME := resctest_resc

DESTINATION := $(HOME)/Projects/os/cross/i686-pc-btos

BUILD-AS := i686-pc-btos-as
BUILD-AR := i686-pc-btos-ar
BUILD-AS-OPTIONS := -g -fPIC -c
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c -fPIC
BUILD-CPP-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -I../../../3rdparty/install/btos/include -std=gnu++11
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c -fPIC
BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu99
LINK := i686-pc-btos-gcc
LINK-FLAGS := -o $(OUTPUT-NAME) -O2 -L. -L../libgds
LIB-LINK-FLAGS := -o $(LIBRARY-NAME) -O2 -fPIC -shared -L. -L../libgds -L../libwm
AR-FLAGS := rcs -o $(LIBRARY-NAME)
LINK-OPTIONS := -Wl,-rpath-link,../../../3rdparty/install/btos/lib -lresc -lgcc_s -lstdc++ -lbtoscore -lm -lbtoslib
LIB-LINK-OPTIONS := -L../../../3rdparty/install/btos/lib -lgcc_s -lstdc++ -lbtoscore -lbtoslib -lm

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp" -not -name "main.cpp")
MAINCPP := main.cpp
RESCFILES := $(shell find resc -type f)

ASOBJS := $(ASFILES:.s=.o)
COBJS := $(CFILES:.c=.o)
CPPOBJS := $(CPPFILES:.cpp=.o)
MAINOBJ := $(MAINCPP:.cpp=.o)

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))

all: $(OUTPUT-NAME) copy

-include $(CDEPFILES) $(CPPDEPFILES)

copy: $(LIBRARY-NAME)
	mkdir -p $(DESTINATION)/lib
	cp -u $(LIBRARY-NAME) $(DESTINATION)/lib

clean: dummy.delete

dummy.delete:
	-@$(RM) *.o
	-@$(RM) $(OUTPUT-NAME)
	-@$(RM) $(LIBRARY-NAME)

$(LIBRARY-NAME): $(ASOBJS) $(COBJS) $(CPPOBJS) Makefile
	$(LINK) $(LIB-LINK-FLAGS) $(ASOBJS) $(CPPOBJS) $(COBJS) $(LIB-LINK-OPTIONS)

$(OUTPUT-NAME): $(LIBRARY-NAME) $(MAINOBJ) Makefile resctest_resc.tar.o
	$(LINK) $(LINK-FLAGS) $(MAINOBJ) resctest_resc.tar.o $(LINK-OPTIONS)

.s.o: %.s
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

.cpp.o: %.cpp
	$(BUILD-CPP) -MMD -MP $(BUILD-CPP-FLAGS) $< -o $@ $(BUILD-CPP-OPTIONS)

$(CPPOBJS) $(COBJS) $(MAINOBJ) $(ASOBJS): Makefile
$(CPPOBJS) $(COBJS) $(MAINOBJ): $(RESC-TAR-NAME).h

$(RESC-TAR-NAME).h $(RESC-TAR-NAME).o: $(RESC-TAR-NAME)
	../../../scripts/elfembed.sh $(RESC-TAR-NAME) resc $(RESC-VAR-NAME)
	
$(RESC-TAR-NAME): $(RESCFILES)
	tar cf $@ -C resc .