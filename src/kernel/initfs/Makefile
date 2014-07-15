xxd_data.inc: data/config.ini data/test.sys data/boot.sys data/rtc.sys
	./make_inc.sh

data/test.sys: ../../modules/test/test.sys
	cp ../../modules/test/test.sys data/test.sys

data/boot.sys: ../../modules/boot/boot.sys
	cp ../../modules/boot/boot.sys data/boot.sys

data/rtc.sys: ../../modules/rtc/rtc.sys
	cp ../../modules/rtc/rtc.sys data/rtc.sys

