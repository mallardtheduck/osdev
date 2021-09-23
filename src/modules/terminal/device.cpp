#include <btos_module.h>
#include <module/utils/string.hpp>
#include "vterm.hpp"

ILock *term_lock;

const char *terminal_var="TERMID";

uint64_t atoi64(const char *str) {
	uint64_t res = 0;
	for (int i = 0; str[i] != '\0'; ++i) res = res*10 + str[i] - '0';

	return res;
}

void reverse(char str[], int length) {
	int start = 0;
	int end = length -1;
	while (start < end) {
		char tmp=*(str+start);
		*(str+start)=*(str+end);
		*(str+end)=tmp;
		start++;
		end--;
	}
}

char* i64toa(uint64_t num, char* str, int base){
	int i = 0;

	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	while (num != 0) {
		uint64_t rem = num % base;
		str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
		num = num/base;
	}

	str[i] = '\0';
	reverse(str, i);
	return str;
}

class TerminalDeviceHandle : public IVisibleDeviceInstance{
private:
	vterm *terminal = nullptr;
	vterm_options opts;
public:
	TerminalDeviceHandle(){
		auto hl = term_lock->LockExclusive();
		uint64_t termid=0;
		if(CurrentProcess().GetEnvironmentVariable(terminal_var)){
			termid = atoi64(CurrentProcess().GetEnvironmentVariable(terminal_var));
		}
		terminal = terminals->get(termid);
		if(!terminal){
			dbgpf("TERM: Could not locate terminal %i!\n", (int)termid);
			terminal = terminals->get(0);
		}
		if(!terminal) return;
		terminal->open();
		char termidvalue[128]={0};
		i64toa(terminal->get_id(), termidvalue, 10);
		CurrentProcess().SetEnvironmentVariable(terminal_var, termidvalue);
	}

	size_t Read(size_t bytes, char *buffer) override{
		if(terminal) return terminal->read(opts, bytes, buffer);
		else return 0;
	}
	size_t Write(size_t bytes, const char *buffer) override{
		if(terminal) return terminal->write(opts, bytes, buffer);
		else return 0;
	}

	bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) override{
		if(terminal) return terminal->seek(opts, pos, flags);
		else return 0;
	}

	int IOCtl(int fn, size_t bytes, char *buffer) override{
		if(terminal) return terminal->ioctl(opts, fn, bytes, buffer);
		else return 0;
	}

	int GetType() override{
		return driver_types::TERMINAL;
	}
	const char *GetDescription() override{
		return "Terminal device.";
	}

	bool Close() override{
		if(terminal) {
			terminal->close(opts);
			return true;
		}else return false;
	}
};

class TerminalDevice : public IVisibleDevice{
private:
	string name = "TERM";
public:
	IVisibleDeviceInstance *Open() override{
		return new TerminalDeviceHandle();
	}

	int GetType() override{
		return driver_types::TERMINAL;
	}
	const char *GetDescription() override{
		return "Terminal device.";
	}
	const char *GetName() override{
		return name.c_str();
	}
	void SetName(const char *n) override{
		name = n;
	}
};

void init_device(){
	term_lock = API->NewLock();
	auto device = new TerminalDevice();
	API->GetVisibleDeviceManager().AddVisibleDevice(device);
	const char *node = device->GetName();
	char devname[BT_MAX_PATH];
	sprintf(devname, "DEV:/%s", node);
	CurrentProcess().SetEnvironmentVariable("STDOUT", devname);
	CurrentProcess().SetEnvironmentVariable("STDIN", devname);
	CurrentProcess().SetEnvironmentVariable("STDERR", devname);
	CurrentProcess().SetEnvironmentVariable(terminal_var, "0");
}
