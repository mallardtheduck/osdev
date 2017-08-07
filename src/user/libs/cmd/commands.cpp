#include <cmd/commands.hpp>
#include <cmd/utils.hpp>
#include <cmd/globbing.hpp>
#include <cmd/path.hpp>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <dev/rtc.h>
#include <btos/process.hpp>

using namespace std;

namespace btos_api{
namespace cmd{

typedef void (*command_fn)(const command &);

void print_os_version(ostream &output=cout){
	display_file("INFO:/VERSION", output);
}

void display_file(const string &path, ostream &output){
	ifstream file(path);
	if(file.is_open()){
    	string line;
    	while(getline(file, line)) output << line << endl;
    }
}

void list_files(string path, ostream &out=cout, char sep='\t'){
	if(is_dir(path)) path+="/*";
	vector<string> files=glob(path);
	for(const string &file : files){
		bt_directory_entry entry=bt_stat(file.c_str());
		if(entry.valid){
			if(entry.type==FS_Directory){
				out << '[' << entry.filename << ']' << sep << "---" << endl;
			}else if(entry.type==FS_Device){
				out << '{' << entry.filename << '}' << sep << "---" << endl;
			}else{
				out << entry.filename << sep << entry.size << endl;
			}
		}
	}
}

void display_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
    ostream &output=*cmd.output;
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;
	}
    if(commandline[1] != "-") {
        vector<string> files = glob(commandline[1]);
        for (const string &file : files) {
            display_file(parse_path(file), output);
        }
    }else{
        string line;
        while(getline(*cmd.input, line)) output << line << endl;
    }
}

void ls_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
    ostream &output=*cmd.output;
	string path;
	if(commandline.size() < 2){
		path=get_cwd();
	}else{
		path=commandline[1];
	}
	stringstream ls;
	ls << "# name, size" << endl;
	list_files(path, ls, ',');
	display_table(ls.str(), output);
}

void cd_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
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

void path_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
	if(commandline.size() < 2){
		cout << get_cwd() << endl;
	}else{
		cout << parse_path(commandline[1]) << endl;
	}
}

void touch_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;
	}else{
		vector<string> files=glob(commandline[1]);
		for(const string &file : files){
			string path=parse_path(file);
			if(path.length()){
				FILE *fh=fopen(path.c_str(), "a");
				if(fh) fclose(fh);
				else cout << "Error opening file." << endl;
			}else cout << "Invalid path." << endl;
		}
	}
}

void echo_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
    ostream &output=*cmd.output;
	if(commandline.size() < 2 || (commandline[1]=="-f" && commandline.size() < 3)){
		cout << "Usage:" << endl;
		cout << commandline[0] << " [-f filename] text" << endl;
	}else{
		ostream *out=&output;
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

void mkdir_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
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

void del_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;
	}else{
		vector<string> files=glob(commandline[1]);
		for(const string &file : files){
			bt_filehandle fh=bt_fopen(parse_path(file).c_str(), FS_Read | FS_Delete);
			if(fh) bt_fclose(fh);
			else cout << "Could not delete " << file << endl;
		}
	}
}

void rmdir_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
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

void copy_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
	if(commandline.size() < 3){
		cout << "Usage:" << endl;
		cout << commandline[0] << " from to" << endl;
	}else{
		vector<string> from=glob(commandline[1]);
		string to=parse_path(commandline[2]);
		if(from.size()==1 && is_directory(parse_path(from[0]))){
			cout << "Cannot copy directory " << from[0] << endl;
			return;
		}
		if(!is_directory(to) && from.size() > 1){
			cout << "Cannot copy multiple files to non-directory target." << endl;
			return;
		}
		for(const string &file : from){
			bt_directory_entry ent = bt_stat(parse_path(file).c_str());
			if(is_directory(file)){
				cout << "Ignoring directory " << file << endl;
				continue;
			}
			string target=parse_path(to);
			if(is_directory(to)){
				string filename=path_file(file);
				target=parse_path(to + '/' + filename);
			}
			ifstream fromfile(file);
			ofstream tofile(target);
			if(!fromfile.is_open()){
				cout << "Could not open source file " << file << endl;
				return;
			}else if(!tofile.is_open()){
				cout << "Could not create target " << target << endl;
				return;
			}
			bt_filesize_t sofar = 0;
			while(true){
				if(ent.size > 10240){
					int progress = (100 * sofar) / ent.size;
					streampos outpos = cout.tellp();
					for(size_t i = 0; i < file.length() + 10; ++i){
						cout << " ";
					}
					cout.seekp(outpos);
					cout << file << " : " << progress << "%";
					cout.seekp(outpos);
				}
				char buffer[4096];
				streamsize bytes_read=fromfile.read(buffer, 4096).gcount();
				if(bytes_read){
					tofile.write(buffer, bytes_read);
				}else break;
				sofar+=bytes_read;
			}
			if(ent.size > 10240){
				streampos outpos = cout.tellp();
				for(size_t i = 0; i < file.length() + 10; ++i){
					cout << " ";
				}
				cout.seekp(outpos);
			}
		}
	}
}

