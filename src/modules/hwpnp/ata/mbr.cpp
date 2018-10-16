#include <stdint.h>
#include "ata.hpp"
#include <btos_module.h>

struct part_entry{
	uint8_t boot;
	uint8_t starthead;
	uint16_t start_sector_cylinder;
	uint8_t system;
	uint8_t endhead;
	uint16_t end_sector_cylinder;
	uint32_t start_lba;
	uint32_t sectors;
} __attribute__((packed));

static void mbr_parse(MBRVolume *vol, btos_api::hwpnp::IBlockDevice *dev){
	char blockbuf[512];
	part_entry part_table[4];
	dev->ReadSector(0, (uint8_t*)blockbuf);
	memcpy((void*)part_table, (void*)&blockbuf[0x1be], 64);
	for(size_t i=0; i<4; ++i){
		part_entry &p=part_table[i];
		dbgpf("ATA: MBR parition %i: %x, %i,+%i\n", (int)i, (int)p.system, p.start_lba, (int)p.sectors);
		if(p.system){
			vol->partitions.push_back({p.start_lba, p.sectors});
		}
	}
}

MBRVolume::MBRVolume(btos_api::hwpnp::IBlockDevice *dev) : device(dev) {
	mbr_parse(this, device);
}

btos_api::hwpnp::DeviceID MBRVolume::GetID(){
	return VolumeDeviceID;
}

const char *MBRVolume::GetDescription(){
	return "MBR partitioned volume";
}

size_t MBRVolume::GetSubDeviceCount(){
	return partitions.size();
}

btos_api::hwpnp::DeviceID MBRVolume::GetSubDevice(size_t i){
	if(i > partitions.size()) return btos_api::hwpnp::NullDeviceID;
	else return PartitionDeviceID;
}

btos_api::hwpnp::IDriver *MBRVolume::GetDriver(){
	return GetMBRVolumeDriver();
}

btos_api::hwpnp::IDeviceNode *MBRVolume::GetDeviceNode(){
	return nullptr;
}

void MBRVolume::ReadSector(size_t i, uint64_t lba, uint8_t *buf){
	if(i > partitions.size()) return;
	if(lba > partitions[i].sectors) return;
	uint64_t realLBA = partitions[i].start + lba;
	device->ReadSector(realLBA, buf);
}

void MBRVolume::WriteSector(size_t i, uint64_t lba, const uint8_t *buf){
	if(i > partitions.size()) return;
	if(lba > partitions[i].sectors) return;
	uint64_t realLBA = partitions[i].start + lba;
	device->WriteSector(realLBA, buf);
}

size_t MBRVolume::GetSectorSize(){
	return device->GetSectorSize();
}

bt_filesize_t MBRVolume::GetSize(size_t i){
	if(i > partitions.size()) return 0;
	return partitions[i].sectors * device->GetSectorSize();
}

Partition::Partition(btos_api::hwpnp::IVolume *vol, size_t i) : volume(vol), index(i), node(this) {}
		
btos_api::hwpnp::DeviceID Partition::GetID(){
	return PartitionDeviceID;
}

const char *Partition::GetDescription(){
	return "Disk partition";
}

size_t Partition::GetSubDeviceCount(){
	return 0;
}

btos_api::hwpnp::DeviceID Partition::GetSubDevice(size_t){
	return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *Partition::GetDriver(){
	return GetPartitionDriver();
}

btos_api::hwpnp::IDeviceNode *Partition::GetDeviceNode(){
	return &node;
}

int Partition::GetType(){
	return driver_types::STR_PART;
}
	
void Partition::ReadSector(uint64_t lba, uint8_t *buf){
	volume->ReadSector(index, lba, buf);
}

void Partition::WriteSector(uint64_t lba, const uint8_t *buf){
	volume->WriteSector(index, lba, buf);
}

size_t Partition::GetSectorSize(){
	return volume->GetSectorSize();
}

bt_filesize_t Partition::GetSize(){
	return volume->GetSize(index);
}

PartitionDeviceNode::PartitionDeviceNode(Partition *dev) : btos_api::hwpnp::BlockDeviceNode(dev) {}

const char *PartitionDeviceNode::GetBaseName(){
	return "PART";
}
