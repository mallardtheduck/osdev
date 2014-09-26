PROGS := test ctest cpptest cmd cls title

all: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir clean; \
	done

dummy.file: