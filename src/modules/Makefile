all: test boot

test: dummy.file
	$(MAKE) -C test

boot: dummy.file
	$(MAKE) -C boot

clean: test-clean boot-clean

test-clean: dummy.file
	$(MAKE) -C test clean

boot-clean: dummy.file
	$(MAKE) -C boot clean

dummy.file: