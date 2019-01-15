#include <btos_module.h>

USE_SYSCALL_TABLE;
USE_DEBUG_PRINTF;
char *current_section="default";

#include "ini.h"
#include "cmdline.hpp"

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

bool starts_with(const char *s, const char *str){
    if(strlen(str)<strlen(s)) return false;
    for(size_t i=0; i<strlen(s); ++i){
        if(s[i]!=str[i]) return false;
    }
    return true;
}

void dputs(void *handle, char *s){
	size_t buflen = (strlen(s) * 2);
	char *buf = (char*)malloc(buflen);
	for(size_t i = 0; i < buflen; ++i){
		buf[i * 2] = s[i];
		buf[(i * 2) + 1] = 0x07;
	}
	devwrite(handle, buflen, buf);
	free(buf);
}

void displaywrite(const char *s, const char *dev){
	void *handle=devopen(dev);
	if(!handle){
		dbgpf("BOOT: Specified display device: %s\n", dev);
		panic("(BOOT) Display device not valid!");
	}
    dputs(handle, (char*)s);
    devclose(handle);
}

void configure_console(const char */*value*/){
	char *dname;
	void *ditr = get_first_device(&dname);
	while(ditr){
		drv_device *dev = get_device(dname);
		auto type = dev->driver.type(dev->id);
		if((type & 0xF0) == driver_types::VIDEO){
			dbgpf("(BOOT) DISPLAY_DEVICE = %s\n", dname);
			setenv("DISPLAY_DEVICE", dname, 0, 0);
		}else if(type == driver_types::IN_KEYBOARD){
			dbgpf("(BOOT) INPUT_DEVICE = %s\n", dname);
			setenv("INPUT_DEVICE", dname, 0, 0);
		}else if(type == driver_types::IN_MOUSE){
			dbgpf("(BOOT) POINTER_DEVICE = %s\n", dname);
			setenv("POINTER_DEVICE", dname, 0, 0);
		}
		ditr = get_next_device(ditr, &dname);
	}
	displaywrite("Starting BT/OS...", getenv("DISPLAY_DEVICE", 0));
}

extern "C" int handler(void *c, const char* section, const char* name, const char* value){
	#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
	dbgpf("BOOT: [%s] %s=%s\n", section, name, value);

	if(MATCH(current_section, "configure_console")){
		configure_console(value);
	}else if(MATCH(current_section, "load")){
		char *name, *params;
		if(split(value, ',', &name, &params)){
			dbgpf("BOOT: %s,%s\n", name, params);
			module_load(name, params);
			free(name);
			free(params);
		}else module_load((char*)value, NULL);

	}else if(MATCH(current_section, "run")){
		cmdLine cmd = parse_cmd(value);
		wait(spawn(cmd.cmd, cmd.argc, cmd.argv));
		free_cmd(cmd);
    }else if(MATCH(current_section, "spawn")){
		spawn("INIT:/SPAWN.ELX", 1, (char**)&value);
	}else if(MATCH(current_section, "service")){
		char *varname, *cmd;
		if(split(value, ' ', &varname, &cmd)){
			cmdLine cmdL = parse_cmd(cmd);
			pid_t pid = spawn(cmdL.cmd, cmdL.argc, cmdL.argv);
			free_cmd(cmdL);
			char buf[64] = {0};
			sprintf(buf, "%i", (int)pid);
			setenv(varname, buf, 0, 0);
			free(varname);
			free(cmd);
		}
	}else if(MATCH(current_section, "mount")){
		char *path, *rest;
		if(split(value, ',', &path, &rest)){
			char *name, *fs;
			if(split(rest, ',', &name, &fs)){
				if(!mount(name, path, fs)){
					char errormsg[128];
					sprintf(errormsg, "(BOOT) Could not mount %s.\n", path);
					panic(errormsg);
				}
				free(name);
				free(fs);
			}
			free(path);
			free(rest);
		}
	}else if(MATCH(current_section, "setwait")){
		setenv(value, "-", ENV_Global, 0);
	}else if(MATCH(current_section, "waitfor")){
		char *v = getenv(value, 0);
		while(strlen(v) <= 1){
			yield();
			v = getenv(value, 0);
		}
		setenv(value, "", ENV_Global, 0);
	}else if(strcmp(section, current_section) == 0 && starts_with("set ", name)){
        char *set, *varname;
        if(split(name, ' ', &set, &varname)){
            setenv(varname, (char*)value, 0, 0);
            free(set);
            free(varname);
        }
    }else if(strcmp(section, current_section) == 0 && starts_with("kset ", name)){
        char *set, *varname;
        if(split(name, ' ', &set, &varname)){
            set_kvar(varname, (char*)value);
            free(set);
            free(varname);
        }
	}
	return 1;
}

void boot_thread(void*){
	dbgout("BOOT: Boot manager loaded.\n");
	if (ini_parse("INIT:/config.ini", &handler, nullptr) < 0) {
            panic("(BOOT) Can't load 'config.ini'!\n");
    }
}

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	new_thread(&boot_thread, NULL);
	return 0;
}
