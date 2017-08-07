#include <btos/processlist.hpp>
#include <btos/table.hpp>
#include <fstream>
#include <cstdlib>

using namespace std;

namespace btos_api{

	const string ProcessInfoFile = "INFO:/PROCS";

	ProcessList::ProcessList(){
		ifstream file{ProcessInfoFile};
		auto t = parsecsv(file);
		for(auto r : t.rows){
			bt_pid_t pid = strtoull(r["PID"].c_str(), nullptr, 10);
			string name = r["path"];
			size_t memory = strtoul(r["memory"].c_str(), nullptr, 10);
			bt_pid_t parent = strtoull(r["parent"].c_str(), nullptr, 10);

			info.push_back({name, pid, parent, memory});
		}
	}
	size_t ProcessList::Count() const{
		return info.size();
	}
	ProcessInfo ProcessList::operator[](size_t idx) const{
		return info[idx];
	}
	
	vector<ProcessInfo>::iterator ProcessList::begin(){
		return info.begin();
	}
	vector<ProcessInfo>::iterator ProcessList::end(){
		return info.end();
	}

	vector<ProcessInfo>::const_iterator ProcessList::begin() const{
		return info.begin();
	}
	vector<ProcessInfo>::const_iterator ProcessList::end() const{
		return info.end();
	}


}
