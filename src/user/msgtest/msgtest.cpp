#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include "../../include/btos_stubs.h"

using namespace std;

string output_message(bt_msg_header &msg);

int main(int argc, char **argv){
    if(argc==1){
        cout << "Listening on PID " << bt_getpid() << "." << endl;
        bt_msg_header msg=bt_recv(true);
        while(true){
            string data=output_message(msg);
            if(data=="echo"){
                bt_msg_header reply;
                reply.to=msg.from;
                reply.reply_id=msg.id;
                reply.flags = bt_msg_flags::Reply;
                char *replycontent=(char*)"echo";
                reply.content=replycontent;
                reply.length=strlen(replycontent);
                uint64_t replyid=bt_send(reply);
                cout << "Sent reply ID: " << replyid << endl;
            }
            if(data=="quit") {
                bt_msg_ack(&msg);
                return 0;
            }
            bt_next_msg(&msg);
        }
    }else if(argc==3){
        bt_msg_header msg;
        int to;
        sscanf(argv[1], "%i", &to);
        msg.to=to;
        msg.length=strlen(argv[2]);
        msg.content=argv[2];
        uint64_t id=bt_send(msg);
        if(id) {
            cout << "Sent message ID: " << id << endl;
            bt_msgwait();
        }else{
            cout << "Could not send message." << endl;
        }
        bt_msg_header reply=bt_recv(false);
        if(reply.valid && (reply.flags & bt_msg_flags::Reply)){
            cout << "Recieved reply: " << endl;
            output_message(reply);
        }
        if(reply.valid) bt_msg_ack(&reply);
    }
}

string output_message(bt_msg_header &msg) {
    char *data=new char[msg.length+1]();
    cout << "Message from: " << msg.from << endl;
    cout << "ID: " << msg.id << endl;
    cout << "Length: " << msg.length << endl;
    bt_msg_content(&msg, data, msg.length);
    cout << "Data: \"" << data << "\"" << endl;
    string ret=data;
    delete data;
    return ret;
}