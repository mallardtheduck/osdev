#include "hwpnp_internal.hpp"

namespace hwpnp = btos_api::hwpnp;

static uint16_t dmi_ext_id;
static bt_pid_t dmi_pid = 0;

static void dmi_extension_uapi(uint16_t fn, ICPUState &state){
	switch(fn){
		case bt_dm_function::Register:
			dmi_pid = CurrentProcess().ID();
			break;
		case bt_dm_function::GetFirstDevice:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(dm_dev_info))){
				*((dm_dev_info*)state.Get32BitRegister(Generic_Register::GP_Register_B)) = get_first_device();
			}
			break;
		case bt_dm_function::GetNextDevice:
			if(is_safe_ptr(state.Get32BitRegister(Generic_Register::GP_Register_B), sizeof(dm_dev_info))){
				*((dm_dev_info*)state.Get32BitRegister(Generic_Register::GP_Register_B)) = get_next_device(*(dm_dev_info*)state.Get32BitRegister(Generic_Register::GP_Register_B));
			}
			break;
	}
}

static module_api::kernel_extension dmi_extension = {
	(char*)"DMI", NULL, &dmi_extension_uapi
};

void pnp_dmi_init(){
	dmi_ext_id = add_extension(&dmi_extension);
}

static void dmi_notify(bt_dm_event::Enum event, const hwpnp::DeviceID &dev){
	if(!dmi_pid || proc_get_status(dmi_pid) != btos_api::bt_proc_status::Running) return;
	btos_api::bt_msg_header msg;
	msg.from = 0;
	msg.source = dmi_ext_id;
	msg.to = dmi_pid;
	msg.flags = 0;
	msg.type = event;
	msg.content = (void*)&dev;
	msg.length = sizeof(dev);
	uint64_t msg_id = msg_send(msg);
	btos_api::bt_msg_header reply = msg_recv_reply_block(msg_id);
	msg_acknowledge(reply, true);
}

void pnp_dmi_notify_device_found(const hwpnp::DeviceID &dev){
	dmi_notify(bt_dm_event::DeviceFound, dev);
}