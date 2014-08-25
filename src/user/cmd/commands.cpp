#include "cmd.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>

using namespace std;

typedef void (*command_fn)(const vector<string>&);

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

void list_files(const string &path, ostream &out=cout, char sep='\t'){
	bt_dirhandle dir=bt_dopen(path.c_str(), FS_Read);
	if(!dir) return;
	bt_directory_entry entry=bt_dread(dir);
	while(entry.valid){
		if(entry.type==FS_Directory){
			out << '[' << entry.filename << ']' << sep << "---" << endl;
		}else if(entry.type==FS_Device){
			out << '{' << entry.filename << '}' << sep << "---" << endl;
		}else{
			out << entry.filename << sep << entry.size << endl;
		}
		entry=bt_dread(dir);
	}
	bt_dclose(dir);
}

void display_command(const vector<string> &commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;

	}
	display_file(parse_path(commandline[1]));
}

void ls_command(const vector<string> &commandline){
	string path;
	if(commandline.size() < 2){
		path=get_cwd();
	}else{
		path=parse_path(commandline[1]);
	}
	stringstream ls;
	ls << "# name, size" << endl;
	list_files(path, ls, ',');
	display_table(ls.str());
}

void cd_command(const vector<string> &commandline){
	if(commandline.size() < 2){
		cout << get_cwd() << endl;
	}else{
		string newpath=parse_path(commandline[1]);
		bt_directory_entry ent=bt_stat(newpath.c_str());
		if(!ent.valid || ent.type != FS_Directory){
			cout << "No such directory." << endl;
		}else if(newpath.length()) set_cwd(newpath);
	}
}

void path_command(const vector<string> &commandline){
	if(commandline.size() < 2){
		cout << get_cwd() << endl;
	}else{
		cout << parse_path(commandline[1]) << endl;
	}
}

void touch_command(const vector<string> &commandline){
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

void echo_command(const vector<string> &commandline){
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

void mkdir_command(const vector<string> &commandline){
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

void del_command(const vector<string> &commandline){
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

void rmdir_command(const vector<string> &commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " dirname" << endl;
	}else{
		string path=parse_path(commandline[1]);
		bt_filehandle dh=bt_dopen(path.c_str(), FS_Read | FS_Delete);
		if(dh) bt_dclose(dh);
		else cout << "Could not open directory." << endl;
		dh=bt_dopen(path.c_str(), FS_Read);
        if(dh){
            cout << "Could not remove directory." << endl;
            bt_dclose(dh);
        }
	}
}

void copy_command(const vector<string> &commandline){
	if(commandline.size() < 3){
		cout << "Usage:" << endl;
		cout << commandline[0] << " from to" << endl;
	}else{
		string from=parse_path(commandline[1]);
		string to=parse_path(commandline[2]);
		if(is_directory(from)){
			cout << "Cannot copy directory." << endl;
		}
		if(is_directory(to)){
			string filename=path_file(from);
			to=parse_path(to + '/' + filename);
		}
		ifstream fromfile(from);
		ofstream tofile(to);
		if(!fromfile.is_open() || !tofile.is_open()){
			cout << "Could not open files." << endl;
		}
		while(true){
			char buffer[512];
			streamsize bytes_read=fromfile.read(buffer, 512).gcount();
			if(bytes_read){
				tofile.write(buffer, bytes_read);
			}else break;
		}
	}
}

void move_command(const vector<string> &commandline){
	if(commandline.size() < 3){
		cout << "Usage:" << endl;
		cout << commandline[0] << " from to" << endl;
	}else{
		copy_command(commandline);
		del_command(commandline);
	}
}

void ver_command(const vector<string>&){
	cout << "BT/OS CMD" << endl;
	print_os_version();
}

void list_command(const vector<string> &commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " pattern" << endl;
	}else{
		vector<string> matches=resolve_wildcards(commandline[1]);
		for(const string &s : matches){
			cout << s << endl;
		}
	}
}

unordered_map<string, command_fn> builtin_commands={
	{"ls", &ls_command},
	{"dir", &ls_command},
	{"cat", &display_command},
	{"type", &display_command},
	{"cd", &cd_command},
	{"chdir", &cd_command},
	{"path", &path_command},
	{"realpath", &path_command},
	{"touch", &touch_command},
	{"create", &touch_command},
	{"echo", &echo_command},
	{"print", &echo_command},
	{"mkdir", &mkdir_command},
	{"md", &mkdir_command},
	{"del", &del_command},
	{"delete", &del_command},
	{"erase", &del_command},
	{"rm", &del_command},
	{"rmdir", &rmdir_command},
	{"rd", &rmdir_command},
	{"copy", &copy_command},
	{"cp", &copy_command},
	{"move", &move_command},
	{"mv", &move_command},
	{"ver", &ver_command},
	{"table", &table_command},
	{"tbl", &table_command},
	{"list", &list_command},
};

bool run_builtin(const vector<string> &commandline){
	const string command=to_lower(commandline[0]);
	if(builtin_commands.find(command)!=builtin_commands.end()){
		builtin_commands[command](commandline);
		return true;
     }
    return false;
}

bool run_program(const vector<string> &commandline){
	const string command=to_lower(commandline[0]);
	string path=parse_path(command);
	if(!command.length()) return false;
	path+=".elx";
	bt_directory_entry ent=bt_stat(path.c_str());
	if(ent.valid && ent.type == FS_File){
		char **argv=new char*[commandline.size()];
		size_t i=0;
		for(const string &s : commandline){
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

bool run_command(const vector<string> &commandline){
	if(!commandline.size()) return true;
	if(run_builtin(commandline)) return true;
	else if(run_program(commandline)) return true;
	else if(commandline[0]=="exit") return false;
	cout << "Unknown command." << endl;
	return true;
}