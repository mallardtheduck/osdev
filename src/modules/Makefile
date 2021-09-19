MODULES := boot fatfs terminal iso9660 hwpnp cache

all: dummy.file
	for dir in $(MODULES); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(MODULES); do \
		make -C $$dir clean; \
	done

dummy.file: