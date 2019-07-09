OUTPUT-NAME := rescutil.elx
RESC-TAR-NAME := rescutil_resc.tar
RESC-VAR-NAME := rescutil_resc

BUILD-AS := i686-pc-btos-as
BUILD-AS-OPTIONS := -g -fPIC -c
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c -std=gnu++11
BUILD-CPP-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c
BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu99
LINK := i686-pc-btos-gcc
LINK-FLAGS := -o $(OUTPUT-NAME) -O2
LINK-OPTIONS := -Wl,-rpath-link,../../../3rdparty/install/btos/lib -lgcc_s -lstdc++ -lbtoscore -lbtoslib -lresc

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp")
RESCFILES := $(shell find resc -type f)

ASOBJS := $(ASFILES:.s=.o)
COBJS := $(CFILES:.c=.o)
CPPOBJS := $(CPPFILES:.cpp=.o)

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))

all: $(OUTPUT-NAME)

-include $(CDEPFILES) $(CPPDEPFILES)

clean: dummy.delete

dummy.delete:
	-@$(RM) *.o
	-@$(RM) $(OUTPUT-NAME)

$(OUTPUT-NAME): $(ASOBJS) $(COBJS) $(CPPOBJS) Makefile $(RESC-TAR-NAME).o
	$(LINK) $(LINK-FLAGS) $(ASOBJS) $(CPPOBJS) $(COBJS) $(RESC-TAR-NAME).o $(LINK-OPTIONS)

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