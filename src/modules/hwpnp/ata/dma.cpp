#include "ata.hpp"

static bool dma_init=false;
/*
pci_call_table *PCI_CALL_TABLE;

const int DMA_ON = 1;
const int DMA_READ = 8;
*/
const int bus0_io_base=0x1F0;
const int bus1_io_base=0x170;
/*
struct prd{
	uint32_t data;
	uint16_t bytes;
	uint16_t reserved;

	prd() : reserved((1 << 15)) {}
} __attribute__((packed));

prd bus0prd __attribute__((aligned(8))), bus1prd __attribute__((aligned(8)));
lock dma_lock, dma_init_lock;*/

uint32_t bmr;
volatile bool bus0done, bus1done;

void dma_int_handler(ICPUState &state){
	//dbgpf("ATA: IRQ %i\n", irq);
	if(dma_init){
		uint8_t bus0status=inb(bmr+0x02);
		uint8_t bus1status=inb(bmr+0x0A);
		if(bus0status & 0x04){
			dbgpf("ATA: Bus 0 interrupt!\n");
			dbgpf("ATA: Bus 0 status: %x\n", bus0status);
			bus0done=true;
			outb(bmr+0x02, 0x04);
		}
		if(bus1status & 0x04){
			dbgpf("ATA: Bus 1 interrupt!\n");
			dbgpf("ATA: Bus 1 status: %x\n", bus1status);
			bus1done=true;
			outb(bmr+0x0A, 0x04);
		}
	}
	/*if(!bus0done && irq == 14){
		dbgout("ATA: Bus 0 IRQ\n");
	}
	if(!bus1done && irq == 15){
		dbgout("ATA: Bus 1 IRQ\n");
	}*/
	auto irq = state.GetIRQNo();
	if(irq == 14) bus0done = true;
	if(irq == 15) bus1done = true;
	API->GetHAL().AcknowlegdeIRQ(irq);
	/*enable_interrupts();
	yield();*/
}


bool dma_blockcheck(void *q){
	return *(bool*)q;
}

void ata_reset_wait(uint32_t bus){
	if(bus == bus0_io_base){
		bus0done = false;
	}else if(bus == bus1_io_base){
		bus1done = false;
	}else{
		panic("ATA: Unknown device!");
	}
}

void ata_wait_irq(uint32_t bus){
	void *blockptr;
	if(bus == bus0_io_base){
		blockptr=(void*)&bus0done;
	}else if(bus == bus1_io_base){
		blockptr=(void*)&bus1done;
	}else{
		panic("ATA: Unknown device!");
	}
	API->CurrentThread().SetBlock([&]{
		return dma_blockcheck(blockptr);
	});
}

