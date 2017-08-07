#ifndef _PROCESSLIST_HPP
#define _PROCESSLIST_HPP

#include "process.hpp"
#include <string>
#include <vector>

namespace btos_api{

	class ProcessInfo{
	private:
		std::string name;
		bt_pid_t pid;
		bt_pid_t parent;
		size_t memory;

		ProcessInfo(std::string n, bt_pid_t p, bt_pid_t pa, size_t m) : name(n), pid(p), parent(pa), memory(m) {}

		friend class ProcessList;
	public:
		ProcessInfo(const ProcessInfo&) = default;

		std::string Name(){
			return name;
		}
		bt_pid_t PID(){
			return pid;
		}
		bt_pid_t Parent(){
			return parent;
		}
		size_t Memory(){
			return memory;
		}

		Process GetProcess(){
			return pid;
		}
	};

	class ProcessList{
	private:
		std::vector<ProcessInfo> info;
	public:
		ProcessList();
		size_t Count() const;
		ProcessInfo operator[](size_t idx) const;
		
		std::vector<ProcessInfo>::iterator begin();
		std::vector<ProcessInfo>::iterator end();

		std::vector<ProcessInfo>::const_iterator begin() const;
		std::vector<ProcessInfo>::const_iterator end() const;
	};

}

#endif
