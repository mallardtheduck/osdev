#include "pci.hpp"

static pci_device *pci_findbyclass(uint8_t classcode, uint8_t subclass){
    for(size_t i=0; i<MAX_PCI_DEVICES; ++i){
        if(pci_devices[i]->present && pci_devices[i]->classcode==classcode && pci_devices[i]->subclass==subclass){
            return pci_devices[i];
        }
    }
    return NULL;
}

static pci_device *pci_findbyvendor(uint16_t vendor, uint16_t devid){
    for(size_t i=0; i<MAX_PCI_DEVICES; ++i){
        if(pci_devices[i]->present && pci_devices[i]->vendor==vendor && pci_devices[i]->devid==devid){
            return pci_devices[i];
        }
    }
    return NULL;
}

static uint16_t pci_readword(pci_device dev, uint8_t offset){
    return read_configword(dev.bus, dev.slot, dev.func, offset);
}

static void pci_write(pci_device dev, uint8_t offset, uint32_t value){
    write_config32(dev.bus, dev.slot, dev.func, offset, value);
}

pci_call_table pci_table={
    &pci_findbyclass,
    &pci_findbyvendor,
    &pci_readword,
    &pci_write,
};

kernel_extension pci_extension={
    "PCI",
    &pci_table,
    NULL,
};

void pci_init_extension(){
    add_extension(&pci_extension);
}
