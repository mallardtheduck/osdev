#include "btos.h"

char* getenv (const char* name){
	static char buffer[BT_MAX_PATH];
	if(bt_getenv(name, buffer, BT_MAX_PATH)) return buffer;
	else return NULL;
}
