#ifndef _PCI_HPP
#define _PCI_HPP

#include "module_stubs.h"

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
extern pci_device *pci_devices[MAX_PCI_DEVICES];

uint16_t read_configword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

#endif