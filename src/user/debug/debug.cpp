#include <iostream>
#include <btos_stubs.h>

uint16_t debug_ext_id;

bool init_debug(){
    debug_ext_id = bt_query_extension("DEBUG");
    return debug_ext_id != 0;
}

uint32_t call_debug(uint16_t fn, uint32_t b, uint32_t c, uint32_t d){
    uint32_t a = (debug_ext_id << 16) + fn;
    return btos_call(a, b, c, d);
}

void debug_register(){
    call_debug(0, 0, 0, 0);
}

int main(){
    if(!init_debug()){
        std::cout << "Could not locate DEBUG extension." << std::endl;
        return 0;
    }
    std::cout << "DEBUG extension ID: " << debug_ext_id << std::endl;
    debug_register();

    bt_msg_header msg = bt_recv(true);
    while(true){
        bt_pid_t pid;
        bt_msg_content(&msg, (void*)&pid, sizeof(pid));
        std::cout << "PID: " << pid << " crashed." << std::endl;
        bt_msg_header reply;
        reply.to = 0;
        reply.reply_id = msg.id;
        reply.flags = bt_msg_flags::Reply;
        reply.length = 0;
        bt_send(reply);
        bt_next_msg(&msg);
    }

    return 0;
}
