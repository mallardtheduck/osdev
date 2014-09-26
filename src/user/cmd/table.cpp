#include "cmd.hpp"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

typedef map<string, string> table_row;

struct table{
	vector<string> headers;
	vector<table_row> rows;
};

vector<string> splitcsv(const string &line){
	vector<string> ret;
	stringstream current;
	bool quote=false;
	bool escape=false;
	for(const char &c : line){
		if(!escape && c=='\"'){
			quote=!quote;
		}else if(!escape && c=='\\'){
			escape=true;
		}else if(!escape && !quote && c==','){
			string curstr=current.str();
			trim(curstr);
			ret.push_back(curstr+" ");
			current.str("");
		}else{
			if(escape) escape=false;
			current << c;
		}
	}
	string curstr=current.str();
	if(curstr.length()){
		trim(curstr);
		ret.push_back(curstr+" ");
	}
	return ret;
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

bool is_number(const std::string& s)
{
    return !s.empty() && find_if(s.begin(), s.end(),
    	[](char c) { return !isdigit(c) && c!='.' && c!='-' && c!=' '; }
    ) == s.end();
}

void print_padded(const string &value, size_t width, bool center){
	size_t length=value.length();
	if(length>width){
		cout << value.substr(0, width-1) << ' ';
	}else{
		size_t padding=width-length;
		if(center){
			size_t leftpad=padding/2;
			size_t rightpad=padding-leftpad;
			string lpad(leftpad, ' ');
			string rpad(rightpad, ' ');
			cout << lpad << value << rpad;
		}else{
			if(is_number(value)){
				string pad(padding-1, ' ');
				cout << pad << value << ' ';
			}else{
				string pad(padding, ' ');
				cout << value << pad;
			}
		}
	}
}

void display_table(table tbl, size_t width){
	map<string, size_t> maxlength;
	for(const string &s : tbl.headers){
		maxlength[s]=s.length();
	}
	for(const table_row &row : tbl.rows){
		for(const pair<string, string> &field : row){
			if(field.second.length()+1 > maxlength[field.first]) maxlength[field.first] = field.second.length()+1;
		}
	}
	size_t total=0;
	for(const pair<string, size_t> &l : maxlength){
		total+=l.second;
	}
	while(total > width - 1){
		size_t max=0;
		for(const pair<string, size_t> &l : maxlength){
			if(l.second >  max) max=l.second;
		}
		for(pair<const string, size_t> &l : maxlength){
			if(l.second==max){
				l.second--;
				total--;
			}
		}
	}
	for(const string &h : tbl.headers){
		print_padded(h, maxlength[h], true);
	}
	cout << endl;
	for(const table_row &row : tbl.rows){
		for(const string &h : tbl.headers){
			print_padded(row.at(h), maxlength[h], false);
		}
		cout << endl;
	}
}

void table_command(const vector<string> &commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;
	}else{
		vector<string> files=glob(commandline[1]);
		for(const string &file : files){
			ifstream in(file);
			if(in.is_open()){
				table tbl=parsecsv(in);
				if(tbl.rows.size()){
					display_table(tbl, 80);
				}
			}
		}
	}
}

void display_table(const string &input){
	stringstream in(input);
	table tbl=parsecsv(in);
	if(tbl.rows.size()){
		display_table(tbl, 80);
	}
}
