#include <btos_module.h>
#include <util/holdlock.hpp>
#include "ata.hpp"

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wunused-function"

drv_driver ata_driver;

lock ata_lock, ata_drv_lock;

void out_bytes(char *bytes, size_t count){
	for(size_t i=0; i<count; ++i){
		dbgpf("%2x", bytes[i]);
	}
	dbgout("\n");
}

void ata_io_wait(struct ata_device * dev) {
	inb(dev->control);
	inb(dev->control);
	inb(dev->control);
	inb(dev->control);
}


int ata_wait(struct ata_device * dev, int advanced) {
	uint8_t status = 0;

	ata_io_wait(dev);

	while ((status = inb(dev->io_base + ATA_REG_STATUS)) & ATA_SR_BSY) {
        //dbgpf("ATA: Status: %x\n", inb(dev->io_base + ATA_REG_STATUS));
        yield();
    }

	if (advanced) {
		status = inb(dev->io_base + ATA_REG_STATUS);
		if (status   & ATA_SR_ERR) {
            dbgpf("ATA: ATA_SR_ERR\n");
            return 1;
        }
		if (status   & ATA_SR_DF)   {
            dbgpf("ATA: ATA_SR_DF\n");
            return 1;
        }
		if (!(status & ATA_SR_DRQ)) {
            dbgpf("ATA: ATA_SR_DRQ\n");
            return 1;
        }
	}

	return 0;
}

int ata_wait(btos_api::hwpnp::IATABus *bus, size_t index, int advanced) {
	uint8_t status = 0;

	bus->ReadControlByte(index);
	bus->ReadControlByte(index);
	bus->ReadControlByte(index);
	bus->ReadControlByte(index);

	while ((status = bus->InByte(index, ATA_REG_STATUS)) & ATA_SR_BSY) {
        //dbgpf("ATA: Status: %x\n", inb(dev->io_base + ATA_REG_STATUS));
        yield();
    }

	if (advanced) {
		status = bus->InByte(index, ATA_REG_STATUS);
		if (status   & ATA_SR_ERR) {
            dbgpf("ATA: ATA_SR_ERR\n");
            return 1;
        }
		if (status   & ATA_SR_DF)   {
            dbgpf("ATA: ATA_SR_DF\n");
            return 1;
        }
		if (!(status & ATA_SR_DRQ)) {
            dbgpf("ATA: ATA_SR_DRQ\n");
            return 1;
        }
	}

	return 0;
}

static void ata_soft_reset(struct ata_device * dev) {
	outb(dev->control, 0x04);
	outb(dev->control, 0x00);
}

