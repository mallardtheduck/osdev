#include "api.hpp"
#include <terminal.h>

void terminal_uapi_fn(uint16_t fn, isr_regs */*regs*/){
	switch(fn){
		case bt_terminal_api::RegisterBackend:{
			break;
		}
		case bt_terminal_api::CreateTerminal:{
			break;
		}
		case bt_terminal_api::ReadBuffer:{
			break;
		}
	}
}

uapi_hanlder_fn terminal_uapi = &terminal_uapi_fn;