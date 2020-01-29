OUTPUT-NAME := calc.elx
RESC-TAR-NAME := calc_resc.tar
RESC-VAR-NAME := calc_resc
APP-ICON-NAME := calc

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
LINK-OPTIONS := -lgcc_s -lstdc++ -lm  -lbtoscore -lbtoslib -lresc -lgds -lwm -lgui -lclipboard

RESCFILES-16-ACTIONS := \
	calc_standard.png \
	calc_scientific.png \
	calc_programmer.png \
	editcopy.png \
	editpaste.png \

RESCFILES-APP-ICON := \
	resc/$(APP-ICON-NAME)_16.png \
	resc/$(APP-ICON-NAME)_32.png \

RESCFILES-EXTRA := resc/app.inf resc/icons.inf

BOOTFILE := boot.o
ASFILES := $(shell find . -type f -name "*.s")
CFILES := $(shell find . -type f -name "*.c")
CPPFILES := $(shell find . -type f -name "*.cpp")

RESCFILES-16-ACTIONS-SRC := $(patsubst %,../../../icons/16/actions/%,$(RESCFILES-16-ACTIONS))
RESCFILES-16-ACTIONS-DST :=  $(patsubst %,resc/%,$(RESCFILES-16-ACTIONS))
RESCFILES := $(RESCFILES-16-ACTIONS-DST) $(RESCFILES-APP-ICON) $(RESCFILES-EXTRA)

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
	
$(RESCFILES-16-ACTIONS-DST): $(RESCFILES-16-ACTIONS-SRC)
	@mkdir -p $(@D)
	cp ../../../icons/16/actions/$(patsubst resc/%,%,$@) $@

resc/$(APP-ICON-NAME)_16.png: ../../../icons/16/apps/$(APP-ICON-NAME).png
	@mkdir -p $(@D)
	cp $< $@

resc/$(APP-ICON-NAME)_32.png: ../../../icons/32/apps/$(APP-ICON-NAME).png
	@mkdir -p $(@D)
	cp $< $@
	
resc/app.inf: app.inf
	cp $< $@

resc/icons.inf: icons.inf
	cp $< $@