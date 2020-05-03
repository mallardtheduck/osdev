#include <btos_module.h>
#include <util/holdlock.hpp>
#include "ata.hpp"

int
memcmp(const void *vs1, const void *vs2, size_t n){
	unsigned char u1, u2;
	char *s1 = (char*)vs1; char *s2 = (char*)vs2;

	for ( ; n-- ; s1++, s2++) {
		u1 = * (unsigned char *) s1;
		u2 = * (unsigned char *) s2;
		if ( u1 != u2) {
			return (u1-u2);
		}
		}
	return 0;
}

/*static void ata_io_wait(btos_api::hwpnp::IATABus *bus, size_t index) {
	bus->ReadControlByte(index);
	bus->ReadControlByte(index);
	bus->ReadControlByte(index);
	bus->ReadControlByte(index);
}*/

bool atapi_device_init(ata_device *dev){
	dbgpf("ATA: Initializing ATAPI device on bus %d\n", dev->io_base);

	outb(dev->io_base + ATA_REG_ERROR, 1);
	outb(dev->control, 0);

	outb(dev->io_base + ATA_REG_HDDEVSEL, 0xA0 | dev->slave << 4);
	ata_io_wait(dev);

	outb(dev->io_base + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
	ata_io_wait(dev);
	
	unsigned char cl = inb(dev->io_base + ATA_REG_LBA1);
	unsigned char ch = inb(dev->io_base + ATA_REG_LBA2);
	
	if(!(cl == 0x14 && ch == 0xEB) && !(cl == 0x69 && ch == 0x96)){
		return false;
	}

	outb(dev->io_base + ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
	ata_io_wait(dev);

	int status = inb(dev->io_base + ATA_REG_COMMAND);
	dbgpf("ATA: Device status: %d\n", status);
	
	if(status == 0 || (status & ATA_SR_ERR)) {
		dbgpf("ATA: Device does not exist or not ATAPI.\n");
		return false;
	}

	ata_wait(dev, 0);

	uint16_t * buf = (uint16_t *)&dev->identity;

	for (int i = 0; i < 256; ++i) {
		buf[i] = ins(dev->io_base);
	}

	uint8_t * ptr = (uint8_t *)&dev->identity.model;
	for (int i = 0; i < 39; i+=2) {
		uint8_t tmp = ptr[i+1];
		ptr[i+1] = ptr[i];
		ptr[i] = tmp;
	}

	dbgpf("ATA: Device Name:  %s\n", dev->identity.model);
	dbgpf("ATA: Sectors (48): %llu\n", dev->identity.sectors_48);
	dbgpf("ATA: Sectors (24): %lu\n", dev->identity.sectors_28);
	
	dev->atapi_packet_size = 0xFF;
	if((dev->identity.flags & 0x03) == 0) dev->atapi_packet_size = 12;
	if((dev->identity.flags & 0x03) == 1) dev->atapi_packet_size = 16;
	dbgpf("ATA: ATAPI Packet size: %d (%i)\n", (int)dev->atapi_packet_size, (int)(dev->identity.flags & 0x03));
	

	outb(dev->control, 0);
	
	//atapi_test(dev);
	
	return true;
}

size_t atapi_scsi_command(btos_api::hwpnp::IATABus *bus, size_t index, uint8_t cmd[12], size_t size, uint8_t *buf){
	const int max_fails = 5;
	int fails = 0;
	while(true){
		memset(buf, 0, size);
		uint8_t slave = bus->IsSlave(index);
		//dbgpf("ATA: Executing ATAPI SCSI command: %x\n", cmd[0]);
		
		bus->OutByte(index, ATA_REG_HDDEVSEL, slave << 4);
		ata_wait(bus, index, 0);
		bus->WriteControlByte(index, 0x00);
		bus->OutByte(index, ATA_REG_FEATURES, 0x00);
		bus->OutByte(index, ATA_REG_LBA1, (size & 0x000000ff) >> 0);
		bus->OutByte(index, ATA_REG_LBA2, (size & 0x0000ff00) >> 8);
		bus->OutByte(index, ATA_REG_COMMAND, ATA_CMD_PACKET);
		ata_wait(bus, index, 0);
		while(!(bus->ReadControlByte(index) & ATA_SR_DRQ)) cpu_pause();
		bus->ResetIntWait(index);
		for(size_t i=0; i<6; ++i){
			bus->OutWord(index, ATA_REG_DATA, ((uint16_t*)cmd)[i]);
		}
		bus->WaitInt(index);
		bus->ResetIntWait(index);
		uint8_t status = bus->ReadControlByte(index);
		//dbgpf("ATA: ATAPI status: %x\n", (int)status);
		if(status & ATA_SR_ERR){
			dbgout("ATA: ATAPI command error.\n");
			fails++;
			if(fails < max_fails) continue;
			else return 0;
		}
		size_t read = bus->InByte(index, ATA_REG_LBA1) + (bus->InByte(index, ATA_REG_LBA2) << 8);
		
		if(read != size){
			dbgout("ATA: ATAPI data size mismatch.\n");
			fails++;
			if(fails < max_fails) continue;
			else return 0;
		}
		
		//dbgout("ATA: ATAPI data:\n");
		for(size_t i=0; i<read/2; ++i){
			((uint16_t*)buf)[i] = bus->InWord(index, ATA_REG_DATA);
			//dbgpf("%x", (uint32_t)((uint16_t*)buf)[i]);
		}
		//dbgout("\n");
		ata_wait(bus, index, 0);
		while((bus->ReadControlByte(index) & ATA_SR_DRQ)) cpu_pause();
		return read;
	}
}

int atapi_device_read(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t *buf){
	//dbgpf("ATAPI: READ bus: %p, index: %i, lba: %x, buf: %p\n", bus, (int)index, lba, buf);
	uint8_t read_cmd[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	read_cmd[9] = 1;              /* 1 sector */
	read_cmd[2] = (lba >> 0x18) & 0xFF;   /* most sig. byte of LBA */
	read_cmd[3] = (lba >> 0x10) & 0xFF;
	read_cmd[4] = (lba >> 0x08) & 0xFF;
	read_cmd[5] = (lba >> 0x00) & 0xFF;
	//dbgpf("ATA: Read ATAPI sector %i.\n", lba);
	
	size_t ret = atapi_scsi_command(bus, index, read_cmd, ATAPI_SECTOR_SIZE, buf);
	
	return ret;
}

atapi_capacity atapi_device_capacity(btos_api::hwpnp::IATABus *bus, size_t index){
	uint8_t capacity_cmd[12] = {0x25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	atapi_capacity buf;
	auto len = atapi_scsi_command(bus, index, capacity_cmd, sizeof(buf), (uint8_t*)&buf);
	buf.block_size = __builtin_bswap32(buf.block_size);
	buf.total_blocks = __builtin_bswap32(buf.total_blocks);
	//dbgpf("ATAPI: %x %x\n", buf.block_size, buf.total_blocks);
	if(len != sizeof(buf)) panic("(ATAPI) Could not read capacity!");
	if(buf.block_size != ATAPI_SECTOR_SIZE) panic("(ATAPI) Unsupported block size.");
	return buf;
}

ATAPIDevice::ATAPIDevice(btos_api::hwpnp::IATABus *b, size_t i) : 
	bus(b), index(i), node(this), capacity(atapi_device_capacity(bus, index))
{}

btos_api::hwpnp::DeviceID ATAPIDevice::GetID(){
	return ATAPIDeviceID;
}

const char *ATAPIDevice::GetDescription(){
	return "ATAPI optical drive";
}

size_t ATAPIDevice::GetSubDeviceCount(){
	return 1;
}

btos_api::hwpnp::DeviceID ATAPIDevice::GetSubDevice(size_t index){
	if(index == 0) return VolumeDeviceID;
	return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *ATAPIDevice::GetDriver(){
	return GetATAPIDriver();
}

btos_api::hwpnp::IDeviceNode *ATAPIDevice::GetDeviceNode(){
	return &node;
}
	
bool ATAPIDevice::ReadSector(uint64_t lba, uint8_t *buf){
	if(!cache){
		if(btos_api::IsCacheLoaded()) cache = btos_api::CreateCache(ATAPI_SECTOR_SIZE, 1024);
	}
	if(cache && cache->Retrieve(lba, (char*)buf)) return true;
	auto lock = bus->GetLock();
	auto ret = atapi_device_read(bus, index, lba, buf) == ATAPI_SECTOR_SIZE;
	if(ret && cache) cache->Store(lba, (char*)buf);
	return ret;
}

bool ATAPIDevice::WriteSector(uint64_t, const uint8_t*){
	//Not supported
	return false;
}

size_t ATAPIDevice::GetSectorSize(){
	return ATAPI_SECTOR_SIZE;
}

bt_filesize_t ATAPIDevice::GetSize(){
	auto size = capacity.total_blocks * ATAPI_SECTOR_SIZE;
	//dbgpf("ATAPI: Size: %i\n", (int)size);
	return size;
}

ATAPIDeviceNode::ATAPIDeviceNode(ATAPIDevice *dev) : btos_api::hwpnp::BlockDeviceNode(dev) {}

const char *ATAPIDeviceNode::GetBaseName(){
	return "ATAPI";
}
