#ifndef _PROCESS_HPP
#define _PROCESS_HPP

#include <btos.h>
#include <vector>
#include <string>

namespace btos_api{

	class Process{
	private:
		bt_pid_t pid;

		Process() = delete;
	public:
		static Process Spawn(const char *path, size_t argc = 0, const char **argv = nullptr);
		static Process Spawn(const std::string &path, std::vector<std::string> args = std::vector<std::string>());
		static Process Current();

		Process(bt_pid_t p);
		int Wait() const;
		bool Kill();
		bt_priority Prioritize(bt_priority priority);
		bt_pid_t GetPID() const;
	};

}

#endif
