#ifndef FATFS_DRIVE_HPP
#define FATFS_DRIVE_HPP

#include <btos_module.h>

class FatFSDrive : private nonmovable{
private:
	IFileHandle *dev;
public:
	FatFSDrive(IFileHandle *d) : dev(d) {}

	int read_sector(char *buffer, uint64_t sector, size_t count);
	int write_sector(const char *buffer, uint64_t sector, size_t count);

	uint64_t get_sector_count();	

	void sync();

	~FatFSDrive();
};

FatFSDrive *GetDrive(uint8_t id);
uint8_t NewDrive(IFileHandle *drv);
void DeleteDrive(uint8_t id);

#endif