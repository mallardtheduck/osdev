#include "initfs.hpp"
#include "xxd_data.inc"

unsigned char null_file[] = {};

initfs_file initfs_data[] = {
	{true, "NULL.FILE", null_file, sizeof(null_file)},
	{true, "CONFIG.INI", __data_config_ini, sizeof(__data_config_ini)},
	{true, "TEST.SYS", __data_test_sys, sizeof(__data_test_sys)},
	{true, "BOOT.SYS", __data_boot_sys, sizeof(__data_boot_sys)},
	{true, "RTC.SYS", __data_rtc_sys, sizeof(__data_rtc_sys)},
	{false, "", NULL, 0}
};
