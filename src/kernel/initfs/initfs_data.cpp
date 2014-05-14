#include "initfs.hpp"
#include "xxd_data.inc"

unsigned char null_file[] = {};

initfs_file initfs_data[] = {
	{true, "NULL.FILE", null_file, sizeof(null_file)},
	{true, "CONFIG.INI", __data_config_ini, sizeof(__data_config_ini)},
	{true, "TEST.SYS", __data_test_sys, sizeof(__data_test_sys)},
	{false, "", NULL, 0}
};
