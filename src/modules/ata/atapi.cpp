#include <btos_module.h>
#include <util/holdlock.hpp>
#include "ata.hpp"

void atapi_test(ata_device *dev);

void atapi_device_init(ata_device *dev){
	dbgpf("ATA: Initializing ATAPI device on bus %d\n", dev->io_base);

	outb(dev->io_base + 1, 1);
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

	outb(dev->io_base + ATA_REG_CONTROL, 0);
	
	atapi_test(dev);
}

void atapi_device_read(ata_device *dev, uint32_t lba, uint8_t *buf){
	uint16_t bus = dev->io_base;
	uint8_t slave = dev->slave;
	size_t errors;

	uint8_t read_cmd[12] = { 0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	
try_again:
	dbgout("ATAPI: 0\n");
	outb(bus + ATA_REG_CONTROL, 0);

	ata_wait(dev, 0);
	dbgout("ATAPI: 1\n");

	outb(bus + ATA_REG_HDDEVSEL, slave << 4);
	ata_wait(dev, 0);
	outb(bus + ATA_REG_FEATURES, 0x00);
	outb(bus + ATA_REG_LBA1, (lba & 0x0000ff00) >>  8);
	outb(bus + ATA_REG_LBA2, (lba & 0x00ff0000) >> 16);
	dbgout("ATAPI: 2\n");
	ata_reset_wait(bus);
	outb(bus + ATA_REG_COMMAND, ATA_CMD_PACKET);
	dbgout("ATAPI: 3\n");
	ata_wait_irq(bus);
	dbgout("ATAPI: 4\n");
	ata_reset_wait(bus);
	dbgout("ATAPI: 5\n");
	outsm(bus, read_cmd, 6);
	dbgout("ATAPI: 6\n");
	ata_wait_irq(bus);
	dbgout("ATAPI: 7\n");

	if (ata_wait(dev, 1)) {
		dbgpf("ATA: Error during ATAPI read of lba block %d\n", lba);
		errors++;
		if (errors > 4) {
			dbgpf("ATA: -- Too many errors trying to read this block. Bailing.\n", 0);
			return;
		}
		goto try_again;
	}

	int size = 256;
	insm(bus,buf,size);
	ata_wait(dev, 0);
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
	if(bytes % 512) return 0;
	atapi_instance *inst=(atapi_instance*)instance;
	for(size_t i=0; i<bytes; i+=512){
        if(!cache_get((size_t)inst->dev, inst->pos/512, &buf[i])) {
            release_lock(&ata_drv_lock);
            atapi_queued_read(inst->dev, inst->pos / 512, (uint8_t *) &buf[i]);
            take_lock(&ata_drv_lock);
            cache_add((size_t)inst->dev, inst->pos/512, &buf[i]);
        }
		inst->pos+=512;
	}
	return bytes;
}

size_t atapi_write(void */*instance*/, size_t /*bytes*/, char */*buf*/){
    return 0;
}

size_t atapi_seek(void *instance, size_t pos, uint32_t flags){
	atapi_instance *inst=(atapi_instance*)instance;
	if(pos % 512) return inst->pos;
	if(flags & FS_Relative) inst->pos+=pos;
	else if(flags & FS_Backwards){
		inst->pos = (inst->dev->identity.sectors_48 * 512) - pos;
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
	uint8_t buf[512];
	atapi_device_read(dev, 0, buf);
	
	dbgpf("ATAPI TEST: %x %x %x\n", (int)buf[0], (int)buf[1], (int)buf[2]);
	panic("q");
}