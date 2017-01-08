OUTPUT-NAME := elltest.elx
LIB-NAME := testlib.ell

BUILD-C := i686-pc-btos-gcc
ELX-BUILD-C-FLAGS := -c
ELX-BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../include -std=gnu99
ELL-BUILD-C-FLAGS := -c -fPIC
ELL-BUILD-C-OPTIONS := -Wall -Wextra -Werror -g -c -I../../include -std=gnu99
LINK := i686-pc-btos-gcc
ELX-LINK-FLAGS := -o $(OUTPUT-NAME) -O2
ELX-LINK-OPTIONS := -lgcc_s -l:testlib.ell
ELL-LINK-FLAGS := -O2 -fPIC -shared
ELL-LINK-OPTIONS := -o $(LIB-NAME)

ELX-CFILES := elltest.c
ELL-CFILES := testlib.c

ELX-OBJS := elltest.o
ELL-OBJS := testlib.o

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))
CPPDEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))

all: $(OUTPUT-NAME) $(LIB-NAME)

-include $(CDEPFILES) $(CPPDEPFILES)

clean: dummy.delete

dummy.delete:
	-@$(RM) *.o
	-@$(RM) $(OUTPUT-NAME)
	-@$(RM) $(LIB-NAME)

$(OUTPUT-NAME): $(ELX-OBJS) Makefile $(LIB-NAME)
	$(LINK) $(ELX-LINK-FLAGS) $(ELX-OBJS) $(ELX-LINK-OPTIONS)

$(LIB-NAME): $(ELL-OBJS) Makefile
	$(LINK) $(ELL-LINK-FLAGS) $(ELL-OBJS) $(ELL-LINK-OPTIONS)

$(ELX-OBJS): %.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(ELX-BUILD-C-FLAGS) $< -o $@ $(ELX-BUILD-C-OPTIONS)

$(ELL-OBJS): %.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(ELL-BUILD-C-FLAGS) $< -o $@ $(ELL-BUILD-C-OPTIONS)
