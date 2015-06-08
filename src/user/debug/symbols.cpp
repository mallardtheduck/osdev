#include "debug.hpp"
#include "table.hpp"
#include "symbols.hpp"
#include <libelf.h>
#include <gelf.h>
#include <fcntl.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unistd.h>

using namespace std;

string get_pid_filename(bt_pid_t pid){
	ifstream info("INFO:/PROCS");
	table tbl = parsecsv(info);
	for(auto row : tbl.rows){
		if(atoi(row["PID"].c_str()) == (int)pid){
			return row["path"];
		}
	}
	return "";
}

void test_symbols(string filename) {
	if ( elf_version ( EV_CURRENT ) == EV_NONE )
		printf (" ELF library initialization failed : %s " , elf_errmsg ( -1));

	int fd = open(filename.c_str(), O_RDONLY, 0);
	Elf *e;
	if (( e = elf_begin ( fd , ELF_C_READ, NULL )) == NULL )
		printf (" elf_begin () failed : %s . " , elf_errmsg ( -1));

	Elf_Kind ek = elf_kind(e);

	const char *k;
	switch (ek) {
		case ELF_K_AR:
			k = " ar (1) archive ";
			break;
		case ELF_K_ELF:
			k = " elf object ";
			break;
		case ELF_K_NONE:
			k = " data ";
			break;
		default:
			k = " unrecognized ";
	}
	cout << "Elf_Kind: " << k << endl;

	Elf_Scn *scn = NULL;
	GElf_Shdr shdr;
	while ((scn = elf_nextscn(e, scn)) != NULL) {
		gelf_getshdr(scn, &shdr);
		if (shdr.sh_type == SHT_SYMTAB) {
			/* found a symbol table, go print it. */
			break;
		}
	}
	Elf_Data *data = elf_getdata(scn, NULL);
	size_t count = shdr.sh_size / shdr.sh_entsize;
	GElf_Sym sym;
	for(size_t ndx = 0; ndx < count; ++ndx) {
		gelf_getsym(data, ndx, &sym);
		cout << sym.st_value << ":" << elf_strptr(e, shdr.sh_link, sym.st_name) << endl;
	}
}

vector<symbol> get_symbols(bt_pid_t pid){
	vector<symbol> ret;
	string filename = get_pid_filename(pid);
	if (elf_version(EV_CURRENT) == EV_NONE) throw string("Init fail.");
	int fd = open(filename.c_str(), O_RDONLY, 0);
	Elf *e = elf_begin(fd, ELF_C_READ, NULL);
	if(!e) throw string("Symbol load fail.");
	Elf_Scn *scn = NULL;
	GElf_Shdr shdr;
	while((scn = elf_nextscn(e, scn))){
		gelf_getshdr(scn, &shdr);
		if(shdr.sh_type == SHT_SYMTAB){
			Elf_Data *data = elf_getdata(scn, NULL);
			size_t count = shdr.sh_size / shdr.sh_entsize;
			GElf_Sym sym;
			for(size_t ndx = 0; ndx < count; ++ndx){
				symbol s;
				gelf_getsym(data, ndx, &sym);
				s.name = elf_strptr(e, shdr.sh_link, sym.st_name);
				s.address = sym.st_value;
				ret.push_back(s);
			}
		}
	}
	elf_end(e);
	close(fd);
	return ret;
}


symbol get_symbol(vector<symbol> symbols, intptr_t addr){
	symbol ret;
	ret.address = 0;
	ret.name = "(Unknown)";
	for(auto sym : symbols){
		if(ret.address < sym.address && sym.address < addr){
			ret = sym;
		}
	}
	return ret;
}