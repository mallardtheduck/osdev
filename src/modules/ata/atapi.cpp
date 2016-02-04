#include <btos_module.h>
#include <util/holdlock.hpp>
#include "ata.hpp"

void atapi_test(ata_device *dev);

void atapi_device_init(ata_device *dev){
	dbgpf("ATA: Initializing ATAPI device on bus %d\n", dev->io_base);

	outb(dev->io_base + ATA_REG_ERROR, 1);
	outb(dev->control, 0);

	outb(dev->io_base + ATA_REG_HDDEVSEL, 0xA0 | dev->slave << 4);
	ata_io_wait(dev);

	outb(dev->io_base + ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
	ata_io_wait(dev);

	int status = inb(dev->io_base + ATA_REG_COMMAND);
	dbgpf("ATA: Device status: %d\n", status);

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
	dbgpf("ATA: Sectors (48): %d\n", (uint32_t)dev->identity.sectors_48);
	dbgpf("ATA: Sectors (24): %d\n", dev->identity.sectors_28);
	
	dev->atapi_packet_size = 0xFF;
	if((dev->identity.flags & 0x03) == 0) dev->atapi_packet_size = 12;
	if((dev->identity.flags & 0x03) == 1) dev->atapi_packet_size = 16;
	dbgpf("ATA: ATAPI Packet size: %d (%i)\n", (int)dev->atapi_packet_size, (int)(dev->identity.flags & 0x03));
	

	outb(dev->control, 0);
	
	//atapi_test(dev);
}

size_t atapi_scsi_command(ata_device *dev, uint8_t cmd[12], size_t size, uint8_t *buf){
	uint16_t bus = dev->io_base;
	uint8_t slave = dev->slave;
	dbgpf("ATA: Executing ATAPI SCSI command: %x\n", cmd[0]);
	
	outb(dev->io_base + ATA_REG_HDDEVSEL, slave << 4);
	ata_wait(dev, 0);
	outb(dev->control, 0x00);
	outb(bus + ATA_REG_FEATURES, 0x00);
	outb(bus + ATA_REG_LBA1, (size & 0x000000ff) >> 0);
	outb(bus + ATA_REG_LBA2, (size & 0x0000ff00) >> 8);
	outb(bus +  ATA_REG_COMMAND, ATA_CMD_PACKET);
	ata_wait(dev, 0);
	while(!(inb(dev->control) & ATA_SR_DRQ));
	ata_reset_wait(bus);
	for(size_t i=0; i<6; ++i){
		out16(bus, ((uint16_t*)cmd)[i]);
	}
	ata_wait_irq(bus);
	ata_reset_wait(bus);
	size_t read = inb(bus + ATA_REG_LBA1) + (inb(bus + ATA_REG_LBA2) << 8);
	for(size_t i=0; i<read/2; ++i){
		((uint16_t*)buf)[i] = in16(bus);
	}
	ata_wait(dev, 0);
	return read;
}

int atapi_device_read(ata_device *dev, uint32_t lba, uint8_t *buf){
	uint8_t read_cmd[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	read_cmd[9] = 1;              /* 1 sector */
	read_cmd[2] = (lba >> 0x18) & 0xFF;   /* most sig. byte of LBA */
	read_cmd[3] = (lba >> 0x10) & 0xFF;
	read_cmd[4] = (lba >> 0x08) & 0xFF;
	read_cmd[5] = (lba >> 0x00) & 0xFF;
	dbgpf("ATA: Read ATAPI sector %i.\n", lba);
	
	return atapi_scsi_command(dev, read_cmd, 2048, buf);
}

struct atapi_instance{
	ata_device *dev;
	size_t pos;
};

void *atapi_open(void *id){
    hold_lock hl(&ata_drv_lock);
	atapi_instance *instance=new atapi_instance();
	instance->dev=(ata_device*)id;
	instance->pos=0;
	return instance;
}

bool atapi_close(void *instance){
    hold_lock hl(&ata_drv_lock);
	if(instance){
		delete (ata_device*) instance;
		return true;
	}else return false;
}

size_t atapi_read(void *instance, size_t bytes, char *buf){
    hold_lock hl(&ata_drv_lock);
	if(bytes % ATAPI_SECTOR_SIZE) return 0;
	atapi_instance *inst=(atapi_instance*)instance;
	for(size_t i=0; i<bytes; i+=ATAPI_SECTOR_SIZE){
        if(!cache_get((size_t)inst->dev, inst->pos/ATAPI_SECTOR_SIZE, &buf[i])) {
            release_lock(&ata_drv_lock);
            atapi_queued_read(inst->dev, inst->pos / ATAPI_SECTOR_SIZE, (uint8_t *) &buf[i]);
            take_lock(&ata_drv_lock);
            cache_add((size_t)inst->dev, inst->pos/ATAPI_SECTOR_SIZE, &buf[i]);
        }
		inst->pos+=ATAPI_SECTOR_SIZE;
	}
	return bytes;
}

size_t atapi_write(void */*instance*/, size_t /*bytes*/, char */*buf*/){
    return 0;
}

size_t atapi_seek(void *instance, size_t pos, uint32_t flags){
	atapi_instance *inst=(atapi_instance*)instance;
	if(pos % ATAPI_SECTOR_SIZE) return inst->pos;
	if(flags & FS_Relative) inst->pos+=pos;
	else if(flags & FS_Backwards){
		inst->pos = (inst->dev->identity.sectors_48 * ATAPI_SECTOR_SIZE) - pos;
	}else if(flags == (FS_Relative | FS_Backwards)) inst->pos-=pos;
	else inst->pos=pos;
	return inst->pos;
}

int atapi_ioctl(void */*instance*/, int /*fn*/, size_t /*bytes*/, char */*buf*/){
	return 0;
}

int atapi_type(){
	return driver_types::STR_OPTICAL;
}

char *atapi_desc(){
	return (char*)"ATAPI Optical drive";
}

drv_driver atapi_driver={&atapi_open, &atapi_close, &atapi_read, &atapi_write, &atapi_seek, &atapi_ioctl, &atapi_type, &atapi_desc};

void atapi_test(ata_device *dev){
	uint8_t buf[2048] = {0};
	atapi_device_read(dev, 0, buf);
	
	dbgpf("ATAPI TEST: %x %x %x\n", (int)buf[0], (int)buf[1], (int)buf[2]);
}