void move_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
	if(commandline.size() < 3){
		cout << "Usage:" << endl;
		cout << commandline[0] << " from to" << endl;
	}else{
		copy_command(cmd);
		del_command(cmd);
	}
}

void ver_command(const command &cmd){
    ostream &output=*cmd.output;
	output << "BT/OS CMD" << endl;
	print_os_version(output);
}

void list_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
    ostream &output=*cmd.output;
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " pattern" << endl;
	}else{
		vector<string> matches=glob(commandline[1]);
		for(const string &s : matches){
			output << s << endl;
		}
	}
}

void setenv_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " name [value]" << endl;
	}else{
		string value="";
		if(commandline.size() == 3) value=commandline[2];
		bt_setenv(commandline[1].c_str(), value.c_str(), 0);
	}
}

void time_command(const command &cmd){
	vector<string> commandline=cmd.args;
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " command" << endl;
	}else{
		ostream &output=*cmd.output;
		commandline.erase(commandline.begin());
		command ncmd = cmd;
		ncmd.args = commandline;
		uint64_t start = bt_rtc_millis();
		run_command(ncmd);
		uint64_t end = bt_rtc_millis();
		output << "Time: " << (end - start) << "ms." << endl;
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
	{"glob", &list_command},
	{"setenv", &setenv_command},
	{"set", &setenv_command},
	{"time", &time_command},
};

bool run_builtin(const command &cmd){
    vector<string> commandline=cmd.args;
	const string command=to_lower(commandline[0]);
	if(builtin_commands.find(command)!=builtin_commands.end()){
		builtin_commands[command](cmd);
		return true;
     }
    return false;
}

bool run_program(const command &cmd) {
    vector<string> commandline=cmd.args;
    const string command = to_lower(commandline[0]);
    string path = parse_path(command);
    if (!ends_with(to_lower(path), ".elx")) path += ".elx";
    vector<string> possibles;
    if (command.find('/') == string::npos) {
        vector<string> paths = get_paths();
        for (const string &p : paths) {
            string possible = parse_path(p + "/" + command);
            if (possible.length()) {
                if (!ends_with(to_lower(possible), ".elx")) possible += ".elx";
                possibles.push_back(possible);
            }
        }
    } else {
        if (path.length()) possibles.push_back(path);
    }
    if (!possibles.size()) return false;
    for (const string &p : possibles) {
        bt_directory_entry ent = bt_stat(p.c_str());
        if (ent.valid && ent.type == FS_File) {
            vector<string> args=commandline;
            args.erase(args.begin());
            string std_in=get_env("STDIN");
            string std_out=get_env("STDOUT");
            set_env("STDIN", cmd.input_path);
            set_env("STDOUT", cmd.output_path);
			Process proc = Process::Spawn(p, args);
            set_env("STDIN", std_in);
            set_env("STDOUT", std_out);
            int ret = 0;
            if (proc.GetPID()) ret = proc.Wait();
			else cout << "Could not launch " << p << endl;
            if (ret == -1) cout << p << " crashed." << endl;
            return true;

        }
    }
	return false;
}

bool run_command(const command &cmd){
	if(!cmd.args.size()) return true;
	else if(cmd.args[0]=="exit") return false;
	else if(run_builtin(cmd)) return true;
	else if(run_program(cmd)) return true;
	cout << "Unknown command." << endl;
	return true;
}

command::command(){
    this->input=&cin;
    this->output=&cout;
    input_path=get_env("STDIN");
    output_path=get_env("STDOUT");
    redir_input=false;
    redir_output=false;
}

command::~command(){
}

void command::set_input(string path) {
    input_path=path;
    redir_input=true;
}

void command::set_output(string path) {
    output_path=path;
    redir_output=true;
}

void command::openio(){
    if(redir_input){
        input=new ifstream(input_path);
        input_ptr.reset(input);
    }
    if(redir_output){
        output=new ofstream(output_path, ios_base::app);
        output_ptr.reset(output);
    }
}

void command::closeio(){
    output->flush();
    input_ptr.reset();
    output_ptr.reset();
}

}
}
