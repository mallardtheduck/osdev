export PREFIX:=$(HOME)/Projects/os/cross
export TARGET:=i686-elf
export PATH:=$(PREFIX)/bin:$(PATH)

all: modules kernel
clean: kernel-clean modules-clean
rebuild: clean all

kernel: dummy.file
	$(MAKE) -C kernel

kernel-clean: dummy.file
	$(MAKE) -C kernel clean

modules: dummy.file
	$(MAKE) -C modules

modules-clean: dummy.file
	$(MAKE) -C modules clean

test: dummy.file
	cd kernel && ./test.sh

testtxt: dummy.file
	cd kernel && ./testtxt.sh

dummy.file: