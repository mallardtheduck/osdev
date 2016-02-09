TARS := test livecd

all: dummy.file
	for dir in $(TARS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(TARS); do \
		make -C $$dir clean; \
	done

dummy.file:
