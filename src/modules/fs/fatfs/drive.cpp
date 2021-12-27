#include "drive.hpp"

constexpr size_t SectorSize = 512;

int FatFSDrive::read_sector(char *buffer, uint64_t sector, size_t count){
	auto pos = sector * SectorSize;
	auto len = count * SectorSize;
	//dbgpf("FATFS: Read sector: %llu (%llu) len: %lu (%lu)\n", sector, pos, count, len);
	dev->Seek(pos, fs_seek_flags::FS_Set);
	dev->Read(len, buffer);
	return 0;
}

int FatFSDrive::write_sector(const char *buffer, uint64_t sector, size_t count){
	auto pos = sector * SectorSize;
	auto len = count * SectorSize;
	dev->Seek(pos, fs_seek_flags::FS_Set);
	dev->Write(len, buffer);
	return 0;
}

uint64_t FatFSDrive::get_sector_count(){
	auto size = dev->Seek(0, fs_seek_flags::FS_Backwards);
	dbgpf("FATFS: Sector count: %llu (%llu)\n", size / SectorSize, size);
	return size / SectorSize;
}

void FatFSDrive::sync(){
	dev->Flush();
}

FatFSDrive::~FatFSDrive(){
	dev->Close();
	delete dev;
}

static map<uint8_t, FatFSDrive *> drives;

FatFSDrive *GetDrive(uint8_t id){
	FatFSDrive *ret = nullptr;
	if(drives.has_key(id)) ret = drives[id];
	//dbgpf("FATFS: GetDrive(%i): %p\n", (int)id, ret);
	return ret;
}

uint8_t NewDrive(IFileHandle *drv){
	uint8_t id = 0;
	while(drives.has_key(id)) ++id;
	drives[id] = new FatFSDrive(drv);
	dbgpf("FATFS: Drive %i (%p) allocated for handle %p.\n", (int)id, drives[id], drv);
	return id;
}

void DeleteDrive(uint8_t id){
	if(drives.has_key(id)){
		auto drive = drives[id];
		drives.erase(id);
		delete drive;
	}
}