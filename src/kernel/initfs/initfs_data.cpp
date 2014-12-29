#include "initfs.hpp"
#include "xxd_data.inc"

unsigned char null_file[] = {};

initfs_file initfs_data[] = {
	{true, "NULL.FILE", null_file, sizeof(null_file)},
	{true, "CONFIG.INI", __data_config_ini, sizeof(__data_config_ini)},
	{true, "BOOT.SYS", __data_boot_sys, sizeof(__data_boot_sys)},
	{true, "RTC.SYS", __data_rtc_sys, sizeof(__data_rtc_sys)},
	{true, "PS2.SYS", __data_ps2_sys, sizeof(__data_ps2_sys)},
	{true, "ATA.SYS", __data_ata_sys, sizeof(__data_ata_sys)},
	{true, "FAT.SYS", __data_fat_sys, sizeof(__data_fat_sys)},
    {true, "SPAWN.ELX", __data_spawn_elx, sizeof(__data_spawn_elx)},
	{false, "", NULL, 0}
};
