OUTPUT-NAME := reg.elx
LIBRARY-NAME := registry.ell

DESTINATION := $(HOME)/Projects/os/cross/i686-pc-btos

BUILD-AS := i686-pc-btos-as
BUILD-AR := i686-pc-btos-ar
BUILD-AS-OPTIONS := -g -fPIC -c
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c -fPIC
BUILD-CPP-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu++1y
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c -fPIC
BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu99
LINK := i686-pc-btos-gcc
LINK-FLAGS := -o $(OUTPUT-NAME) -O2 -L. -L../libgds
LIB-LINK-FLAGS := -o $(LIBRARY-NAME) -O2 -fPIC -shared -L.
AR-FLAGS := rcs -o $(LIBRARY-NAME)
LINK-OPTIONS := -lregistry -lgcc_s -lstdc++ -lbtoscore -lm -lbtoslib
LIB-LINK-OPTIONS := -lgcc_s -lstdc++ -lbtoscore -lm

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp" -not -name "main.cpp")
MAINCPP := main.cpp

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

$(OUTPUT-NAME): $(LIBRARY-NAME) $(MAINOBJ) Makefile
	$(LINK) $(LINK-FLAGS) $(MAINOBJ) $(LINK-OPTIONS)

.s.o: %.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

.cpp.o: %.cpp Makefile
	$(BUILD-CPP) -MMD -MP $(BUILD-CPP-FLAGS) $< -o $@ $(BUILD-CPP-OPTIONS)
