PROGS := test ctest cpptest cmd cls termctl switcher spawn kill load mount msgtest mousetest vgatest fputest gds debug crash libgds wm libwm wmmenu startwm termwin breakout sleep tar format

all: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir; \
	done

clean: dummy.file
	for dir in $(PROGS); do \
		make -C $$dir clean; \
	done

dummy.file:
