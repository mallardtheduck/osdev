export PREFIX:=$(HOME)/Projects/os/cross
export TARGET:=i686-elf
export PATH:=$(PREFIX)/bin:$(PATH)

all: modules user kernel
clean: kernel-clean modules-clean user-clean
rebuild: clean all

kernel: dummy.file
	$(MAKE) -C kernel

kernel-clean: dummy.file
	$(MAKE) -C kernel clean

modules: dummy.file
	$(MAKE) -C modules

modules-clean: dummy.file
	$(MAKE) -C modules clean

user: dummy.file
	$(MAKE) -C user

user-clean:
	$(MAKE) -C user clean

test: dummy.file testreqs
	cd kernel && ./test.sh

testtxt: dummy.file testreqs
	cd kernel && ./testtxt.sh

testreqs: kernel/test.img

kernel/test.img:
	qemu-img create kernel/test.img 100M

dummy.file: