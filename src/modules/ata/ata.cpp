#include "module_stubs.h"
#include "io.h"
#include "ata.hpp"
#include "module_cpp.hpp"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-function"

drv_driver ata_driver;

struct ata_device {
	int io_base;
	int control;
	int slave;
	ata_identify_t identity;
};

lock ata_lock;

/* TODO support other sector sizes */
#define ATA_SECTOR_SIZE 512


static void ata_io_wait(struct ata_device * dev) {
	inb(dev->io_base + ATA_REG_ALTSTATUS);
	inb(dev->io_base + ATA_REG_ALTSTATUS);
	inb(dev->io_base + ATA_REG_ALTSTATUS);
	inb(dev->io_base + ATA_REG_ALTSTATUS);
}


static int ata_wait(struct ata_device * dev, int advanced) {
	uint8_t status = 0;

	ata_io_wait(dev);

	while ((status = inb(dev->io_base + ATA_REG_STATUS)) & ATA_SR_BSY);

	if (advanced) {
		status = inb(dev->io_base + ATA_REG_STATUS);
		if (status   & ATA_SR_ERR)  return 1;
		if (status   & ATA_SR_DF)   return 1;
		if (!(status & ATA_SR_DRQ)) return 1;
	}

	return 0;
}

static void ata_soft_reset(struct ata_device * dev) {
	outb(dev->control, 0x04);
	outb(dev->control, 0x00);
}

