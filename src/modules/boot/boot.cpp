#include <module/module.inc>

const char *current_section = "default";

#include "ini.h"
#include "cmdline.hpp"

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

char *strdup(const char *s){
	size_t size = strlen(s) + 1;
	char *ret = (char*)malloc(size);
	strncpy(ret, s, size);
	return ret;
}

bool split(const char *str, char c, char **before, char **after){
	for(size_t i = 0; str && str[i]; ++i){
		if(str[i]==c){
			size_t beforeSize = i + 1;
			*before = (char*)malloc(beforeSize);
			memset((void*)*before, 0, beforeSize);
			memcpy((void*)*before, (void*)str, i);
			if(str[beforeSize]) *after = strdup(&str[beforeSize]);
			else after = nullptr;
			return true;
		}
	}
	return false;
}

bool starts_with(const char *s, const char *str){
	if(strlen(str) < strlen(s)) return false;
	for(size_t i = 0; i < strlen(s); ++i){
		if(s[i] != str[i]) return false;
	}
	return true;
}

void dputs(IVisibleDeviceInstance *handle, const char *s){
	// (void)handle; (void)s;
	// return;
	dbgpf("dputs(%p, %p \"%s\")\n", handle, s, s);
	size_t slen = strlen(s);
	size_t buflen = slen * 2;
	char *buf = (char*)malloc(buflen);
	dbgpf("buf: %p buflen: %lu\n", buf, buflen);
	for(size_t i = 0; i < slen; ++i){
		buf[i * 2] = s[i];
		buf[(i * 2) + 1] = 0x07;
	}
	handle->Write(buflen, buf);
	free(buf);
}

uint64_t atoi64(const char *str) {
	uint64_t res = 0;
	for (int i = 0; str[i] != '\0'; ++i) res = res*10 + str[i] - '0';

	return res;
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
		bt_pid_t pid = 0;
		{
			auto proc = API->GetProcessManager().Spawn(cmd.cmd, args);
			pid = proc->ID();
		}
		free_cmd(cmd);
		if(pid) API->GetProcessManager().WaitProcess(pid);
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
					auto mount = filesystem->Mount(node);
					if(mount){
						API->GetVirtualFilesystem().Attach(name, mount);
					}else{
						char errormsg[128];
						sprintf(errormsg, "(BOOT) Could not mount %s (mount failed).\n", path);
						panic(errormsg);
					}
				}else{
					char errormsg[128];
					sprintf(errormsg, "(BOOT) Could not mount %s (fs: %p node: %p).\n", path, filesystem, node.get());
					panic(errormsg);
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
		API->CurrentThread().SetPriority(1000);
		while(strlen(v) <= 1){
			API->CurrentThread().Yield();
			asm volatile("pause");
			v = API->CurrentProcess().GetEnvironmentVariable(value);
		}
		API->CurrentThread().SetPriority(10);
		API->CurrentProcess().SetEnvironmentVariable(value, "");
	}else if(MATCH(current_section, "waitstage")){
		char *pidVar, *stageStr;
		if(split(value, ' ', &pidVar, &stageStr)){
			const char *pidStr = API->CurrentProcess().GetEnvironmentVariable(pidVar);
			bt_pid_t pid = atoi64(pidStr);
			size_t stage = atoi64(stageStr);
			dbgpf("BOOT: Waiting for proc %llu to reach stage %lu\n", pid, stage);
			API->CurrentThread().SetBlock([&]{
				auto proc = API->GetProcess(pid);
				if(!proc) return true;
				return proc->GetProcStage() >= stage;
			});
			free(pidVar);
			free(stageStr);
		}
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
	API->CurrentThread().SetName("Boot");
	dbgout("BOOT: Boot manager loaded.\n");
	if (ini_parse("INIT:/config.ini", &handler, nullptr) < 0) {
			panic("(BOOT) Can't load 'config.ini'!\n");
	}
}

int module_main(char *){
	API->GetScheduler().NewThread(&boot_thread);
	return 0;
}
