all: test

test: dummy.file
	$(MAKE) -C test

clean: test-clean boot-clean rtc-clean

test-clean: dummy.file
	$(MAKE) -C test clean

dummy.file: