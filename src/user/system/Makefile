PROGS := eloader spawn switcher gds wm sm

all: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir clean; \
	done

dummy.file:
