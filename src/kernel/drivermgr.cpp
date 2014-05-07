#include "kernel.hpp"
#include "ministl.hpp"
#include "string.hpp"
#include "locks.hpp"

lock drv_lock;

map<string, drv_driver>* drivers;

struct drv_instance{
	drv_driver driver;
	void *instance;
};

void drv_init(){
	dbgout("DRV: Init\n");
	drivers=new map<string, drv_driver>();
	init_lock(drv_lock);
}

string get_unique_name(string name){
	char buf[12];
	int i=0;
	while(i<999){
		sprintf(buf, "%s%i", name.c_str(), i);
		if(!drivers->has_key(buf)) return buf;
	}
	return "";
}

void drv_add_device(char *name, drv_driver *driver){
	string sname;
	{ hold_lock hl(drv_lock);
		sname=get_unique_name(name);
		(*drivers)[sname]=*driver;
	}
	strncpy(name, sname.c_str(), 12);
	dbgpf("DRV: Device %s registered.\n", sname.c_str());
}

drv_driver drv_get(char *name){
	drv_driver ret;
	{ hold_lock hl(drv_lock);
		ret=(*drivers)[name];
	}
	return ret;
}

void *drv_open(char *driver){
	hold_lock hl(drv_lock);
	drv_instance *inst=new drv_instance();
	//TODO: Attach to process somehow...
	inst->driver=drv_get(driver);
	inst->instance=inst->driver.open();
	return (void*)inst;
}

bool drv_close(void *instance){
	drv_instance *inst=(drv_instance*)instance;
	bool ret=inst->driver.close(inst->instance);
	if(ret) free(inst);
	return ret;
}

int drv_read(void *instance, size_t bytes, char *buf){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.read(inst->instance, bytes, buf);
}

bool drv_write(void *instance, size_t bytes, char *buf){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.write(inst->instance, bytes, buf);
}

void drv_seek(void *instance, size_t pos, bool relative){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.seek(inst->instance, pos, relative);
}
	
int drv_ioctl(void *instance, int fn, size_t bytes, char *buf){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.ioctl(inst->instance, fn, bytes, buf);
}
	
int drv_get_type(char *driver){
	hold_lock hl(drv_lock);
	return drv_get(driver).type();
}

int drv_get_type(void *instance){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.type();
}

char *drv_get_desc(char *driver){
	hold_lock hl(drv_lock);
	return drv_get(driver).desc();
}

char *drv_get_desc(void *instance){
	drv_instance *inst=(drv_instance*)instance;
	return inst->driver.desc();
}
