LIBRARY-NAME := btoscore.ell
STATIC-LIBRARY-NAME := libbtoscore.a

DESTINATION := $(HOME)/Projects/os/cross/i686-pc-btos

BUILD-AS := i686-pc-btos-as
BUILD-AR := i686-pc-btos-ar
BUILD-AS-OPTIONS := -g -fPIC -c
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c
BUILD-CPP-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu++11
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c
BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu99
LINK := i686-pc-btos-gcc
LIB-LINK-FLAGS := -o $(LIBRARY-NAME) -O2 -fPIC -shared -L.
AR-FLAGS := rcs -o $(STATIC-LIBRARY-NAME)
LINK-OPTIONS := -lgcc_s 
LIB-LINK-OPTIONS := -lgcc_s 

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp" -not -name "main.cpp")

ASOBJS := $(ASFILES:.s=.o)
COBJS := $(CFILES:.c=.o)
CPPOBJS := $(CPPFILES:.cpp=.o)
MAINOBJ := $(MAINCPP:.cpp=.o)
STATIC-COBJS := $(STATIC-FILES:.c=.o)

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))

all: copy

copy: $(LIBRARY-NAME) $(STATIC-LIBRARY-NAME)
	mkdir -p $(DESTINATION)/lib
	cp -u $(LIBRARY-NAME) $(DESTINATION)/lib
	cp -u $(STATIC-LIBRARY-NAME) $(DESTINATION)/lib

-include $(CDEPFILES) $(CPPDEPFILES)

clean: dummy.delete

dummy.delete:
	-@$(RM) *.o
	-@$(RM) $(LIBRARY-NAME)
	-@$(RM) $(STATIC-LIBRARY-NAME)


$(LIBRARY-NAME): $(ASOBJS) $(COBJS) $(CPPOBJS) Makefile
	$(LINK) $(LIB-LINK-FLAGS) $(ASOBJS) $(CPPOBJS) $(COBJS) $(LIB-LINK-OPTIONS)
	
$(STATIC-LIBRARY-NAME): $(ASOBJS) $(COBJS) $(CPPOBJS) Makefile
	$(BUILD-AR) $(AR-FLAGS) $(ASOBJS) $(CPPOBJS) $(COBJS)

.s.o: %.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

.cpp.o: %.cpp Makefile
	$(BUILD-CPP) -MMD -MP $(BUILD-CPP-FLAGS) $< -o $@ $(BUILD-CPP-OPTIONS)
