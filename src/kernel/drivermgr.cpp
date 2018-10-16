#include "kernel.hpp"
#include "ministl.hpp"
#include "string.hpp"
#include "locks.hpp"

lock drv_lock;
map<string, drv_device>* devices;

struct drv_instance{
	drv_driver driver;
	void *id;
	void *instance;
};

char *drv_devices_infofs(){
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# name, type, description\n");
	hold_lock hl(drv_lock);
	for(map<string, drv_device>::iterator i=devices->begin(); i!=devices->end(); ++i){
		sprintf(&buffer[strlen(buffer)], "%s, %x, \"%s\"\n", i->first.c_str(), i->second.driver.type(i->second.id), i->second.driver.desc(i->second.id));
	}
	return buffer;
}

void drv_init(){
	dbgout("DRV: Init\n");
	devices=new map<string, drv_device>();
	init_lock(drv_lock);
	infofs_register("DEVICES", &drv_devices_infofs);
}

string get_unique_name(string name){
	char buf[12];
	for(int i=0; i < 1000; ++i){
		sprintf(buf, "%s%i", name.c_str(), i);
		if(!devices->has_key(buf)) return buf;
	}
	return "";
}

void drv_add_device(char *name, drv_driver *driver, void *id){
	string sname;
	{ hold_lock hl(drv_lock);
		sname=get_unique_name(name);
		(*devices)[sname].driver=*driver;
		(*devices)[sname].id=id;
	}
	strncpy(name, sname.c_str(), 12);
	dbgpf("DRV: Device %s registered.\n", sname.c_str());
}

drv_device *drv_get(const char *name){
	drv_device *ret;
	{ hold_lock hl(drv_lock);
		if(!devices->has_key(name)) return NULL;
		ret=&(*devices)[name];
	}
	return ret;
}

void *drv_open(const char *driver){
	//hold_lock hl(drv_lock);
	drv_device *drv=drv_get(driver);
	if(!drv) return NULL;
	drv_instance *inst=new drv_instance();
	//TODO: Attach to process somehow...
	inst->driver=drv->driver;
	inst->instance=inst->driver.open(drv->id);
	inst->id = drv->id;
	return (void*)inst;
}

bool drv_close(void *instance){
	drv_instance *inst=(drv_instance*)instance;
	bool ret=inst->driver.close(inst->instance);
	if(ret) free(inst);
	return ret;
}

size_t drv_read(void *instance, size_t bytes, char *buf){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.read(inst->instance, bytes, buf);
}

size_t drv_write(void *instance, size_t bytes, char *buf){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.write(inst->instance, bytes, buf);
}

bt_filesize_t drv_seek(void *instance, bt_filesize_t pos, uint32_t flags){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.seek(inst->instance, pos, flags);
}
	
int drv_ioctl(void *instance, int fn, size_t bytes, char *buf){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.ioctl(inst->instance, fn, bytes, buf);
}
	
int drv_get_type(const char *driver){
	auto dev = drv_get(driver);
	return dev->driver.type(dev->id);
}

int drv_get_type(void *instance){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.type(inst->id);
}

char *drv_get_desc(const char *driver){
	auto dev = drv_get(driver);
	return dev->driver.desc(dev->id);
}

char *drv_get_desc(void *instance){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.desc(inst->id);
}

void *drv_firstdevice(char **p){
	map<string, drv_device>::iterator ret=devices->begin();
	*p=(char*)ret->first.c_str();
	return (void*)ret;
}

void *drv_nextdevice(void *i, char **p){
	map<string, drv_device>::iterator ret=(map<string, drv_device>::iterator)i;
	++ret;
	*p=(char*)ret->first.c_str();
	if(ret>=devices->end()) return NULL;
	else return (void*)ret;
}
