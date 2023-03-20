#include "pci.hpp"

#include <module/module.inc>

static const uint32_t CONFIG_ADDRESS=0xCF8;
static const uint32_t CONFIG_DATA=0xCFC;

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

void write_config32(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value){
    uint32_t pciaddr=mk_pci_address(bus, slot, func, offset);
    out32(CONFIG_ADDRESS, pciaddr);
    out32(CONFIG_DATA, value);
}

int module_main(char *){
	API->GetHwPnPManager().RegisterDriver(GetPCIBusDriver());
    return 0;
}

void PCIBusDevice::ScanBus(uint8_t bus){
	for(uint8_t slot=0; slot<255; ++slot){
        for(uint8_t func=0; func<8; ++func) {
            auto dev = ScanDevice(bus, slot, func);
            if (dev.present) {
                uint8_t header_format=read_configword(bus, slot, func, 0x0E);
                if((header_format & 0x7F)==0) AddDevice(dev);
                else if(header_format==1 && dev.id.Class==0x0604){
                    uint16_t busnumbers= read_configword(bus, slot, func, 0x18);
                    uint8_t secondary=(busnumbers & 0xFF00) >> 8;
                    ScanBus(secondary);
                }
                if(func==0 && !(header_format & 0x80)) break;
            }
        }
    }
}

void PCIBusDevice::AddDevice(const PCIDevice &dev){
	devices.push_back(dev);
}

PCIBusDevice::PCIDevice PCIBusDevice::ScanDevice(uint8_t bus, uint8_t slot, uint8_t func){
	PCIDevice ret;
    ret.present=false;
    uint16_t vendor= read_configword(bus, slot, func, 0);
    if(vendor!=0xFFFF){
        ret.present=true;
        ret.bus=bus;
        ret.slot=slot;
        ret.func=func;
        ret.id.Bus=btos_api::hwpnp::PNPBUS::PCI;
        ret.id.VendorID=vendor;
        ret.id.DeviceID=read_configword(bus, slot, func, 2);
        ret.id.ExtraID=0;
        ret.id.Revision=0;
        ret.id.Class=read_configword(bus, slot, func, 0x0A);
    }
    return ret;
}

void PCIBusDevice::Lock(){
	bus_lock->TakeExclusive();
}

void PCIBusDevice::Unlock(){
	bus_lock->Release();
}

PCIBusDevice::PCIBusDevice(){
	bus_lock = API->NewLock();
	ScanBus(0);
}

btos_api::hwpnp::DeviceID PCIBusDevice::GetID(){
	return PCPCIDeviceID;
}

const char *PCIBusDevice::GetDescription(){
	return "PCI system bus";
}

size_t PCIBusDevice::GetSubDeviceCount(){
	return devices.size();
}

btos_api::hwpnp::DeviceID PCIBusDevice::GetSubDevice(size_t i){
	if(i < devices.size()) return devices[i].id;
	else return btos_api::hwpnp::NullDeviceID;
}

btos_api::hwpnp::IDriver *PCIBusDevice::GetDriver(){
	return GetPCIBusDriver();
}
	
uint8_t PCIBusDevice::ReadConfigByte(size_t index, uint8_t offset){
	if(index < devices.size()){
		auto &dev = devices[index];
		uint32_t pciaddr = mk_pci_address(dev.bus, dev.slot, dev.func, offset);
		out32(CONFIG_ADDRESS, pciaddr);
    	return (uint8_t)((in32(CONFIG_DATA) >> ((offset & 2) * 8)) & 0xff);
	}else return 0;
}

uint16_t PCIBusDevice::ReadConfigWord(size_t index, uint8_t offset){
	if(index < devices.size()){
		auto &dev = devices[index];
		uint32_t pciaddr = mk_pci_address(dev.bus, dev.slot, dev.func, offset);
		out32(CONFIG_ADDRESS, pciaddr);
    	return (uint16_t)((in32(CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff);
	}else return 0;
}

uint32_t PCIBusDevice::ReadConfig32(size_t index, uint8_t offset){
	if(index < devices.size()){
		auto &dev = devices[index];
		uint32_t pciaddr = mk_pci_address(dev.bus, dev.slot, dev.func, offset);
		out32(CONFIG_ADDRESS, pciaddr);
    	return in32(CONFIG_DATA);
	}else return 0;
}
	
void PCIBusDevice::WriteConfigByte(size_t index, uint8_t offset, uint8_t value){
	if(index < devices.size()){
		auto &dev = devices[index];
		uint32_t pciaddr = mk_pci_address(dev.bus, dev.slot, dev.func, offset);
	    out32(CONFIG_ADDRESS, pciaddr);
	    outb(CONFIG_DATA, value);
	}
}

void PCIBusDevice::WriteConfigWord(size_t index, uint8_t offset, uint16_t value){
	if(index < devices.size()){
		auto &dev = devices[index];
		uint32_t pciaddr = mk_pci_address(dev.bus, dev.slot, dev.func, offset);
	    out32(CONFIG_ADDRESS, pciaddr);
	    out16(CONFIG_DATA, value);
	}
}

void PCIBusDevice::WriteConfig32(size_t index, uint8_t offset, uint32_t value){
	if(index < devices.size()){
		auto &dev = devices[index];
		uint32_t pciaddr = mk_pci_address(dev.bus, dev.slot, dev.func, offset);
	    out32(CONFIG_ADDRESS, pciaddr);
	    out32(CONFIG_DATA, value);
	}
}

class PCIBusDriver : public btos_api::hwpnp::IDriver{
public:
	btos_api::hwpnp::DeviceID GetDeviceID();
	bool IsCompatible(const btos_api::hwpnp::DeviceID &dev);
	const char *GetDescription();
	btos_api::hwpnp::IDevice *CreateDevice(const btos_api::hwpnp::DeviceID &dev, btos_api::hwpnp::IDevice *parent, size_t index);
	void DestroyDevice(btos_api::hwpnp::IDevice *dev);
	uint32_t GetPriority();
};

btos_api::hwpnp::DeviceID PCIBusDriver::GetDeviceID(){
	return PCPCIDeviceID;
}

bool PCIBusDriver::IsCompatible(const btos_api::hwpnp::DeviceID &dev){
	return
    dev.Bus == PCPCIDeviceID.Bus &&
	dev.VendorID == PCPCIDeviceID.VendorID &&
	dev.DeviceID == PCPCIDeviceID.DeviceID &&
	dev.Revision == PCPCIDeviceID.Revision &&
	dev.ExtraID == PCPCIDeviceID.ExtraID &&
	dev.Class == PCPCIDeviceID.Class;
}

const char *PCIBusDriver::GetDescription(){
	return "PCI system bus driver";
}

btos_api::hwpnp::IDevice *PCIBusDriver::CreateDevice(const btos_api::hwpnp::DeviceID&, btos_api::hwpnp::IDevice*, size_t){
	return new PCIBusDevice();
}

void PCIBusDriver::DestroyDevice(btos_api::hwpnp::IDevice *dev){
	delete (PCIBusDevice*)dev;
}

uint32_t PCIBusDriver::GetPriority(){
	return btos_api::hwpnp::DriverPriority::Generic;
}

static PCIBusDriver theDriver;

btos_api::hwpnp::IDriver *GetPCIBusDriver(){
	return &theDriver;
}
