#ifndef _PCI_H
#define _PCI_H

#include <btos_module.h>

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

#ifndef __cplusplus
typedef struct pci_device pci_device;
#endif

struct pci_call_table{
    pci_device *(*pci_findbyclass)(uint8_t, uint8_t);
    pci_device *(*pci_findbyvendor)(uint16_t, uint16_t);
    uint16_t (*pci_readword)(pci_device, uint8_t);
    void (*pci_write)(pci_device, uint8_t, uint32_t);
};

#ifndef __cplusplus
typedef struct pci_call_table pci_call_table;
#endif

#ifndef PCI_NO_STUBS

extern pci_call_table *PCI_CALL_TABLE;

inline static bool init_pci(){
    uint16_t extid=get_extension_id("PCI");
    if(!extid) return false;
    PCI_CALL_TABLE = (pci_call_table*) get_extension(extid)->calltable;
    return true;
}

inline static pci_device *pci_findbyclass(uint8_t classcode, uint8_t subclass){
    return PCI_CALL_TABLE->pci_findbyclass(classcode, subclass);
}

inline static pci_device *pci_findbyvendor(uint16_t vendor, uint16_t devid){
    return PCI_CALL_TABLE->pci_findbyvendor(vendor, devid);
}

inline static uint16_t pci_readword(pci_device dev, uint8_t offset){
    return PCI_CALL_TABLE->pci_readword(dev, offset);
}

inline static void pci_write(pci_device dev, uint8_t offset, uint32_t value){
    return PCI_CALL_TABLE->pci_write(dev, offset, value);
}

#endif

#endif