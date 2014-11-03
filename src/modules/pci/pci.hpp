#ifndef _PCI_HPP
#define _PCI_HPP

#include "module_stubs.h"
#include "module_cpp.hpp"
#include "io.h"

#define PCI_NO_STUBS
#include "pci.h"

const size_t MAX_PCI_DEVICES=256;
extern pci_device *pci_devices[MAX_PCI_DEVICES];

uint16_t read_configword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void write_config32(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value);
void pci_init_extension();

#endif