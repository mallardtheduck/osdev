#include <btos/process.hpp>

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

}
