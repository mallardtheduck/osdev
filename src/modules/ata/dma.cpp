#include "ata.hpp"
#include "pci.h"
#include "io.h"
#include "holdlock.hpp"

static bool dma_init=false;
pci_call_table *PCI_CALL_TABLE;

const int bus0_io_base=0x1F0;
const int bus1_io_base=0x170;

struct prd{
    uint32_t data;
    uint16_t bytes;
    uint16_t reserved;

    prd() : reserved((1 << 15)) {}
} __attribute__((packed));

prd *bus0prd, *bus1prd;
lock dma_lock, dma_init_lock;
uint32_t bmr;

volatile bool bus0done, bus1done;

void dma_int_handler(int irq, isr_regs*){
    panic("ATA Interrupt!\n");
    if(inb(bmr+0x02) & 0x04){
        bus0done=true;
        outb(bmr+0x02, 0x04);
    }
    if(inb(bmr+0x0A) & 0x04){
        bus1done=true;
        outb(bmr+0x0A, 0x04);
    }
    irq_ack(irq);
}

bool dma_blockcheck(void *q){
    return *(bool*)q;
}

void set_bus0_prdt(uint32_t bmr, prd *prd){
    out32(bmr+0x04, physaddr((void*)prd));
    bus0prd=prd;
}

void set_bus1_prdt(uint32_t bmr, prd *prd){
    out32(bmr+0x0C, physaddr((void*)prd));
    bus1prd=prd;
}

bool init_dma(){
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
        dbgpf("ATA: STATUS: %x CMD: %x NEWCMD:%x\n", status, cmd, newcmd);
        pci_write(*dev, 0x08, (status << 16) | newcmd);
        init_lock(&dma_lock);
        set_bus0_prdt(bmr, new prd());
        set_bus1_prdt(bmr, new prd());
        handle_irq(14, &dma_int_handler);
        handle_irq(15, &dma_int_handler);
        /*uint16_t intnos=pci_readword(*dev, 0x3C);
        uint16_t latgran=pci_readword(*dev, 0x3E);
        intnos &= 0xFF00;
        intnos |= 15;
        pci_write(*dev, 0x3C, (latgran << 16) | intnos);*/
        irq_ack(14);
        unmask_irq(14);
        irq_ack(15);
        unmask_irq(15);
        dma_init=true;
        return true;
    }
    return false;
}

void dma_read_sector(ata_device *dev, uint32_t lba, uint8_t *buf){
    dbgpf("ATA: DMA read: dev: %x, lba: %x, buf: %x\n", dev, lba, physaddr((void*)buf));
    if(!dma_init) return;
    int bus=dev->io_base;
    int slave=dev->slave;

    void *blockptr=NULL;
    uint16_t base;

    hold_lock hl(&dma_lock);
    if(dev->io_base==bus0_io_base){
        bus0prd->data=physaddr((void*)buf);
        bus0prd->bytes=ATA_SECTOR_SIZE;
        base=0;
        bus0done=false;
        blockptr=(void*)&bus0done;
        dbgout("ATA: Primary.\n");
    }else if(dev->io_base==bus1_io_base){
        bus1prd->data=physaddr((void*)buf);
        bus1prd->bytes=ATA_SECTOR_SIZE;
        base=0x08;
        bus1done=false;
        blockptr=(void*)&bus1done;
        dbgout("ATA: Secondary.\n");
    }else{
        panic("(ATA) Unrecognised device!");
    }
    outb(bus + ATA_REG_CONTROL, 2);

    ata_wait(dev, 0);
    outb(bus + ATA_REG_CONTROL, 0);

    uint8_t cmd=inb(bmr + base);
    outb(bmr + base, cmd | 8 | 1);

    outb(bus + ATA_REG_HDDEVSEL, 0xe0 | slave << 4 | (lba & 0x0f000000) >> 24);
    //outb(bus + ATA_REG_FEATURES, 0x00);
    outb(bus + ATA_REG_SECCOUNT0, 1);
    outb(bus + ATA_REG_LBA0, (lba & 0x000000ff) >>  0);
    outb(bus + ATA_REG_LBA1, (lba & 0x0000ff00) >>  8);
    outb(bus + ATA_REG_LBA2, (lba & 0x00ff0000) >> 16);
    outb(bus + ATA_REG_COMMAND, ATA_CMD_READ_DMA);

    inb(bus + ATA_REG_ALTSTATUS);
    inb(bus + ATA_REG_ALTSTATUS);
    inb(bus + ATA_REG_ALTSTATUS);
    inb(bus + ATA_REG_ALTSTATUS);
    inb(bus + ATA_REG_ALTSTATUS);

    uint8_t status=inb(bmr + base + 2);
    outb(bmr + base + 2, status | 2 | 4);

    dbgpf("ATA: Waiting for DMA to complete...\n");
    thread_setblock(&dma_blockcheck, blockptr);
    /*while(inb(bmr+base+2) & 0x01) {
        yield();
        dbgpf("ATA: cmd: %x status %x\n", inb(bmr+base), inb(bmr+base+2));
        dbgpf("ATA: Status: %x\n", inb(bus + ATA_REG_STATUS));
        if(!(inb(bus + ATA_REG_STATUS) & 0x80)) break;
    }*/
    dbgpf("ATA: Status: %x\n", inb(bus + ATA_REG_STATUS));
    //ata_wait(dev, 0);
    //(void)blockptr;
    if(inb(bmr + base+2) & 0x02) panic("ATA DMA ERROR!");
    dbgpf("ATA: DMA complete.\n");
}

void preinit_dma(){
    init_lock(&dma_init_lock);
}