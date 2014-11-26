export PREFIX:=$(HOME)/Projects/os/cross
export TARGET:=i686-elf
export PATH:=$(PREFIX)/bin:$(PATH)

all: modules user disk kernel
clean: kernel-clean modules-clean user-clean disk-clean
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

test: dummy.file disk
	cd kernel && ./test.sh

testtxt: dummy.file disk
	cd kernel && ./testtxt.sh

disk: disk/btos.img

disk/btos.img: dummy.file
	make -C disk

disk-clean: dummy.file
	make -C disk clean

dummy.file: