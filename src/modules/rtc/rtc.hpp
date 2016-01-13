#include <btos_module.h>

#define RTC_NO_STUBS
#include <dev/rtc.h>

#define FORMAT "%02i:%02i:%02i %02i/%02i/%02i"

extern volatile uint64_t msec_counter;

struct datetime{
	int day, month, year;
	int hour, minute, second;
};

void init_api();
void init_clock(const datetime bootTime);
datetime current_datetime();