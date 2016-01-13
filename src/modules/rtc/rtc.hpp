#include <btos_module.h>

#define RTC_NO_STUBS
#include <dev/rtc.h>

//ISO-8061-ish format. Using 'T' as a delimeter instead of space (as ISO dictates) is bad for reaability, so is not used.
#define FORMAT "%02i-%02i-%02i %02i:%02i:%02i"

extern volatile uint64_t msec_counter;

struct datetime{
	int day, month, year;
	int hour, minute, second;
};

void init_api();
void init_clock(const datetime bootTime);
datetime current_datetime();