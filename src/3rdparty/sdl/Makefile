LIBRARY-NAME := SDL2.ell
DESTINATION := ../install/btos

BUILD-C := i686-pc-btos-gcc
BUILD-C-FLAGS := -c -Wall -Wextra
BUILD-C-OPTIONS := -g -c -I./include -I../../include -std=gnu99
LINK := i686-pc-btos-gcc
LIB-LINK-FLAGS := -o $(LIBRARY-NAME) -O2 -fPIC -shared -L.
LIB-LINK-OPTIONS := -lgcc_s -lc -lbtoscore -lgds -lwm

SOURCES = \
	src/*.c \
	src/atomic/*.c \
	src/audio/*.c \
	src/audio/dummy/*.c \
	src/cpuinfo/*.c \
	src/events/*.c \
	src/file/*.c \
	src/haptic/*.c \
	src/haptic/dummy/*.c \
	src/joystick/*.c \
	src/joystick/dummy/*.c \
	src/loadso/dummy/*.c \
	src/power/*.c \
	src/filesystem/dummy/*.c \
	src/render/*.c \
	src/render/software/*.c \
	src/stdlib/*.c \
	src/thread/*.c \
	src/thread/pthread/*.c \
	src/timer/*.c \
	src/timer/dummy/*.c \
	src/video/*.c \
	src/video/dummy/*.c \
	src/video/btos/*.c

OBJECTS = $(shell echo $(SOURCES) | sed -e 's,\.c,\.o,g')

all: $(LIBRARY-NAME) copy

.c.o: %.c Makefile
	$(BUILD-C) -MMD -MP $(BUILD-C-FLAGS) $< -o $@ $(BUILD-C-OPTIONS)

$(LIBRARY-NAME): $(OBJECTS) Makefile
	$(LINK) $(LIB-LINK-FLAGS) $(OBJECTS) $(LIB-LINK-OPTIONS)

clean:
	rm -f $(TARGET) $(OBJECTS)
	
copy: $(LIBRARY-NAME)
	mkdir -p $(DESTINATION)/lib
	cp -u $(LIBRARY-NAME) $(DESTINATION)/lib
	mkdir -p $(DESTINATION)/include/SDL2
	cp -uR include/*.h $(DESTINATION)/include/SDL2
