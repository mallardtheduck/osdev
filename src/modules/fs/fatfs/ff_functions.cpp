#include <btos_module.h>
#include "ff_functions.h"
#include "drive.hpp"

EXTERN_C void *create_lock(){
	return API->NewLock();
}

EXTERN_C void take_lock(void *lock){
	static_cast<ILock*>(lock)->TakeExclusive();
}

EXTERN_C void release_lock(void *lock){
	static_cast<ILock*>(lock)->Release();
}

EXTERN_C void delete_lock(void *lock){
	delete static_cast<ILock*>(lock);
}

EXTERN_C uint8_t get_disk_status(uint8_t drive){
	auto drv = GetDrive(drive);
	if(drv) return 0;
	else return 2; //STA_NODISK
}

EXTERN_C void init_disk(uint8_t drive){

}

EXTERN_C int read_sector(uint8_t drive, char *buffer, uint64_t sector, size_t count){
	auto drv = GetDrive(drive);
	if(drv) return drv->read_sector(buffer, sector, count);
	else return 0;
}

EXTERN_C int write_sector(uint8_t drive, const char *buffer, uint64_t sector, size_t count){
	auto drv = GetDrive(drive);
	if(drv) return drv->write_sector(buffer, sector, count);
	else return 0;
}

EXTERN_C void sync(uint8_t drive){
	auto drv = GetDrive(drive);
	if(drv) drv->sync();
}

EXTERN_C size_t get_block_size(uint8_t drive){
	return 512;
}

EXTERN_C size_t get_sector_size(uint8_t drive){
	return get_block_size(drive);
}

EXTERN_C uint64_t get_sector_count(uint8_t drive){
	auto drv = GetDrive(drive);
	if(drv) return drv->get_sector_count();
	else return 0;
}

EXTERN_C uint32_t get_fattime(){
	return 0;
}

EXTERN_C int memcmp(const void *s1, const void *s2, size_t n){
	const unsigned char *p1 = (const unsigned char *)s1;
	const unsigned char *p2 = (const unsigned char *)s2;
	while(n--){
		if( *p1 != *p2 ) return *p1 - *p2;
		else p1++,p2++;
	}
	return 0;
}

EXTERN_C char *strchr(const char *s, int c){
	while (*s != (char)c){
		if (!*s++) return 0;
	}
	return (char *)s;
}


