#include <module/module.inc>

const char *current_section = "default";

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

void dputs(IVisibleDeviceInstance *handle, const char *s){
	size_t buflen = (strlen(s) * 2);
	char *buf = (char*)malloc(buflen);
	for(size_t i = 0; i < buflen; ++i){
		buf[i * 2] = s[i];
		buf[(i * 2) + 1] = 0x07;
	}
	handle->Write(buflen, buf);
	free(buf);
}

void displaywrite(const char *s, const char *dev){
	auto device = API->GetVisibleDeviceManager().GetVisibleDevice(dev);
	if(device){
		auto handle = device->Open();
		if(handle){
			dputs(handle, s);
			handle->Close();
			delete handle;
		}
	}else{
		dbgpf("BOOT: Specified display device: %s\n", dev);
		panic("(BOOT) Display device not valid!");
	}
}

void configure_console(const char */*value*/){
	auto &proc = API->CurrentProcess();
	for(auto &dev : API->GetVisibleDeviceManager()){
		auto type = dev.GetType();
		auto dname = dev.GetName();
		if((type & 0xF0) == driver_types::VIDEO){
			dbgpf("(BOOT) DISPLAY_DEVICE = %s\n", dname);
			proc.SetEnvironmentVariable("DISPLAY_DEVICE", dname);
		}else if(type == driver_types::IN_KEYBOARD){
			dbgpf("(BOOT) INPUT_DEVICE = %s\n", dname);
			proc.SetEnvironmentVariable("INPUT_DEVICE", dname);
		}else if(type == driver_types::IN_MOUSE){
			dbgpf("(BOOT) POINTER_DEVICE = %s\n", dname);
			proc.SetEnvironmentVariable("POINTER_DEVICE", dname);
		}
	}
	displaywrite("Starting BT/OS...", proc.GetEnvironmentVariable("DISPLAY_DEVICE"));
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
			API->LoadModule(name, params);
			free(name);
			free(params);
		}else API->LoadModule((char*)value, NULL);

	}else if(MATCH(current_section, "run")){
		cmdLine cmd = parse_cmd(value);
		vector<const char*> args;
		for(size_t i = 0; i < cmd.argc; ++i) args.push_back(cmd.argv[i]);
		auto proc = API->GetProcessManager().Spawn(cmd.cmd, args);
		free_cmd(cmd);
		if(proc) proc->Wait();
	}else if(MATCH(current_section, "spawn")){
		vector<const char*> args;
		args.push_back(value);
		API->GetProcessManager().Spawn("INIT:/SPAWN.ELX", args);
	}else if(MATCH(current_section, "service")){
		char *varname, *cmd;
		if(split(value, ' ', &varname, &cmd)){
			cmdLine cmdL = parse_cmd(cmd);
			vector<const char*> args;
			for(size_t i = 0; i < cmdL.argc; ++i) args.push_back(cmdL.argv[i]);
			auto proc = API->GetProcessManager().Spawn(cmdL.cmd, args);
			free_cmd(cmdL);
			if(proc){
				auto pid = proc->ID();
				char buf[64] = {0};
				sprintf(buf, "%i", (int)pid);
				API->CurrentProcess().SetEnvironmentVariable(varname, buf);
			}
			free(varname);
			free(cmd);
		}
	}else if(MATCH(current_section, "mount")){
		char *path, *rest;
		if(split(value, ',', &path, &rest)){
			char *name, *fs;
			if(split(rest, ',', &name, &fs)){
				auto filesystem = API->GetFilesystemManager().GetByName(fs);
				auto node = API->GetVirtualFilesystem().GetNode(path);
				if(filesystem && (strcmp(path, "") == 0 || node)){
					auto mount = filesystem->Mount(*node);
					if(mount){
						API->GetVirtualFilesystem().Attach(name, mount);
					}else{
						char errormsg[128];
						sprintf(errormsg, "(BOOT) Could not mount %s.\n", path);
						panic(errormsg);
					}
				}
				free(name);
				free(fs);
			}
			free(path);
			free(rest);
		}
	}else if(MATCH(current_section, "setwait")){
		API->CurrentProcess().SetEnvironmentVariable(value, "-", ENV_Global);
	}else if(MATCH(current_section, "waitfor")){
		const char *v = API->CurrentProcess().GetEnvironmentVariable(value);
		while(strlen(v) <= 1){
			API->CurrentThread().Yield();
			v = API->CurrentProcess().GetEnvironmentVariable(value);
		}
		API->CurrentProcess().SetEnvironmentVariable(value, "");
	}else if(strcmp(section, current_section) == 0 && starts_with("set ", name)){
		char *set, *varname;
		if(split(name, ' ', &set, &varname)){
			API->CurrentProcess().SetEnvironmentVariable(varname, (char*)value);
			free(set);
			free(varname);
		}
	}else if(strcmp(section, current_section) == 0 && starts_with("kset ", name)){
		char *set, *varname;
		if(split(name, ' ', &set, &varname)){
			API->GetKernelConfigVariables().SetVariable(varname, (char*)value);
			free(set);
			free(varname);
		}
	}
	return 1;
}

void boot_thread(){
	dbgout("BOOT: Boot manager loaded.\n");
	if (ini_parse("INIT:/config.ini", &handler, nullptr) < 0) {
			panic("(BOOT) Can't load 'config.ini'!\n");
	}
}

extern "C" int module_main(IModuleAPI *api, char *params){
	ModuleInit(api);
	API->GetScheduler().NewThread(&boot_thread);
	return 0;
}
