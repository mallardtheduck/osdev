#ifndef _RTC_HPP
#define _RTC_HPP

#include <btos_module.h>

#define RTC_NO_STUBS
#include <dev/rtc.hpp>

struct datetime{
	int day, month, year;
	int hour, minute, second;
};

void init_api();
void init_clock(const datetime bootTime);
datetime current_datetime();
uint64_t datetime2epoch(const datetime &dt);

void init_timer();
uint64_t get_msecs();
uint64_t rtc_get_time();

void init_rtc();

#endif