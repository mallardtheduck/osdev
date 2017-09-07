#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <btos/table.hpp>

using namespace std;

namespace btos_api{
	
	void trim(string& str){
		string::size_type pos = str.find_last_not_of(' ');
		if(pos != string::npos) {
			str.erase(pos + 1);
			pos = str.find_first_not_of(' ');
			if(pos != string::npos) str.erase(0, pos);
		}
		else{
			str.erase(str.begin(), str.end());
		}
	}
	
	vector<string> splitline(const string &line, char delim){
		vector<string> ret;
		stringstream current;
		bool quote=false;
		bool escape=false;
		for(const char &c : line){
			if(!escape && c=='\"'){
				quote=!quote;
			}else if(!escape && c=='\\'){
				escape=true;
			}else if(!escape && !quote && c==delim){
				string curstr=current.str();
				trim(curstr);
				ret.push_back(curstr);
				current.str("");
			}else{
				if(escape) escape=false;
				current << c;
			}
		}
		string curstr=current.str();
		if(curstr.length()){
			trim(curstr);
			ret.push_back(curstr);
		}
		return ret;
	}
	
	vector<string> splitcsv(const string &line){
		return splitline(line, ',');
	}

	table parsecsv(istream &file){
		table ret;
		string header;
		getline(file, header);
		if(!header[0]=='#') return ret;
		header=header.substr(2);
		ret.headers=splitcsv(header);
		string line;
		while(getline(file, line)){
			vector<string> fields=splitcsv(line);
			if(fields.size() != ret.headers.size()) continue;
			table_row row;
			for(size_t i=0; i<fields.size(); ++i){
				row.insert(make_pair(ret.headers[i], fields[i]));
			}
			ret.rows.push_back(row);
		}
		return ret; 
	}

	table parsecsv(const string &str){
		stringstream ss{str};
		return parsecsv(ss);
	}
	
}