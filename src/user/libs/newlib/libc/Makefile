LIBRARY-NAME := libc.ell
G-LIBRARY-NAME := libg.ell
STATIC-NAME := libc.a
G-STATIC-NAME := libg.a
STARTUP-OBJS := sys/btos/crt0.o sys/btos/crti.o sys/btos/crtn.o

DESTINATION := $(HOME)/Projects/os/cross/i686-pc-btos

BUILD-AS := i686-pc-btos-gcc
BUILD-AR := i686-pc-btos-ar
BUILD-AS-OPTIONS := -g -c -fPIC -D_I386MACH_NEED_SOTYPE_FUNCTION
AR-FLAGS := rcs -o $(STATIC-NAME)
BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c -fPIC -DINTERNAL_NEWLIB -D_COMPILING_NEWLIB -ffreestanding
BUILD-C-OPTIONS := -Wall -Wextra -g -c -I../../../../include -I./sys/btos -I./include -std=gnu99
LINK := i686-pc-btos-gcc
LINK-FLAGS := -O2 -fPIC -shared -nodefaultlibs -ffreestanding -lm -lgcc_s
LINK-OPTIONS := -o $(LIBRARY-NAME)

FOLDERS := argz ctype errno locale machine reent search signal stdio stdlib string sys syscalls time
SKIP-FILES := signal/signal.c stdlib/getenv.c syscalls/syslseek.c syscalls/syswait.c syscalls/sysunlink.c syscalls/sysopen.c syscalls/sysgetpid.c syscalls/sysgettod.c syscalls/sysfcntl.c syscalls/sysfork.c syscalls/syskill.c syscalls/syswrite.c syscalls/sysstat.c syscalls/syssbrk.c syscalls/sysisatty.c syscalls/sysexecve.c syscalls/sysclose.c syscalls/syslink.c syscalls/sysread.c syscalls/sysfstat.c syscalls/systimes.c string/memcpy.c string/strlen.c string/memcmp.c string/memmove.c string/memset.c string/memchr.c string/strchr.c sys/btos/crti.S sys/btos/crt0.S sys/btos/crtn.S
SKIP-SPEC := $(shell printf "! -wholename %s " $(SKIP-FILES))

ASFILES := $(shell find $(FOLDERS) -type f -name "*.s" -or -name "*.S" $(SKIP-SPEC))
CFILES := $(shell find $(FOLDERS) -type f -name "*.c" $(SKIP-SPEC))

INCLUDE-FOLDERS := include sys/btos

ASOBJS1 := $(ASFILES:.s=.o)
ASOBJS2 := $(ASOBJS1:.S=.o)
ASOBJS := $(ASOBJS2)
COBJS := $(CFILES:.c=.o)

EXTRAOBJS := stdio/vfiprintf.o stdio/svfprintf.o stdio/svfiprintf.o stdio/vfiwprintf.o stdio/svfwprintf.o stdio/svfiwprintf.o stdio/vfiscanf.o stdio/svfscanf.o stdio/svfiscanf.o stdio/vfiwscanf.o stdio/svfwscanf.o stdio/svfiwscanf.o

CDEPFILES := $(patsubst %.c,%.d,$(CFILES))

all: $(LIBRARY-NAME) $(STATIC-NAME) $(STARTUP-OBJS) copy

startfiles: copy-startfiles

-include $(CDEPFILES) $(CPPDEPFILES)

copy:
	mkdir -p $(DESTINATION)/lib
	mkdir -p $(DESTINATION)/include
	cp -u $(LIBRARY-NAME) $(DESTINATION)/lib
	cp -u $(STATIC-NAME) $(DESTINATION)/lib
	cp -u $(LIBRARY-NAME) $(DESTINATION)/lib/$(G-LIBRARY-NAME)
	cp -u $(STATIC-NAME) $(DESTINATION)/lib/$(G-STATIC-NAME)
	for folder in $(INCLUDE-FOLDERS); do \
		(cd $$folder && find -type f -name "*.h" -exec cp -u --parents {} $(DESTINATION)/include \;); \
	done

copy-startfiles: $(STARTUP-OBJS)
	for file in $(STARTUP-OBJS); do cp $$file $(DESTINATION)/lib; done

clean: dummy.delete

dummy.delete:
	-@find . -name \*.o -delete
	-@$(RM) $(LIBRARY-NAME)
	-@$(RM) $(STATIC-NAME)

$(LIBRARY-NAME): $(ASOBJS) $(COBJS) $(EXTRAOBJS) Makefile
	$(LINK) $(LINK-FLAGS) $(ASOBJS) $(COBJS) $(EXTRAOBJS) $(LINK-OPTIONS)

$(STATIC-NAME): $(ASOBJS) $(COBJS) $(EXTRAOBJS) Makefile
	$(BUILD-AR) $(AR-FLAGS) $(ASOBJS) $(COBJS) $(EXTRAOBJS)

.s.o: %.s Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.S.o: %.S Makefile
	$(BUILD-AS) $< -o $@ $(BUILD-AS-OPTIONS)

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/vfiprintf.o: stdio/vfprintf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfprintf.o: stdio/vfprintf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfiprintf.o: stdio/vfprintf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/vfiwprintf.o: stdio/vfwprintf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfwprintf.o: stdio/vfwprintf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfiwprintf.o: stdio/vfwprintf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/vfiscanf.o: stdio/vfscanf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfscanf.o: stdio/vfscanf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfiscanf.o: stdio/vfscanf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/vfiwscanf.o: stdio/vfwscanf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfwscanf.o: stdio/vfwscanf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common

stdio/svfiwscanf.o: stdio/vfwscanf.c
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) -DSTRING_ONLY -DINTEGER_ONLY $< -o $@ $(BUILD-C-OPTIONS) -I$(shell dirname $<) -I../libm/common
