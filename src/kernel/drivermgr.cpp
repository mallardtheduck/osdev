#include "kernel.hpp"
#include "ministl.hpp"
#include "string.hpp"
#include "locks.hpp"

lock drv_lock;

map<string, drv_driver>* drivers;

void drv_init(){
	dbgout("DRV: Init\n");
	drivers=new map<string, drv_driver>();
	init_lock(drv_lock);
}

string get_unique_name(string name){
	char buf[12];
	int i=0;
	while(i<999 && (sprintf(buf, "%s%i", name.c_str(), i),drivers->has_key(name+buf)));
	if(i<999) return name+buf;
	else return "";
}

void drv_add_device(char *name, drv_driver *driver){
	string sname(name);
	sname=get_unique_name(name);
	{ hold_lock hl(drv_lock);
		(*drivers)[sname]=*driver;
	}
	strncpy((char*)sname.c_str(), name, 9);
	dbgpf("DRV: Device %s registered.\n", sname.c_str());
}

drv_driver drv_get(char *name){
	drv_driver ret;
	{ hold_lock hl(drv_lock);
		ret=(*drivers)[name];
	}
	return ret;
}
