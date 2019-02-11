output-name := tests.pkf

import-files:= \
 data/tests/ctest.elx \
 data/tests/cpptest.elx \
 data/tests/test.sys \
 data/tests/msgtest.elx \
 data/tests/mousetest.elx \
 data/tests/vgatest.elx \
 data/tests/fputest.elx \
 data/tests/crash.elx \
 data/tests/gdstest.elx \
 data/tests/wmtest.elx \
 data/tests/shmtest.elx \
 data/tests/elltest.elx \
 data/tests/testlib.ell \
 data/tests/elldtest.elx \
 data/tests/nctest.elx \
 data/tests/sdltest.elx \
 data/tests/pthreadtest.elx \
 data/tests/testpng.png \
 data/tests/testsw.elx \
 data/tests/guitest.elx \

all: ../$(output-name)
pkg-files:= $(shell find pkgfiles -type f)

data/tests/ctest.elx: ../../user/tests/ctest/ctest.elx create.directories
	cp $< $@

data/tests/cpptest.elx: ../../user/tests/cpptest/cpptest.elx create.directories
	cp $< $@

data/tests/test.sys: ../../modules/test/test.sys create.directories
	cp $< $@

data/tests/msgtest.elx: ../../user/tests/msgtest/msgtest.elx create.directories
	cp $< $@

data/tests/mousetest.elx: ../../user/tests/mousetest/mousetest.elx create.directories
	cp $< $@

data/tests/vgatest.elx: ../../user/tests/vgatest/vgatest.elx create.directories
	cp $< $@

data/tests/gdstest.elx: ../../user/libs/libgds/gdstest.elx create.directories
	cp $< $@

data/tests/fputest.elx: ../../user/tests/fputest/fputest.elx create.directories
	cp $< $@

data/tests/shmtest.elx: ../../user/tests/shmtest/shmtest.elx create.directories
	cp $< $@

data/tests/elltest.elx: ../../user/tests/elltest/elltest.elx create.directories
	cp $< $@

data/tests/testlib.ell: ../../user/tests/elltest/testlib.ell create.directories
	cp $< $@

data/tests/elldtest.elx: ../../user/libs/eloader/elldtest.elx
	cp $< $@

data/tests/crash.elx: ../../user/tests/crash/crash.elx create.directories
	cp $< $@

data/tests/wmtest.elx: ../../user/libs/libwm/wmtest.elx create.directories
	cp $< $@

data/tests/nctest.elx: ../../user/tests/nctest/nctest.elx
	cp $< $@

data/tests/sdltest.elx: ../../user/tests/sdltest/sdltest.elx
	cp $< $@
	
data/tests/pthreadtest.elx: ../../user/tests/pthreadtest/pthreadtest.elx
	cp $< $@

data/tests/testpng.png: ../../user/tests/sdltest/testpng.png
	cp $< $@

data/tests/testsw.elx: ../../3rdparty/SDL2-widgets-2.1/testsw
	cp $< $@

data/tests/guitest.elx: ../../user/libs/gui/guitest.elx
	cp $< $@

create.directories:
	mkdir -p data/tests
	touch create.directories

../$(output-name): $(pkg-files) create.directories $(import-files)
	-cp -R pkgfiles/* data
	tar cf ../$(output-name) -C data .

clean:
	-rm -rf data
	-rm ../$(output-name)
	-rm create.directories
