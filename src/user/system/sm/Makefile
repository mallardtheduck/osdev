OUTPUT-NAME := session.elx

BUILD-AS := i686-pc-btos-as
BUILD-AS-OPTIONS := -g -fPIC -c
BUILD-CPP := i686-pc-btos-g++
BUILD-CPP-FLAGS :=  -c
BUILD-CPP-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu++11
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c
BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../../include -std=gnu99
LINK := i686-pc-btos-gcc
LINK-FLAGS := -o $(OUTPUT-NAME) -O2
LINK-OPTIONS := -L../../libs/sm -lgcc_s -lstdc++ -lbtoscore -lm -lbtoslib -lsm

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp")

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

$(OUTPUT-NAME): $(ASOBJS) $(COBJS) $(CPPOBJS) Makefile
	$(LINK) $(LINK-FLAGS) $(ASOBJS) $(CPPOBJS) $(COBJS) $(LINK-OPTIONS)

.s.o: %.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

.cpp.o: %.cpp Makefile
	$(BUILD-CPP) -MMD -MP $(BUILD-CPP-FLAGS) $< -o $@ $(BUILD-CPP-OPTIONS)
