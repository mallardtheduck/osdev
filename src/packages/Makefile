PACKAGES := base kernel install tests protogui gui

all: dummy.file
	for dir in $(PACKAGES); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(PACKAGES); do \
		make -C $$dir clean; \
	done

dummy.file:
