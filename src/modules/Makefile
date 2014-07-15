all: test boot rtc

test: dummy.file
	$(MAKE) -C test

boot: dummy.file
	$(MAKE) -C boot

rtc: dummy.file
	$(MAKE) -C rtc

clean: test-clean boot-clean rtc-clean

test-clean: dummy.file
	$(MAKE) -C test clean

boot-clean: dummy.file
	$(MAKE) -C boot clean

rtc-clean: dummy.file
	$(MAKE) -C rtc clean

dummy.file: