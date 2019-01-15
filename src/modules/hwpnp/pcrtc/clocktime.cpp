#include "rtc.hpp"

uint64_t boot_msec;

const int epochYear = 2000;

const uint64_t secondsPerMinute = 60;
const uint64_t secondsPerHour = secondsPerMinute * 60;
const uint64_t secondsPerDay = secondsPerHour * 24;

const uint64_t secondsPerMonth[] = {
	0,	//Month 0
	31 * secondsPerDay, //Jan
	28 * secondsPerDay,	//Feb (leap day seperately accounted)
	31 * secondsPerDay, //March
	30 * secondsPerDay, //April
	31 * secondsPerDay, //May
	30 * secondsPerDay, //June
	31 * secondsPerDay, //July
	31 * secondsPerDay, //Aug
	30 * secondsPerDay, //Sept
	31 * secondsPerDay, //Oct
	30 * secondsPerDay, //Nov
	31 * secondsPerDay, //Dec
};

bool is_leap_year(int year){
	return ((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0));
}

uint64_t seconds_in_year(int year){
	return is_leap_year(year)? 366 * secondsPerDay : 365 * secondsPerDay;
}

uint64_t seconds_in_month(int month, int year){
	return (month == 2 && is_leap_year(year))? secondsPerMonth[month] + secondsPerDay : secondsPerMonth[month];
}

uint64_t datetime2epoch(const datetime &dt){
	uint64_t ret = 0;
	ret = dt.second;
	ret += dt.minute * secondsPerMinute;
	ret += dt.hour * secondsPerHour;
	ret += dt.day * secondsPerDay;
	for(size_t m = 0; m < (size_t)dt.month; ++m){
		ret += secondsPerMonth[m];
	}
	for(int y = epochYear; y < dt.year; ++y){
		ret += seconds_in_year(y);
	}
	if(is_leap_year(dt.year) && dt.month > 2) ret+=secondsPerDay;	
	return ret * 1000;
}

datetime epoch2datetime(uint64_t ep){
	datetime ret = {0, 0, epochYear, 0, 0, 0};
	ep /= 1000;
	while(ep >= (unsigned)seconds_in_year(ret.year)){
		ep -= seconds_in_year(ret.year);
		++ret.year;
	}
	while(ep >= (unsigned)seconds_in_month(ret.month, ret.year)){
		ep -= seconds_in_month(ret.month, ret.year);
		++ret.month;
	}
	while(ep >= secondsPerDay){
		ep-=secondsPerDay;
		++ret.day;
	}
	while(ep >= secondsPerHour){
		ep-=secondsPerHour;
		++ret.hour;
	}
	while(ep >= secondsPerMinute){
		ep-=secondsPerMinute;
		++ret.minute;
	}
	ret.second = ep;
	return ret;
}

void init_clock(const datetime bootTime){
	boot_msec = datetime2epoch(bootTime);
}

datetime current_datetime(){
	return epoch2datetime(boot_msec + get_msecs());
}
