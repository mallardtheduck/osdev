all: test boot rtc keyboard

test: dummy.file
	$(MAKE) -C test

boot: dummy.file
	$(MAKE) -C boot

rtc: dummy.file
	$(MAKE) -C rtc

keyboard: dummy.file
	$(MAKE) -C keyboard

clean: test-clean boot-clean rtc-clean keyboard-clean

test-clean: dummy.file
	$(MAKE) -C test clean

boot-clean: dummy.file
	$(MAKE) -C boot clean

rtc-clean: dummy.file
	$(MAKE) -C rtc clean

keyboard-clean: dummy.file
	$(MAKE) -C keyboard clean

dummy.file: