#include "module_stubs.h"
#include "module_cpp.hpp"
#include "io.h"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

static const uint32_t CONFIG_ADDRESS=0xCF8;
static const uint32_t CONFIG_DATA=0xCFC;

struct pci_device{
    bool present;
    uint8_t bus;
    uint8_t slot;
    uint8_t func;
    uint16_t vendor;
    uint16_t devid;
    uint8_t classcode;
    uint8_t subclass;
};

uint32_t mk_pci_address(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset){
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    return (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
}

uint16_t read_configword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset){
    uint32_t pciaddr= mk_pci_address(bus, slot, func, offset);
    out32(CONFIG_ADDRESS, pciaddr);
    return (uint16_t)((in32(CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff);
}

uint16_t get_vendor(uint8_t bus, uint8_t slot){
    return read_configword(bus, slot, 0, 0);
}

uint16_t get_devid(uint8_t bus, uint8_t slot){
    return read_configword(bus, slot, 0, 2);
}

pci_device scan_device(uint8_t bus, uint8_t slot, uint8_t func){
    pci_device ret;
    ret.present=false;
    uint16_t vendor= read_configword(bus, slot, func, 0);
    if(vendor!=0xFFFF){
        ret.present=true;
        ret.bus=bus;
        ret.slot=slot;
        ret.func=func;
        ret.vendor=vendor;
        ret.devid= read_configword(bus, slot, func, 2);
        uint16_t classinfo=read_configword(bus, slot, func, 0x0A);
        ret.classcode=(0xFF00 & classinfo) >> 8;
        ret.subclass=0xFF & classinfo;
    }
    return ret;
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
    for(uint8_t i=0; i<255; ++i){
        pci_device dev= scan_device(0, i, 0);
        if(dev.present){
            dbgpf("PCI: Found device bus: 0, slot: %i, func:0, vendor: %x, devid: %x, class: %x, subclass:%x\n",
                    i, dev.vendor, dev.devid, dev.classcode, dev.subclass);
        }
    }

    return 0;
}