#include "module_stubs.h"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#include "ini.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

char *strdup(const char *s){
	char *ret=(char*)malloc(strlen(s)+1);
	strncpy(ret, s, strlen(s)+1);
	return ret;
}

bool split(const char *string, char c, char **before, char **after){
	for(size_t i=0; string && string[i]; ++i){
		if(string[i]==c){
			*before=(char*)malloc(i+1);
			memset((void*)*before, 0, i+1);
			memcpy((void*)*before, (void*)string, i);
			*after=strdup(&string[i+1]);
			return true;
		}
	}
	return false;
}

void dputs(void *handle, char *c){
	devwrite(handle, strlen(c), c);
}

struct config{
	char *display;
	char *input;
} c;

void displaywrite(const char *s){
	void *handle=devopen(c.display);
	if(!handle){
		dbgpf("BOOT: Specified display device: %s\n", c.display);
		panic("(BOOT) Display device not valid!");
	}
    dputs(handle, (char*)s);
    devclose(handle);
}

extern "C" int handler(void *c, const char* section, const char* name, const char* value){
	#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	dbgpf("BOOT: [%s] %s=%s\n", section, name, value);

	if(MATCH("default", "display")){
		((config*)c)->display=strdup(value);
		setenv("DISPLAY_DEVICE", ((config*)c)->display, 0, 0);
		displaywrite("Starting BT/OS...");
	}else if(MATCH("default", "input")){
		((config*)c)->input=strdup(value);
		setenv("INPUT_DEVICE", ((config*)c)->input, 0, 0);
	}else if(MATCH("default", "load")){
		char *name, *params;
		if(split(value, ',', &name, &params)){
			dbgpf("BOOT: %s,%s\n", name, params);
			module_load(name, params);
			free(name);
			free(params);
		}else module_load((char*)value, NULL);
	}else if(MATCH("default", "run")){
		wait(spawn((char*)value, NULL));
	}
	return 1;
}

void boot_thread(void*){
	dbgout("BOOT: Boot manager loaded.\n");
	if (ini_parse("INIT:/config.ini", &handler, &c) < 0) {
            panic("(BOOT) Can't load 'config.ini'!\n");
    }
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	new_thread(&boot_thread, NULL);
	return 0;
}
