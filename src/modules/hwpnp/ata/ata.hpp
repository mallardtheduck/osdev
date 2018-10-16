#ifndef ATA_HPP
#define ATA_HPP
#include <btos_module.h>
#include <dev/hwpnp.hpp>
#include <dev/hwpnp/atabus.hpp>
#include <dev/hwpnp/hdd.hpp>
#include <util/ministl.hpp>

static const btos_api::hwpnp::DeviceID PCATADeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 2
};

static const btos_api::hwpnp::DeviceID HDDDeviceID = {btos_api::hwpnp::PNPBUS::ATA, 0, 0, 0, 0, btos_api::hwpnp::ATADeviceType::HDD};
static const btos_api::hwpnp::DeviceID ATAPIDeviceID = {btos_api::hwpnp::PNPBUS::ATA, 0, 0, 0, 0, btos_api::hwpnp::ATADeviceType::ATAPI};

#define ATA_SR_BSY     0x80
#define ATA_SR_DRDY    0x40
#define ATA_SR_DF      0x20
#define ATA_SR_DSC     0x10
#define ATA_SR_DRQ     0x08
#define ATA_SR_CORR    0x04
#define ATA_SR_IDX     0x02
#define ATA_SR_ERR     0x01

#define ATA_ER_BBK      0x80
#define ATA_ER_UNC      0x40
#define ATA_ER_MC       0x20
#define ATA_ER_IDNF     0x10
#define ATA_ER_MCR      0x08
#define ATA_ER_ABRT     0x04
#define ATA_ER_TK0NF    0x02
#define ATA_ER_AMNF     0x01

#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

#define ATAPI_CMD_READ       0xA8
#define ATAPI_CMD_EJECT      0x1B

#define ATA_IDENT_DEVICETYPE   0
#define ATA_IDENT_CYLINDERS    2
#define ATA_IDENT_HEADS        6
#define ATA_IDENT_SECTORS      12
#define ATA_IDENT_SERIAL       20
#define ATA_IDENT_MODEL        54
#define ATA_IDENT_CAPABILITIES 98
#define ATA_IDENT_FIELDVALID   106
#define ATA_IDENT_MAX_LBA      120
#define ATA_IDENT_COMMANDSETS  164
#define ATA_IDENT_MAX_LBA_EXT  200

#define IDE_ATA        0x00
#define IDE_ATAPI      0x01

#define ATA_MASTER     0x00
#define ATA_SLAVE      0x01

#define ATA_REG_DATA       0x00
#define ATA_REG_ERROR      0x01
#define ATA_REG_FEATURES   0x01
#define ATA_REG_SECCOUNT0  0x02
#define ATA_REG_LBA0       0x03
#define ATA_REG_LBA1       0x04
#define ATA_REG_LBA2       0x05
#define ATA_REG_HDDEVSEL   0x06
#define ATA_REG_COMMAND    0x07
#define ATA_REG_STATUS     0x07
#define ATA_REG_SECCOUNT1  0x08
#define ATA_REG_LBA3       0x09
#define ATA_REG_LBA4       0x0A
#define ATA_REG_LBA5       0x0B
//#define ATA_REG_CONTROL    0x0C
//#define ATA_REG_ALTSTATUS  0x0C
#define ATA_REG_DEVADDRESS 0x0D

// Channels:
#define ATA_PRIMARY      0x00
#define ATA_SECONDARY    0x01

// Directions:
#define ATA_READ      0x00
#define ATA_WRITE     0x01

typedef struct {
	uint16_t base;
	uint16_t ctrl;
	uint16_t bmide;
	uint16_t nien;
} ide_channel_regs_t;

typedef struct {
	uint8_t  reserved;
	uint8_t  channel;
	uint8_t  drive;
	uint16_t type;
	uint16_t signature;
	uint16_t capabilities;
	uint32_t command_sets;
	uint32_t size;
	uint8_t  model[41];
} ide_device_t;

typedef struct {
	uint8_t  status;
	uint8_t  chs_first_sector[3];
	uint8_t  type;
	uint8_t  chs_last_sector[3];
	uint32_t lba_first_sector;
	uint32_t sector_count;
} partition_t;

typedef struct {
	uint16_t flags;
	uint16_t unused1[9];
	char     serial[20];
	uint16_t unused2[3];
	char     firmware[8];
	char     model[40];
	uint16_t sectors_per_int;
	uint16_t unused3;
	uint16_t capabilities[2];
	uint16_t unused4[2];
	uint16_t valid_ext_data;
	uint16_t unused5[5];
	uint16_t size_of_rw_mult;
	uint32_t sectors_28;
	uint16_t unused6[38];
	uint64_t sectors_48;
	uint16_t unused7[152];
} __attribute__((packed)) ata_identify_t;

typedef struct {
	uint8_t     boostrap[446];
	partition_t partitions[4];
	uint8_t     signature[2];
} __attribute__((packed)) mbr_t;

struct ata_device {
    int io_base;
    int control;
    int slave;
	size_t atapi_packet_size;
    ata_identify_t identity;
	uint64_t length;
};

extern lock ata_lock, ata_drv_lock;

void ata_device_read_sector(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t * buf);
void ata_device_read_sector_pio(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t * buf);
void ata_device_write_sector_retry(struct ata_device * dev, uint32_t lba, uint8_t * buf);
void init_queue();
void ata_queued_read(ata_device *dev, uint32_t lba, uint8_t *buf);
void ata_queued_write(ata_device *dev, uint32_t lba, uint8_t *buf);

size_t atapi_queued_read(ata_device *dev, uint32_t lba, uint8_t *buf);

int ata_wait(struct ata_device * dev, int advanced);

void mbr_parse(char* device);

/* TODO support other sector sizes */
#define ATA_SECTOR_SIZE 512
#define ATAPI_SECTOR_SIZE 2048

void cache_add(size_t deviceid, size_t sector, char *data);
bool cache_get(size_t deviceid, size_t sector, char *data);
void cache_drop(size_t deviceid, size_t sector);

//void preinit_dma();
//bool init_dma();
//void dma_read_sector(ata_device *dev, uint32_t lba, uint8_t *buf);

extern drv_driver atapi_driver;
bool atapi_device_init(ata_device *dev);
void ata_io_wait(struct ata_device * dev);
int atapi_device_read(ata_device *dev, uint32_t lba, uint8_t *buf);
void ata_reset_wait(uint32_t bus);
void ata_wait_irq(uint32_t bus);

btos_api::hwpnp::IDriver *GetATADriver();

class ATABusDevice : public btos_api::hwpnp::IATABus{
public:
	struct ATADevice{
		btos_api::hwpnp::DeviceID id;
		ata_device *dev;
	};

	vector<ATADevice> devices;

	ATABusDevice();

	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	
	void OutByte(size_t index, size_t reg, uint8_t byte);
	void OutWord(size_t index, size_t reg, uint16_t word);
	void OutWords(size_t index, size_t reg, size_t count, const uint8_t *buffer);
	uint8_t InByte(size_t index, size_t reg);
	void InWords(size_t index, size_t reg, size_t count, uint8_t *buffer);
	uint8_t ReadControlByte(size_t index);
	void WriteControlByte(size_t index, uint8_t byte);
	bool IsSlave(size_t index);
};

class ATAHDDDevice;

class ATAHDDDeviceNode : public btos_api::hwpnp::HDDDeviceNode{
public:
	ATAHDDDeviceNode(ATAHDDDevice *dev);

	const char *GetBaseName();
};

class ATAHDDDevice : public btos_api::hwpnp::IHDDDevice{
private:
	btos_api::hwpnp::IATABus *bus;
	size_t index;
	ATAHDDDeviceNode node;
public:
	ATAHDDDevice(btos_api::hwpnp::IATABus *b, size_t i) : bus(b), index(i), node(this) {}

	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	btos_api::hwpnp::IDeviceNode *GetDeviceNode();
	
	void ReadSector(uint64_t lba, uint8_t *buf);
	void WriteSector(uint64_t lba, const uint8_t *buf);
	size_t GetSectorSize();
};

btos_api::hwpnp::IDriver *GetATAHDDDriver();

#endif