/*
void set_bus0_prdt(uint32_t bmr, prd *prd){
	uint32_t phys=physaddr((void*)prd);
	dbgpf("ATA: Setting bus 0 PRDT pointer to %x.\n", phys);
	out32(bmr+0x04, phys);
	bus0prd=*prd;
}

void set_bus1_prdt(uint32_t bmr, prd *prd){
	uint32_t phys=physaddr((void*)prd);
	dbgpf("ATA: Setting bus 1 PRDT pointer to %x.\n", phys);
	out32(bmr+0x0C, phys);
	bus1prd=*prd;
}

bool init_dma(){
	return false;
	hold_lock hl(&dma_init_lock);
	if(dma_init) return true;
	if(init_pci()){
		pci_device *dev=pci_findbyclass(0x01, 0x01);
		if(!dev) return false;
		uint16_t bar4low=pci_readword(*dev, 0x20);
		uint16_t bar4high=pci_readword(*dev, 0x22);
		bmr=(bar4high << 16) | bar4low;
		bmr&=~1;
		uint16_t cmd=pci_readword(*dev, 0x08);
		uint16_t status=pci_readword(*dev, 0x0A);
		uint16_t newcmd = cmd | 0x07;
		newcmd &= ~(1 << 10);
		pci_write(*dev, 0x08, (status << 16) | newcmd);
		cmd=pci_readword(*dev, 0x08);
		dbgpf("ATA: STATUS: %x CMD: %x NEWCMD:%x\n", status, cmd, newcmd);
		init_lock(&dma_lock);
		set_bus0_prdt(bmr, new prd());
		set_bus1_prdt(bmr, new prd());
		dma_init=true;
		return true;
	}
	return false;
}

char dma_buffer[ATA_SECTOR_SIZE] __attribute__((aligned(0x1000)));

void dma_read_sector(ata_device *dev, uint32_t lba, uint8_t *buf){
	dbgpf("ATA: DMA read: dev: %p, lba: %x, buf: %x\n", dev, lba, physaddr((void*)buf));
	memset(buf, 0, ATA_SECTOR_SIZE);
	if(!dma_init) return;
	int bus=dev->io_base;
	int slave=dev->slave;

	void *blockptr=NULL;
	uint16_t base;

	hold_lock hl(&dma_lock);
	if(dev->io_base==bus0_io_base){
		bus0prd.data=physaddr((void*)dma_buffer);
		bus0prd.bytes=ATA_SECTOR_SIZE;
		base=0;
		bus0done=false;
		blockptr=(void*)&bus0done;
		set_bus0_prdt(bmr, &bus0prd);
		dbgout("ATA: Primary.\n");
	}else if(dev->io_base==bus1_io_base){
		bus1prd.data=physaddr((void*)dma_buffer);
		bus1prd.bytes=ATA_SECTOR_SIZE;
		base=0x08;
		bus1done=false;
		blockptr=(void*)&bus1done;
		set_bus1_prdt(bmr, &bus1prd);
		dbgout("ATA: Secondary.\n");
	}else{
		panic("(ATA) Unrecognised device!");
	}
	outb(dev->control, 2);
	outb(bmr + base, DMA_READ);

	uint8_t status=inb(bmr + base + 2);
	outb(bmr + base + 2, status | 2 | 4);

	ata_wait(dev, 0);
	outb(dev->control, 0);

	outb(bus + ATA_REG_HDDEVSEL, 0xe0 | slave << 4 | (lba & 0x0f000000) >> 24);
	outb(bus + 1, 0x03);
	outb(bus + 2, 0x21);
	outb(bus + ATA_REG_COMMAND, 0xEF);
	uint8_t q=inb(ATA_REG_STATUS);
	dbgpf("ATA: q=%x\n", q);
	*(bool*)blockptr=false;
	//outb(bus + ATA_REG_FEATURES, 0x01);
	outb(bus + ATA_REG_SECCOUNT0, 1);
	outb(bus + ATA_REG_LBA0, (lba & 0x000000ff) >>  0);
	outb(bus + ATA_REG_LBA1, (lba & 0x0000ff00) >>  8);
	outb(bus + ATA_REG_LBA2, (lba & 0x00ff0000) >> 16);
	outb(bus + ATA_REG_COMMAND, ATA_CMD_READ_DMA);

	uint8_t cmd=inb(bmr + base);
	outb(bmr + base, cmd | DMA_ON);

	dbgpf("ATA: Waiting for DMA to complete...\n");
	thread_setblock(&dma_blockcheck, blockptr);
	outb(bmr + base, 0);
	uint8_t atastatus=ata_wait(dev, 1);
	if(inb(bmr + base+2) & 0x02) atastatus=1;
	if(atastatus){
		panic("(ATA) DMA FAILED");
		dbgpf("ATA: DMA error! Falling back to PIO.\n");
		ata_device_read_sector_pio(dev, lba, buf);
	}else{
		memcpy(buf, dma_buffer, ATA_SECTOR_SIZE);
	}
	dbgpf("ATA: DMA complete.\n");
}
*/

void preinit_dma(){
	dbgout("ATA: DMA/IRQ Pre-Init.\n");
	auto &hal = API->GetHAL();
	hal.HandleIRQ(14, &dma_int_handler);
	hal.HandleIRQ(15, &dma_int_handler);
	hal.EnableIRQ(14);
	hal.EnableIRQ(15);
	//init_lock(&dma_init_lock);
}
