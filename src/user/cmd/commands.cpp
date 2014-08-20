#include "cmd.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void print_os_version(){
	display_file("INFO:/VERSION");
}

void display_file(const string &path){
	ifstream file(path);
	if(file.is_open()){
    	string line;
    	while(getline(file, line)) cout << line << endl;
    }
}

void list_files(const string &path){
	bt_dirhandle dir=bt_dopen(path.c_str(), FS_Read);
	if(!dir) return;
	directory_entry entry=bt_dread(dir);
	while(entry.valid){
		if(entry.type==FS_Directory){
			cout << '[' << entry.filename << ']' << '\t' << entry.size << endl;
		}else if(entry.type==FS_Device){
			cout << '{' << entry.filename << '}' << '\t' << entry.size << endl;
		}else{
			cout << entry.filename << '\t' << entry.size << endl;
		}
		entry=bt_dread(dir);
	}
	bt_dclose(dir);
}

void display_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;

	}
	display_file(parse_path(commandline[1]));
}

void ls_command(vector<string> commandline){
	if(commandline.size() < 2){
		list_files(get_cwd());
	}else{
		list_files(parse_path(commandline[1]));
	}
}

void cd_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << get_cwd() << endl;
	}else{
		string newpath=parse_path(commandline[1]);
		directory_entry ent=bt_stat(newpath.c_str());
		if(!ent.valid || ent.type != FS_Directory){
			cout << "No such directory." << endl;
		}else if(newpath.length()) set_cwd(newpath);
	}
}

void path_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << get_cwd() << endl;
	}else{
		cout << parse_path(commandline[1]) << endl;
	}
}

void touch_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;
	}else{
		string path=parse_path(commandline[1]);
		if(path.length()){
			FILE *fh=fopen(path.c_str(), "a");
			if(fh) fclose(fh);
			else cout << "Error opening file." << endl;
		}else cout << "Invalid path." << endl;
	}
}

void echo_command(vector<string> commandline){
	if(commandline.size() < 2 || (commandline[1]=="-f" && commandline.size() < 3)){
		cout << "Usage:" << endl;
		cout << commandline[0] << " [-f filename] text" << endl;
	}else{
		ostream *out=&cout;
		ofstream file;
		size_t skip=1;
		if(commandline[1]=="-f"){
			file.open(commandline[2]);
			out=&file;
			skip+=2;
		}
		for(const string &s : commandline){
			if(skip) skip--;
			else *out << s << ' ';
		}
		*out << endl;
	}
}

void mkdir_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " dirname" << endl;
	}else{
		string path=parse_path(commandline[1]);
		bt_dirhandle dh=bt_dopen(path.c_str(), FS_Read | FS_Create);
		if(dh) bt_dclose(dh);
		else cout << "Could not create directory." << endl;
	}
}

void del_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;
	}else{
		string path=parse_path(commandline[1]);
		bt_filehandle fh=bt_fopen(path.c_str(), FS_Read | FS_Delete);
		if(fh) bt_fclose(fh);
		else cout << "Could not delete file." << endl;
	}
}

void rmdir_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " dirname" << endl;
	}else{
		string path=parse_path(commandline[1]);
		bt_filehandle dh=bt_dopen(path.c_str(), FS_Read | FS_Delete);
		if(dh) bt_dclose(dh);
		else cout << "Could not remove directory." << endl;
	}
}

bool run_builtin(vector<string> commandline){
	const string command=commandline[0];
	if(command=="cat"){
		display_command(commandline);
		return true;
	}else if(command=="ls"){
      	ls_command(commandline);
      	return true;
    }else if(command=="cd"){
    	cd_command(commandline);
    	return true;
    }else if(command=="path"){
    	path_command(commandline);
    	return true;
    }else if(command=="touch"){
    	touch_command(commandline);
        return true;
    }else if(command=="echo"){
        echo_command(commandline);
		return true;
    }else if(command=="mkdir"){
		mkdir_command(commandline);
		return true;
	}else if(command=="del"){
		del_command(commandline);
		return true;
	}else if(command=="rmdir"){
		rmdir_command(commandline);
		return true;
	}
    return false;
}

bool run_program(vector<string> commandline){
	const string command=commandline[0];
	string path=parse_path(command);
	if(!command.length()) return false;
	path+=".elx";
	directory_entry ent=bt_stat(path.c_str());
	if(ent.valid && ent.type == FS_File){
		char **argv=new char*[commandline.size()];
		size_t i=0;
		for(string &s : commandline){
			argv[i]=(char*)s.c_str();
			++i;
		}
		bt_pid pid=bt_spawn(path.c_str(), commandline.size(), argv);
		delete[] argv;
		if(pid) bt_wait(pid);
		return true;
	}
	return false;
}

bool run_command(vector<string> commandline){
	if(!commandline.size()) return true;
	if(run_builtin(commandline)) return true;
	else if(run_program(commandline)) return true;
	else if(commandline[0]=="exit") return false;
	cout << "Unknown command." << endl;
	return true;
}