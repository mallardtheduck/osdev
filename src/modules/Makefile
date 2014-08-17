MODULES := boot test rtc keyboard ata fat

all: dummy.file
	for dir in $(MODULES); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(MODULES); do \
		make -C $$dir clean; \
	done

dummy.file: