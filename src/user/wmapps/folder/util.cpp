#define BTOS_NO_USING
#include <btos.h>

#include <string>
#include <iostream>
#include <fstream>

#include <gui/messagebox.hpp>
#include <util/tinyformat.hpp>

#include "folder.hpp"

namespace gui = btos_api::gui;

void CopyMove(const std::string from, const std::string to, bool move, btos_api::wm::Window *parent){
	std::ifstream fromfile(from);
	std::ofstream tofile(to);
	if(!fromfile.is_open()){
		gui::MessageBox(tfm::format("Count not open source file \"%s\"!", from), "Error", LoadIcon("icons/error_32.png")).Show(parent);
		return;
	}else if(!tofile.is_open()){
		gui::MessageBox(tfm::format("Count not open target file \"%s\"!", to), "Error", LoadIcon("icons/error_32.png")).Show(parent);
		return;
	}
	bt_filesize_t sofar = 0;
	while(true){
		/*if(ent.size > 10240){
			int progress = (100 * sofar) / ent.size;
			streampos outpos = cout.tellp();
			for(size_t i = 0; i < file.length() + 10; ++i){
				cout << " ";
			}
			cout.seekp(outpos);
			cout << file << " : " << progress << "%";
			cout.seekp(outpos);
		}*/
		char buffer[4096];
		std::streamsize bytes_read = fromfile.read(buffer, 4096).gcount();
		if(bytes_read){
			tofile.write(buffer, bytes_read);
		}else break;
		sofar += bytes_read;
	}
	/*if(ent.size > 10240){
		streampos outpos = cout.tellp();
		for(size_t i = 0; i < file.length() + 10; ++i){
			cout << " ";
		}
		cout.seekp(outpos);
	}*/
	if(move){
		fromfile.close();
		auto fh = btos_api::bt_fopen(from.c_str(), FS_Read | FS_Delete);
		if(fh) btos_api::bt_fclose(fh);
	}
}