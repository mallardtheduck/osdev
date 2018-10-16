#include "hwpnp_internal.hpp"
#include "../ministl.hpp"

using namespace btos_api::hwpnp;

IRootDevice *rootDev = nullptr;

struct KnownDevice{
	IDevice *parent = nullptr;
	size_t index = 0;
	DeviceID id;
	IDevice *device = nullptr;
	
	KnownDevice() {}
	KnownDevice(IDevice *p, size_t idx, DeviceID i, IDevice *d) : 
		parent(p), index(idx), id(i), device(d) {}
};

vector<KnownDevice> *known_devices;

static char *pnp_devices_infofs(){
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# id, parent, index, devid, type, description, driver\n");
	sprintf(&buffer[strlen(buffer)], "%p, %p, %i, %x%x:%x%x:%x%x:%x%x:%x%x:%x%x, %i, \"%s\", %p\n",
			rootDev, nullptr, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			rootDev->GetType(),
			rootDev->GetDescription(),
			rootDev->GetDriver()
		);
	for(auto d : *known_devices){
		auto devid = d.id;
		sprintf(&buffer[strlen(buffer)], "%p, %p, %i, %x%x:%x%x:%x%x:%x%x:%x%x:%x%x, %i, \"%s\", %p\n",
			d.device, d.parent, (int)d.index,
			Upper(devid.Bus), Lower(devid.Bus), 
			Upper(devid.VendorID), Lower(devid.VendorID), 
			Upper(devid.DeviceID), Lower(devid.DeviceID), 
			Upper(devid.Revision), Lower(devid.Revision), 
			Upper(devid.ExtraID), Lower(devid.ExtraID), 
			Upper(devid.Class), Lower(devid.Class),
			(d.device ? d.device->GetType() : -1),
			(d.device ? d.device->GetDescription() : "Unknown device"),
			(d.device ? d.device->GetDriver() : nullptr)
		);
	}
	return buffer;
}

void pnp_init_devices(){
	known_devices = new vector<KnownDevice>();
	infofs_register("PNPDEVICES", &pnp_devices_infofs);
}

void pnp_add_device(IDevice *parent, const DeviceID &id, size_t idx){
	for(auto d : *known_devices){
		if(d.parent == parent && d.index == idx) return;
	}
	auto dev = pnp_create_device(parent, idx, id);
	known_devices->push_back(KnownDevice(parent, idx, id, dev));
}

IDevice *pnp_resolve_device(IDevice *parent, const DeviceID &id, size_t idx){
	pnp_add_device(parent, id, idx);
	for(auto d : *known_devices){
		if(d.parent == parent && d.index == idx) return d.device;
	}
	return nullptr;
}

void pnp_rescan_devices(){
	for(auto d : *known_devices){
		if(!d.device) d.device = pnp_create_device(d.parent, d.index, d.id);
	}
}

void pnp_set_root_device(IRootDevice *dev){
	if(!rootDev) rootDev = dev;
}

struct node_instance{
	IDeviceNode *node;
	void *h;
};

static void *pnp_node_open(void *id){
	IDeviceNode *node = (IDeviceNode*)id;
	void *h = node->Open();
	if(h){
		node_instance *inst = new node_instance();
		inst->node = node;
		inst->h = h;
		return inst;
	}else{
		return nullptr;
	}
}

static bool pnp_node_close(void *instance){
	node_instance *inst = (node_instance*)instance;
	if(inst->node->Close(inst->h)){
		delete inst;
		return true;
	}else return false;
}

static size_t pnp_node_read(void *instance, size_t bytes, char *buf){
	node_instance *inst = (node_instance*)instance;
	return inst->node->Read(inst->h, bytes, buf);
}

static size_t pnp_node_write(void *instance, size_t bytes, char *buf){
	node_instance *inst = (node_instance*)instance;
	return inst->node->Write(inst->h, bytes, buf);
}

static bt_filesize_t pnp_node_seek(void *instance, bt_filesize_t pos, uint32_t flags){
	node_instance *inst = (node_instance*)instance;
	return inst->node->Seek(inst->h, pos, flags);
}

static int pnp_node_ioctl(void *instance, int fn, size_t bytes, char *buf){
	node_instance *inst = (node_instance*)instance;
	return inst->node->IOCtl(inst->h, fn, bytes, buf);
}

static int pnp_node_type(void *id){
	IDeviceNode *node = (IDeviceNode*)id;
	return node->GetType();
}

static char *pnp_node_desc(void *id){
	IDeviceNode *node = (IDeviceNode*)id;
	return (char*)node->GetDescription();
}

drv_driver nodeAdaptor = {pnp_node_open, pnp_node_close, pnp_node_read, pnp_node_write, pnp_node_seek, pnp_node_ioctl, pnp_node_type, pnp_node_desc};

void pnp_node_add(IDeviceNode *node){
	char name[8] = {0};
	strncpy(name, node->GetBaseName(), 7);
	drv_add_device(name, &nodeAdaptor, node);
}
