#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cstdlib>

#include "debug.hpp"
#include "symbols.hpp"
#include "commands.hpp"

using namespace std;

symbol get_best_symbol(const string &name);

template<typename T> void print_symbol(const symbol &sym){
	size_t vsize = sizeof(T);
	for(size_t i = 0; i < sym.size; i+=vsize){
		T v;
		debug_peek((void*)&v, selected_pid, sym.address + i, vsize);
		cout << v << ' ';
	}
	cout << endl;
}

void print_command(const vector<string> &args){
	if(!selected_pid){
		cout << "No process selected." << endl;
		return;
	}
	if(args.size() < 3){
		cout << "Type and symbol required." << endl;
		return;
	}
	
	symbol sym = get_best_symbol(args[2]);
	if(sym.address == 0){
		cout << "Symbol not found." << endl;
		return;
	}
	
	map<string, void (*)(const symbol&)> printers = 
	{ 
		{ "int", &print_symbol<int> },
		{ "int32", &print_symbol<int32_t> },
		{ "uint", &print_symbol<unsigned int> },
		{ "uint32", &print_symbol<uint32_t> },
		{ "unsigned", &print_symbol<unsigned> },
		{ "size_t", &print_symbol<size_t> },
		{ "int16", &print_symbol<int16_t> },
		{ "short", &print_symbol<short> },
		{ "uint16", &print_symbol<uint16_t> },
		{ "int64", &print_symbol<int64_t> },
		{ "uint64", &print_symbol<uint64_t> },
		{ "pointer", &print_symbol<void*> },
		{ "ptr", &print_symbol<void*> },
		{ "char", &print_symbol<char> },
	};
		
	if(printers.find(args[1]) != printers.end()){
		printers[args[1]](sym);
	}else{
		cout << "Unknown type" << endl;
		return;
	}
}
