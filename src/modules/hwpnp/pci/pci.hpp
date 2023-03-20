#ifndef _PCI_HPP
#define _PCI_HPP

#include <btos_module.h>
#include <dev/hwpnp/pcibus.hpp>

#define PCI_NO_STUBS
#include <util/ministl.hpp>

static const btos_api::hwpnp::DeviceID PCPCIDeviceID = {
		btos_api::hwpnp::PNPBUS::PCBUS,
		0, 0, 0, 0, 4
};

uint16_t read_configword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void write_config32(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value);
void pci_init_extension();

class PCIBusDevice : public btos_api::hwpnp::IPCIBus{
private:
	struct PCIDevice{
		bool present;
		uint8_t bus;
    	uint8_t slot;
    	uint8_t func;
    	btos_api::hwpnp::DeviceID id;
	};
	vector<PCIDevice> devices;
	
	void ScanBus(uint8_t bus);
	void AddDevice(const PCIDevice &dev);
	PCIDevice ScanDevice(uint8_t bus, uint8_t slot, uint8_t func);
	
	ILock *bus_lock;
protected:
	void Lock();
	void Unlock();
public:
	PCIBusDevice();

	btos_api::hwpnp::DeviceID GetID();
	const char *GetDescription();
	size_t GetSubDeviceCount();
	btos_api::hwpnp::DeviceID GetSubDevice(size_t);
	btos_api::hwpnp::IDriver *GetDriver();
	
	uint8_t ReadConfigByte(size_t index, uint8_t offset);
	uint16_t ReadConfigWord(size_t index, uint8_t offset);
	uint32_t ReadConfig32(size_t index, uint8_t offset);
	
	void WriteConfigByte(size_t index, uint8_t offset, uint8_t value);
	void WriteConfigWord(size_t index, uint8_t offset, uint16_t value);
	void WriteConfig32(size_t index, uint8_t offset, uint32_t value);
};

btos_api::hwpnp::IDriver *GetPCIBusDriver();

#endif