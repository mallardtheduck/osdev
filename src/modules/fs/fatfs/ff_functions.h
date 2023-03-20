#ifndef FATFS_FF_FUNCTIONS_H
#define FATFS_FF_FUNCTIONS_H

#include <util/bt_enum.h>
#ifdef __cplusplus
	#include <cstddef>
	#include <cstdint>
#else
	#include <stddef.h>
	#include <stdint.h>
#endif

#define HANDLE void*

EXTERN_C void *create_lock();
EXTERN_C void take_lock(void *lock);
EXTERN_C void release_lock(void *lock);
EXTERN_C void delete_lock(void *lock);

EXTERN_C uint8_t get_disk_status(uint8_t drive);
EXTERN_C int read_sector(uint8_t drive, char *buffer, uint64_t sector, size_t count);
EXTERN_C int write_sector(uint8_t drive, const char *buffer, uint64_t sector, size_t count);
EXTERN_C void sync(uint8_t drive);

EXTERN_C void init_disk(uint8_t drive);
EXTERN_C size_t get_block_size(uint8_t drive);
EXTERN_C size_t get_sector_size(uint8_t drive);
EXTERN_C uint64_t get_sector_count(uint8_t drive);

EXTERN_C uint32_t get_fattime();

EXTERN_C int memcmp(const void *s1, const void *s2, size_t n);
EXTERN_C char *strchr(const char *s, int c);


#endif