static void ata_device_init(struct ata_device * dev) {

	dbgpf("ATA: Initializing IDE device on bus %d\n", dev->io_base);

	outb(dev->io_base + 1, 1);
	outb(dev->control, 0);

	outb(dev->io_base + ATA_REG_HDDEVSEL, 0xA0 | dev->slave << 4);
	ata_io_wait(dev);

	outb(dev->io_base + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
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

	outb(dev->io_base + ATA_REG_CONTROL, 0x02);
}

static int ata_device_detect(struct ata_device * dev) {
	ata_soft_reset(dev);
	outb(dev->io_base + ATA_REG_HDDEVSEL, 0xA0 | dev->slave << 4);
	ata_io_wait(dev);

	unsigned char cl = inb(dev->io_base + ATA_REG_LBA1); /* CYL_LO */
	unsigned char ch = inb(dev->io_base + ATA_REG_LBA2); /* CYL_HI */

	dbgpf("ATA: Device detected: 0x%2x 0x%2x\n", cl, ch);
	if (cl == 0xFF && ch == 0xFF) {
		/* Nothing here */
		return 0;
	}
	if (cl == 0x00 && ch == 0x00) {
		/* Parallel ATA device */
		ata_device_init(dev);
		add_device("ATA", &ata_driver, (void*)dev);

		return 1;
	}

	/* TODO: ATAPI, SATA, SATAPI */
	return 0;
}

static void ata_device_read_sector(struct ata_device * dev, uint32_t lba, uint8_t * buf) {
	uint16_t bus = dev->io_base;
	uint8_t slave = dev->slave;

	take_lock(&ata_lock);

	int errors = 0;
try_again:
	outb(bus + ATA_REG_CONTROL, 0x02);

	ata_wait(dev, 0);

	outb(bus + ATA_REG_HDDEVSEL, 0xe0 | slave << 4 | (lba & 0x0f000000) >> 24);
	outb(bus + ATA_REG_FEATURES, 0x00);
	outb(bus + ATA_REG_SECCOUNT0, 1);
	outb(bus + ATA_REG_LBA0, (lba & 0x000000ff) >>  0);
	outb(bus + ATA_REG_LBA1, (lba & 0x0000ff00) >>  8);
	outb(bus + ATA_REG_LBA2, (lba & 0x00ff0000) >> 16);
	outb(bus + ATA_REG_COMMAND, ATA_CMD_READ_PIO);

	if (ata_wait(dev, 1)) {
		dbgpf("ATA: Error during ATA read of lba block %d\n", lba);
		errors++;
		if (errors > 4) {
			dbgpf("ATA: -- Too many errors trying to read this block. Bailing.\n", 0);
			release_lock(&ata_lock);
			return;
		}
		goto try_again;
	}

	int size = 256;
	insm(bus,buf,size);
	ata_wait(dev, 0);
	release_lock(&ata_lock);
}

static void ata_device_write_sector(struct ata_device * dev, uint32_t lba, uint8_t * buf) {
	uint16_t bus = dev->io_base;
	uint8_t slave = dev->slave;

	take_lock(&ata_lock);

	outb(bus + ATA_REG_CONTROL, 0x02);

	ata_wait(dev, 0);
	outb(bus + ATA_REG_HDDEVSEL, 0xe0 | slave << 4 | (lba & 0x0f000000) >> 24);
	ata_wait(dev, 0);

	outb(bus + ATA_REG_FEATURES, 0x00);
	outb(bus + ATA_REG_SECCOUNT0, 0x01);
	outb(bus + ATA_REG_LBA0, (lba & 0x000000ff) >>  0);
	outb(bus + ATA_REG_LBA1, (lba & 0x0000ff00) >>  8);
	outb(bus + ATA_REG_LBA2, (lba & 0x00ff0000) >> 16);
	outb(bus + ATA_REG_COMMAND, ATA_CMD_WRITE_PIO);
	ata_wait(dev, 0);
	int size = ATA_SECTOR_SIZE / 2;
	outsm(bus,buf,size);
	outb(bus + 0x07, ATA_CMD_CACHE_FLUSH);
	ata_wait(dev, 0);
	release_lock(&ata_lock);
}

static int buffer_compare(uint32_t * ptr1, uint32_t * ptr2, size_t size) {
	if(size % 4) panic("ATA");
	size_t i = 0;
	while (i < size) {
		if (*ptr1 != *ptr2) return 1;
		ptr1++;
		ptr2++;
		i += sizeof(uint32_t);
	}
	return 0;
}

static void ata_device_write_sector_retry(struct ata_device * dev, uint32_t lba, uint8_t * buf) {
	uint8_t *read_buf = (uint8_t*) malloc(ATA_SECTOR_SIZE);
	disable_interrupts();
	do {
		ata_device_write_sector(dev, lba, buf);
		ata_device_read_sector(dev, lba, read_buf);
	} while (buffer_compare((uint32_t *)buf, (uint32_t *)read_buf, ATA_SECTOR_SIZE));
	enable_interrupts();
	free(read_buf);
}

static struct ata_device ata_primary_master   = {.io_base = 0x1F0, .control = 0x3F6, .slave = 0};
static struct ata_device ata_primary_slave    = {.io_base = 0x1F0, .control = 0x3F6, .slave = 1};
static struct ata_device ata_secondary_master = {.io_base = 0x170, .control = 0x376, .slave = 0};
static struct ata_device ata_secondary_slave  = {.io_base = 0x170, .control = 0x376, .slave = 1};


static int ata_initialize(void) {
	/* Detect drives and mount them */

	ata_device_detect(&ata_primary_master);
	ata_device_detect(&ata_primary_slave);
	ata_device_detect(&ata_secondary_master);
	ata_device_detect(&ata_secondary_slave);

	return 0;
}

static int ata_finalize(void) {

	return 0;
}

struct ata_instance{
	ata_device *dev;
	size_t pos;
};

void *ata_open(void *id){
	ata_instance *instance=new ata_instance();
	instance->dev=(ata_device*)id;
	instance->pos=0;
	return instance;
}

bool ata_close(void *instance){
	if(instance){
		delete (ata_device*) instance;
		return true;
	}else return false;
}

int ata_read(void *instance, size_t bytes, char *buf){
	if(bytes % 512) return 0;
	ata_instance *inst=(ata_instance*)instance;
	for(size_t i=0; i<bytes; i+=512){
		ata_device_read_sector(inst->dev, inst->pos/512, (uint8_t*)&buf[512*i]);
		inst->pos+=512;
	}
	return bytes;
}

bool ata_write(void *instance, size_t bytes, char *buf){
	if(bytes % 512) return false;
	ata_instance *inst=(ata_instance*)instance;
	for(size_t i=0; i<bytes; i+=512){
		ata_device_write_sector_retry(inst->dev, inst->pos/512, (uint8_t*)&buf[512*i]);
		inst->pos+=512;
	}
	return true;
}

size_t ata_seek(void *instance, size_t pos, bool relative){
	ata_instance *inst=(ata_instance*)instance;
	if(pos % 512) return inst->pos;
	if(relative) inst->pos+=pos;
	else inst->pos=pos;
	return inst->pos;
}

int ata_ioctl(void *instance, int fn, size_t bytes, char *buf){
	return 0;
}

int ata_type(){
	return driver_types::STR_HDD;
}

char *ata_desc(){
	return (char*)"ATA HDD";
}

extern "C" int module_main(syscall_table *systbl){
	drv_driver driver={ata_open, ata_close, ata_read, ata_write, ata_seek, ata_ioctl, ata_type, ata_desc};
	ata_driver=driver;
	SYSCALL_TABLE=systbl;
	init_lock(&ata_lock);
	ata_initialize();
    return 0;
}