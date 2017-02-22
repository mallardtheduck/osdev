#include <btos.h>
#include <ext/debug.h>
#include <dev/terminal.h>
#include <dev/keyboard.h>
#include <crt_support.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

#include <udis86.h>

#include "debug.hpp"
#include "commands.hpp"
#include "table.hpp"
#include "symbols.hpp"

using namespace std;

volatile bt_pid_t selected_pid;
volatile uint64_t selected_thread;
volatile bool watch_enabled;

void watch_thread(void *){
	bt_msg_header msg = bt_recv(true);
    while(true){
        if(msg.from == 0 && msg.source == debug_ext_id) {
            bt_debug_event_msg content;
            bt_msg_content(&msg, (void *) &content, sizeof(content));
            if(watch_enabled && (selected_pid == 0 || content.pid == selected_pid)){
				out_event(content);
				if(content.event == bt_debug_event::Exception || content.event == bt_debug_event::ThreadEnd){
					context ctx = get_context(content.thread);
					out_context(ctx);
					do_stacktrace(content.pid, ctx);
				}
			}	
            bt_msg_header reply;
            reply.to = 0;
            reply.reply_id = msg.id;
            reply.flags = bt_msg_flags::Reply;
            reply.length = 0;
            bt_send(reply);
		}
		bt_next_msg(&msg);
	}
}

void watch_command(){
	cout << "Watch started. Press <return> to break." << endl;
	watch_enabled=true;
	string q;
	getline(cin, q);
	watch_enabled=false;
}

void proc_command(const vector<string> &args){
	if(args.size() == 2){
		if(args[1] != "none"){
			bt_pid_t newpid = atoll(args[1].c_str());
			bool found = false;
			ifstream info("INFO:/PROCS");
			table tbl = parsecsv(info);
			for(auto row: tbl.rows){
				if((bt_pid_t)atoll(row["PID"].c_str()) == newpid){
					found = true;
					break;
				}
			}
			if(!found){
				cout << "PID not found." << endl;
				return;
			}
			if(newpid != selected_pid){
				selected_thread = 0;
				selected_pid = newpid;
				cout << "Loading symbols..." << flush;
				load_symbols(selected_pid);
				cout << "Done." << endl;
			}
		}else{
			selected_pid = 0;
			selected_thread = 0;
		}
	}
	if(selected_pid > 0){
		cout << "PID " << selected_pid << " selected." << endl;
		ifstream info("INFO:/THREADS");
		table tbl = parsecsv(info);
		uint64_t thread = 0;
		for(auto row: tbl.rows){
			if((bt_pid_t)atoll(row["PID"].c_str()) == selected_pid){
				if(thread == 0) thread = atoll(row["ID"].c_str());
				else{
					thread = 0;
					break;
				}
			}
		}
		if(thread){
			selected_thread = thread;
			cout << "Thread " << selected_thread << " selected." << endl;
		}
	}
	else cout << "No process selected." << endl;
}

void thread_command(const vector<string> &args){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	if(args.size() == 2){
		if(args[1] != "none"){
			uint64_t newthread = atoll(args[1].c_str());
			bool found = false;
			ifstream info("INFO:/THREADS");
			table tbl = parsecsv(info);
			for(auto row: tbl.rows){
				if((uint64_t)atoll(row["ID"].c_str()) == newthread){
					found = true;
					break;
				}
			}
			if(!found){
				cout << "Thread not found." << endl;
				return;
			}
			selected_thread = newthread;
		}else{
			selected_thread = 0;
		}
	}
	if(selected_pid > 0) cout << "Thread " << selected_thread << " selected." << endl;
	else cout << "No thread selected." << endl;
}

void procs_command(){
	ifstream info("INFO:/PROCS");
	table tbl = parsecsv(info);
	for(auto row: tbl.rows){
		cout << row["PID"] << " - " << row["path"] << endl;
	}
}

string thread_status_string(int status){
	//Runnable = 0,
	//Blocked = 1,
	//DebugStopped = 2,
	//DebugBlocked = 3,
	//Ending = 4,
	//Special = 5,
	if(status == 0) return "Runnable";
	if(status == 1) return "Blocked";
	if(status == 2 || status == 3) return "Halted by debugger";
	if(status == 4) return "Ending";
	if(status == 5) return "Special";
	return "Unknown";
}

void threads_command(){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	ifstream info("INFO:/THREADS");
	table tbl = parsecsv(info);
	for(auto row: tbl.rows){
		if((bt_pid_t)atoll(row["PID"].c_str()) == selected_pid){
			cout << row["ID"] << " - Status: " << thread_status_string(atoi(row["status"].c_str())) << " Load: " << row["load"];
			if(atoi(row["alevel"].c_str()) == 0) cout << " - Usermode";
			else cout << " - Kernel";
			cout << endl;
		}
	}
}

