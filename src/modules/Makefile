MODULES := boot test fat terminal pci vga iso9660 hwpnp

all: dummy.file
	for dir in $(MODULES); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(MODULES); do \
		make -C $$dir clean; \
	done

dummy.file: