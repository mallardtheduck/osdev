#include "module_stubs.h"
#include "module_cpp.hpp"
#include "io.h"
#include "../../include/module_stubs.h"

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

const size_t MAX_PCI_DEVICES=256;
pci_device *pci_devices[MAX_PCI_DEVICES];

size_t strlen(const char* str)
{
    size_t ret = 0;
    while ( str[ret] != 0 )
        ret++;
    return ret;
}

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

void add_pci_device(const pci_device &dev){
    pci_device *ptr=new pci_device();
    *ptr=dev;
    for(size_t i=0; i<MAX_PCI_DEVICES; ++i){
        if(!pci_devices[i]) {
            pci_devices[i] = ptr;
            return;
        }
    }
}

void pci_scan(uint8_t bus){
    for(uint8_t slot=0; slot<255; ++slot){
        for(uint8_t func=0; func<8; ++func) {
            pci_device dev = scan_device(bus, slot, func);
            if (dev.present) {
                dbgpf("PCI: Found device bus: %i, slot: %i, func:%i, vendor: %x, devid: %x, class: %x, subclass:%x\n",
                        bus, slot, func, dev.vendor, dev.devid, dev.classcode, dev.subclass);
                uint8_t header_format=read_configword(bus, slot, func, 0x0E);
                dbgpf("PCI: header format %x\n", header_format);
                if((header_format & 0x7F)==0) add_pci_device(dev);
                else if(header_format==1 && dev.classcode==0x06 && dev.subclass==0x04){
                    uint16_t busnumbers= read_configword(bus, slot, func, 0x18);
                    uint8_t secondary=(busnumbers & 0xFF00) >> 8;
                    pci_scan(secondary);
                }
                if(func==0 && !(header_format & 0x80)) break;
            }
        }
    }
}

char *pci_infofs(){
    char *buffer=(char*)malloc(4096);
    memset(buffer, 0, 4096);
    sprintf(buffer, "# bus, slot, func, vendor, id, class, subclass\n");
    for(size_t i=0; i<MAX_PCI_DEVICES; ++i){
        if(pci_devices[i]) {
            sprintf(&buffer[strlen(buffer)], "%i, %i, %i, %x, %x, %x, %x\n",
                pci_devices[i]->bus, pci_devices[i]->slot, pci_devices[i]->func, pci_devices[i]->vendor,
                pci_devices[i]->devid,  pci_devices[i]->classcode, pci_devices[i]->subclass);
        }
    }
    return buffer;
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
    pci_scan(0);
    infofs_register("PCI", &pci_infofs);
    return 0;
}
