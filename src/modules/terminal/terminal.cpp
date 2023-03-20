#include <module/module.inc>
#include <btos/fs_interface.h>
#include "terminal.hpp"
#include "vterm.hpp"
#include "device.hpp"
#include "console_backend.hpp"
#include "api.hpp"

uint64_t default_terminal;
uint16_t terminal_extension_id;

class TerminalExtension : public IKernelExtension{
public:
	const char *GetName(){
		return "TERMINAL";
	}
	
	void UserAPIHandler(uint16_t fn, ICPUState &state){
		terminal_uapi_fn(fn, state);
	}
};

void init();

int module_main(char *){
	init();
	return 0;
}

void init(){
	terminal_extension_id = API->GetKernelExtensionManager().AddExtension(new TerminalExtension());
	API->InfoRegister("TERMS", &terms_infofs);
	init_device();
	terminals = new vterm_list();
	cons_backend = new console_backend();
	uint64_t id = terminals->create_terminal(cons_backend);
	terminals->get(id)->sync();
	cons_backend->switch_terminal(id);
	default_terminal=id;
}