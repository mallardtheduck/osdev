PROGS := wmmenu termwin breakout protoclock prototext prototask calc folder notepad appview elxrun launcher

all: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir clean; \
	done

dummy.file:
