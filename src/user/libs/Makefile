LIBS := btoscore newlib sm btoslib libgds libwm eloader ansi

all: dummy.file
	for dir in $(LIBS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(LIBS); do \
		make -C $$dir clean; \
	done

dummy.file:
