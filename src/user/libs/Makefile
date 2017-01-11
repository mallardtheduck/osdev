LIBS := newlib libgds libwm

all: dummy.file
	for dir in $(LIBS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(LIBS); do \
		make -C $$dir clean; \
	done

dummy.file:
