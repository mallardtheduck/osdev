#include "../../../../../include/btos_stubs.h"

char* getenv (const char* name){
	static char buffer[BT_MAX_PATH];
	bt_getenv(name, buffer, BT_MAX_PATH);
	return buffer;
}
