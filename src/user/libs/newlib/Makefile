LIBS := libm libc

all: dummy.file
	make -C libc startfiles
	for dir in $(LIBS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(LIBS); do \
		make -C $$dir clean; \
	done

dummy.file:
