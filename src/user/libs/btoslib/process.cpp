#include <btos/process.hpp>
#include <sstream>

using namespace std;

namespace btos_api{
	
	Process Process::Spawn(const char *path, size_t argc, const char **argv){
		return Process(bt_spawn(path, argc, (char**)argv));
	}

	Process Process::Spawn(const std::string &path, std::vector<std::string> args){
		const char **argv = new const char*[args.size()];
		for(size_t i = 0; i < args.size(); ++i){
			argv[i] = args[i].c_str();
		}

		Process ret = Process::Spawn(path.c_str(), args.size(), argv);
		delete argv;
		return ret;
	}

	Process Process::Current(){
		return Process(bt_getpid());
	}

	Process::Process(bt_pid_t p) : pid(p) {}

	int Process::Wait() const{
		return bt_wait(pid);
	}

	bool Process::Kill(){
		return bt_kill(pid);
	}

	bt_priority Process::Prioritize(bt_priority priority){
		return bt_prioritize(pid, priority);
	}

	bt_pid_t Process::GetPID() const{
		return pid;
	}

	bt_proc_status::Enum Process::GetStatus() const{
		return bt_get_proc_status(pid);
	}

	pair<string, vector<string>> ParseCmd(const string &cmd){
		vector<string> tokens;
		stringstream current;
		bool quoted=false, escape=false, list=false;
		for(const char &c : cmd){
			if(!escape && !quoted && !list && isspace(c)){
				string cstr=current.str();
				if(cstr.length()) tokens.push_back(cstr);
				current.str("");
			}else if(!escape && !list && c=='"'){
				quoted=!quoted;
			}else if(!quoted && !list && c=='['){
				current << '[';
				list=true;
			}else if(!quoted && list && c==']'){
				current << ']';
				list=false;
			}else if(!escape && c=='\\'){
				escape=true;
			}else if(escape){
				if(c=='n') current << '\n';
				else current << c;
				escape=false;
			}else current << c;
		}
		if(current.str().length()) tokens.push_back(current.str());
		if(tokens.size()){
			string cmd = tokens[0];
			vector<string> args;
			if(tokens.size() > 1){
				for(size_t i = 1; i < tokens.size(); ++i){
					args.push_back(tokens[i]);
				}
			}
			return make_pair(cmd, args); 
		}else{
			return make_pair(string(), vector<string>());
		}
	}

}