static bool ata_device_init(struct ata_device * dev) {

	dbgpf("ATA: Initializing IDE device on bus %d\n", dev->io_base);

	outb(dev->io_base + ATA_REG_ERROR, 1);
	outb(dev->control, 0);

	outb(dev->io_base + ATA_REG_HDDEVSEL, 0xA0 | dev->slave << 4);
	ata_io_wait(dev);

	outb(dev->io_base + ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
	ata_io_wait(dev);

	int status = inb(dev->io_base + ATA_REG_COMMAND);
	dbgpf("ATA: Device status: %d\n", status);

	if(status == 0 || (status & ATA_SR_ERR)) {
		dbgpf("ATA: Device does not exist or not ATA.\n");
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
	ptr[39] = '\0';
	
	dbgpf("ATA: Device Name:  %s\n", dev->identity.model);
	dbgpf("ATA: Sectors (48): %d\n", (uint32_t)dev->identity.sectors_48);
	dbgpf("ATA: Sectors (28): %d\n", dev->identity.sectors_28);
	if(dev->identity.sectors_48 != 0) dev->length = dev->identity.sectors_48;
	else dev->length = dev->identity.sectors_28;
	dbgpf("ATA: Length: %i\n", (int)dev->length);
	if(dev->length == (uint64_t)-1) return false;

	outb(dev->control, 0);
	return true;
}

static int ata_device_detect(struct ata_device * dev, ATABusDevice *parent) {
	ata_soft_reset(dev);
	outb(dev->io_base + ATA_REG_HDDEVSEL, 0xA0 | dev->slave << 4);
	ata_io_wait(dev);

	unsigned char cl = inb(dev->io_base + ATA_REG_LBA1); /* CYL_LO */
	unsigned char ch = inb(dev->io_base + ATA_REG_LBA2); /* CYL_HI */

	dbgpf("ATA: Device detected: 0x%2x 0x%2x\n", cl, ch);
	if (cl == 0xFF && ch == 0xFF) {
		/* Nothing here */
		dbgout("ATA: No device.\n");
		return 0;
	}else{
		if(ata_device_init(dev)){
			btos_api::hwpnp::DeviceID id = HDDDeviceID;
			parent->devices.push_back({id, dev});
			return 1;
		}else if(atapi_device_init(dev)){
			btos_api::hwpnp::DeviceID id = ATAPIDeviceID;
			parent->devices.push_back({id, dev});
			return 1;
		}
	}
	return 0;
}

bool ata_device_read_sector(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t * buf){
    //take_lock(&ata_lock);
    /*if(init_dma()){
        dma_read_sector(bus, index, lba, buf);
    }else{*/
        auto ret = ata_device_read_sector_pio(bus, index, lba, buf);
    //}
    //release_lock(&ata_lock);
    return ret;
}

bool ata_device_read_sector_pio(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t * buf) {
	//if(lba > dev->length) return;
	int slave = bus->IsSlave(index);

	int errors = 0;
try_again:
	bus->WriteControlByte(index, 0);

	ata_wait(bus, index, 0);

	bus->OutByte(index, ATA_REG_HDDEVSEL, 0xe0 | slave << 4 | (lba & 0x0f000000) >> 24);
	//outb(bus + ATA_REG_FEATURES, 0x00);
	bus->OutByte(index, ATA_REG_SECCOUNT0, 1);
	bus->OutByte(index, ATA_REG_LBA0, (lba & 0x000000ff) >>  0);
	bus->OutByte(index, ATA_REG_LBA1, (lba & 0x0000ff00) >>  8);
	bus->OutByte(index, ATA_REG_LBA2, (lba & 0x00ff0000) >> 16);
	bus->OutByte(index, ATA_REG_COMMAND, ATA_CMD_READ_PIO);

	if (ata_wait(bus, index, 1)) {
		dbgpf("ATA: Error during ATA read of lba block %d\n", lba);
		errors++;
		if (errors > 4) {
			dbgpf("ATA: -- Too many errors trying to read this block. Bailing.\n");
			return false;
		}
		goto try_again;
	}

	int size = 256;
	bus->InWords(index, ATA_REG_DATA, size, buf);
	ata_wait(bus, index, 0);
	return true;
}

bool ata_device_write_sector(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t * buf) {
	//if(lba > dev->length) return;
    //take_lock(&ata_lock);
    int slave = bus->IsSlave(index);

    //if(init_dma()){} //TODO: Use DMA

	bus->WriteControlByte(index, 0);

	ata_wait(bus, index, 0);
	bus->OutByte(index, ATA_REG_HDDEVSEL, 0xe0 | slave << 4 | (lba & 0x0f000000) >> 24);
	ata_wait(bus, index, 0);

	//outb(bus + ATA_REG_FEATURES, 0x00);
	bus->OutByte(index, ATA_REG_SECCOUNT0, 0x01);
	bus->OutByte(index, ATA_REG_LBA0, (lba & 0x000000ff) >>  0);
	bus->OutByte(index, ATA_REG_LBA1, (lba & 0x0000ff00) >>  8);
	bus->OutByte(index, ATA_REG_LBA2, (lba & 0x00ff0000) >> 16);
	bus->OutByte(index, ATA_REG_COMMAND, ATA_CMD_WRITE_PIO);
	ata_wait(bus, index, 0);
	int size = ATA_SECTOR_SIZE / 2;
	bus->OutWords(index, ATA_REG_DATA, size, buf);
	bus->OutByte(index, ATA_REG_COMMAND, ATA_CMD_CACHE_FLUSH);
	ata_wait(bus, index, 0);
	//release_lock(&ata_lock);
	return true;
}

/*static int buffer_compare(uint32_t * ptr1, uint32_t * ptr2, size_t size) {
	if(size % 4) panic("ATA");
	size_t i = 0;
	while (i < size) {
		if (*ptr1 != *ptr2) return 1;
		ptr1++;
		ptr2++;
		i += sizeof(uint32_t);
	}
	return 0;
}*/

/*void ata_device_write_sector_retry(struct ata_device * dev, uint32_t lba, uint8_t * buf) {
	uint8_t *read_buf = (uint8_t*) malloc(ATA_SECTOR_SIZE);
	disable_interrupts();
	do {
		ata_device_write_sector(dev, lba, buf);
		ata_device_read_sector(dev, lba, read_buf);
	} while (buffer_compare((uint32_t *)buf, (uint32_t *)read_buf, ATA_SECTOR_SIZE));
	enable_interrupts();
	free(read_buf);
}*/

static struct ata_device ata_primary_master   = {.io_base = 0x1F0, .control = 0x3F6, .slave = 0};
static struct ata_device ata_primary_slave    = {.io_base = 0x1F0, .control = 0x3F6, .slave = 1};
static struct ata_device ata_secondary_master = {.io_base = 0x170, .control = 0x376, .slave = 0};
static struct ata_device ata_secondary_slave  = {.io_base = 0x170, .control = 0x376, .slave = 1};


static int ata_initialize(ATABusDevice *parent) {
	/* Detect drives and mount them */

	ata_device_detect(&ata_primary_master, parent);
	ata_device_detect(&ata_primary_slave, parent);
	ata_device_detect(&ata_secondary_master, parent);
	ata_device_detect(&ata_secondary_slave, parent);

	return 0;
}

/*static int ata_finalize(void) {

	return 0;
}*/

/*extern "C" int module_main(syscall_table *systbl, char *params){
	drv_driver driver={ata_open, ata_close, ata_read, ata_write, ata_seek, ata_ioctl, ata_type, ata_desc};
	ata_driver=driver;
	SYSCALL_TABLE=systbl;
    dbgout("ATA: Init...\n");
	init_lock(&ata_lock);
    init_lock(&ata_drv_lock);
    init_queue();
	preinit_dma();
	ata_initialize();
    return 0;
}*/

ATABusDevice::ATABusDevice(){
	dbgout("ATA: Init...\n");
	init_lock(&ata_lock);
    init_lock(&ata_drv_lock);
    //init_queue();
	preinit_dma();
	ata_initialize(this);
}

void ATABusDevice::Lock(){
	take_lock(&ata_lock);
}

void ATABusDevice::Unlock(){
	release_lock(&ata_lock);
}

btos_api::hwpnp::DeviceID ATABusDevice::GetID(){
	return PCATADeviceID;
}

const char *ATABusDevice::GetDescription(){
	return "ATA storage bus";
}

size_t ATABusDevice::GetSubDeviceCount(){
	return devices.size();
}

btos_api::hwpnp::DeviceID ATABusDevice::GetSubDevice(size_t idx){
	if(idx < devices.size()) return devices[idx].id;
	else return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *ATABusDevice::GetDriver(){
	return GetATADriver();
}

void ATABusDevice::OutByte(size_t i, size_t reg, uint8_t byte){
	if(i < devices.size()){
		outb(devices[i].dev->io_base + reg, byte);
	}
}

void ATABusDevice::OutWord(size_t i, size_t reg, uint16_t word){
	if(i < devices.size()){
		out16(devices[i].dev->io_base + reg, word);
	}
}

void ATABusDevice::OutWords(size_t i, size_t reg, size_t count, const uint8_t *buffer){
	if(i < devices.size()){
		outsm(devices[i].dev->io_base + reg, (uint8_t*)buffer, count);
	}
}

uint8_t ATABusDevice::InByte(size_t i, size_t reg){
	if(i < devices.size()){
		return inb(devices[i].dev->io_base + reg);
	}
	return 0;
}

uint16_t ATABusDevice::InWord(size_t i, size_t reg){
	if(i < devices.size()){
		return in16(devices[i].dev->io_base + reg);
	}
	return 0;
}

void ATABusDevice::InWords(size_t i, size_t reg, size_t count, uint8_t *buffer){
	if(i < devices.size()){
		insm(devices[i].dev->io_base + reg, buffer, count);
	}
}

uint8_t ATABusDevice::ReadControlByte(size_t i){
	if(i < devices.size()){
		return inb(devices[i].dev->control);
	}
	return 0;
}

void ATABusDevice::WriteControlByte(size_t i, uint8_t byte){
	if(i < devices.size()){
		outb(devices[i].dev->control, byte);
	}
}

bool ATABusDevice::IsSlave(size_t i){
	if(i < devices.size()){
		return !!devices[i].dev->slave;
	}
	return false;
}

uint64_t ATABusDevice::GetLength(size_t i){
	if(i < devices.size()){
		return devices[i].dev->length;
	}
	return 0;
}

void ATABusDevice::ResetIntWait(size_t i){
	if(i < devices.size()){
		ata_reset_wait(devices[i].dev->io_base);
	}
}

void ATABusDevice::WaitInt(size_t i){
	if(i < devices.size()){
		ata_wait_irq(devices[i].dev->io_base);
	}
}

ATAHDDDeviceNode::ATAHDDDeviceNode(ATAHDDDevice *dev) : btos_api::hwpnp::BlockDeviceNode(dev) {}

const char *ATAHDDDeviceNode::GetBaseName(){
	return "ATA";
}

btos_api::hwpnp::DeviceID ATAHDDDevice::GetID(){
	return HDDDeviceID;
}

const char *ATAHDDDevice::GetDescription(){
	return "ATA fixed disk drive";
}

size_t ATAHDDDevice::GetSubDeviceCount(){
	return 1;
}

btos_api::hwpnp::DeviceID ATAHDDDevice::GetSubDevice(size_t i){
	if(i != 0) return btos_api::hwpnp::NullDeviceID;
	else return VolumeDeviceID;
}

btos_api::hwpnp::IDriver *ATAHDDDevice::GetDriver(){
	return GetATAHDDDriver();
}

btos_api::hwpnp::IDeviceNode *ATAHDDDevice::GetDeviceNode(){
	return &node;
}
	
bool ATAHDDDevice::ReadSector(uint64_t lba, uint8_t *buf){
	if(!cache){
		if(btos_api::IsCacheLoaded()) cache = btos_api::CreateCache(ATA_SECTOR_SIZE, 4096);
	}
	if(cache && cache->Retrieve(lba, (char*)buf)) return true;
	auto lock = bus->GetLock();
	auto ret = ata_device_read_sector(bus, index, lba, buf);
	if(ret && cache) cache->Store(lba, (char*)buf);
	return ret;
}

bool ATAHDDDevice::WriteSector(uint64_t lba, const uint8_t *buf){
	if(cache) cache->Drop(lba);
	auto lock = bus->GetLock();
	return ata_device_write_sector(bus, index, lba, (uint8_t*)buf);
}

size_t ATAHDDDevice::GetSectorSize(){
	return ATA_SECTOR_SIZE;
}

bt_filesize_t ATAHDDDevice::GetSize(){
	return bus->GetLength(index) * ATA_SECTOR_SIZE;
}