void stat_command(){
	if(!selected_thread){
		cout << "No thread selected." << endl;
		return;
	}
	context ctx = get_context(selected_thread);
	out_context(ctx);
	do_stacktrace(selected_pid, ctx);
}

void modules_command(){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	vector<module> modules = get_modules(selected_pid);
	for(auto m: modules){
		cout << m.name << hex << " - Base: " << m.base << " Limit: " << m.limit << " - " << m.path << endl;
	}
	cout << dec;
}

void ldsyms_command(){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	cout << "Loading symbols..." << flush;
	load_symbols(selected_pid, true);
	cout << "Done." << endl;
}

static symbol get_best_symbol(const string &name){
	vector<symbol> proc_symbols = load_symbols(selected_pid);
	vector<symbol> syms = get_symbols_by_name(proc_symbols, name);
	remove_if(syms.begin(), syms.end(), [](const symbol &s){ return s.size == 0; });
	if(syms.size() == 0){
		return null_symbol;
	}
	return syms[0];
}

void dump_command(const vector<string> &args){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	if(args.size() != 2){
		cout << "No symbol specified." << endl;
		return;
	}
	symbol sym = get_best_symbol(args[1]);
	if(sym.address == 0){
		cout << "Symbol not found." << endl;
		return;
	}
	cout << "Symbol: " << sym.name << " At: " << hex << sym.address << " In: " << sym.file << endl;
	for(size_t i = 0; i < sym.size; ++i){
		intptr_t addr = sym.address + i;
		uint8_t c;
		debug_peek(&c, selected_pid, addr, 1);
		cout << hex << setfill('0') << setw(2) << (unsigned)c << ' ';
	}
	cout << endl;
	cout.copyfmt(ios(NULL));
}

void info_command(const vector<string> &args){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	if(args.size() != 2){
		cout << "No symbol specified." << endl;
		return;
	}
	symbol sym = get_best_symbol(args[1]);
	if(sym.address == 0){
		cout << "Symbol not found." << endl;
		return;
	}
	cout << "Symbol: " << sym.name << endl;
	cout << "Address: " << hex << sym.address << endl;
	cout << "Module: " << sym.file << endl;
	cout << "Size: " << dec << sym.size << endl;
	cout.copyfmt(ios(NULL));
}

void disas_command(const vector<string> &args){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	if(args.size() != 2){
		cout << "No symbol specified." << endl;
		return;
	}
	
	symbol sym = get_best_symbol(args[1]);
		if(sym.address == 0){
		cout << "Symbol not found." << endl;
		return;
	}
	
	
	vector<uint8_t> mem;
	cout << "Symbol: " << sym.name << " At: " << hex << sym.address << " In: " << sym.file << endl;
	for(size_t i = 0; i < sym.size; ++i){
		intptr_t addr = sym.address + i;
		uint8_t c;
		debug_peek(&c, selected_pid, addr, 1);
		mem.push_back(c);
	}
	
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_pc(&ud_obj, sym.address);
	ud_set_input_buffer(&ud_obj, mem.data(), mem.size());
	ud_set_syntax(&ud_obj, UD_SYN_ATT);
	while(ud_disassemble(&ud_obj)){
		cout << hex << setfill('0') << setw(8) << ud_insn_off(&ud_obj) << " - " << ud_insn_hex(&ud_obj);
		cout << " - " << ud_insn_asm(&ud_obj) << endl;
	}
	cout.copyfmt(ios(NULL));
}

std::string input_command(){
	cout << ">";
	string ret;
	getline(cin, ret);
	return ret;
}

bool do_command(string cmd){
	auto line = splitline(cmd, ' ');
	if(line.size() >= 1){
		if(line[0] == "watch"){
			watch_command();
		}else if(line[0] == "proc"){
			proc_command(line);
		}else if(line[0] == "thread"){
			thread_command(line);
		}else if(line[0] == "procs"){
			procs_command();
		}else if(line[0] == "threads"){
			threads_command();
		}else if(line[0] == "stat"){
			stat_command();
		}else if(line[0] == "modules"){
			modules_command();
		}else if(line[0] == "ldsyms"){
			ldsyms_command();
		}else if(line[0] == "dump"){
			dump_command(line);
		}else if(line[0] == "info"){
			info_command(line);
		}else if(line[0] == "disas"){
			disas_command(line);
		}else if(line[0] == "quit"){
			return false;
		}else{
			cout << "Unknown command." << endl;
		}
	}
	return true;
}

