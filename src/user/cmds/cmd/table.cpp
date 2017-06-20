#include "cmd.hpp"
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <btos/table.hpp>

using namespace std;

bool is_number(const std::string& s)
{
    return !s.empty() && find_if(s.begin(), s.end(),
    	[](char c) { return !isdigit(c) && c!='.' && c!='-' && c!=' '; }
    ) == s.end();
}

void print_padded(const string &value, size_t width, bool center, ostream &output=cout){
	size_t length=value.length();
	if(length>width){
        output << value.substr(0, width-1) << ' ';
	}else{
		size_t padding=width-length;
		if(center){
			size_t leftpad=padding/2;
			size_t rightpad=padding-leftpad;
			string lpad(leftpad, ' ');
			string rpad(rightpad, ' ');
            output << lpad << value << rpad;
		}else{
			if(is_number(value)){
				string pad(padding-1, ' ');
                output << pad << value << ' ';
			}else{
				string pad(padding, ' ');
                output << value << pad;
			}
		}
	}
}

void display_table(table tbl, size_t width, ostream &output=cout){
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
		print_padded(h, maxlength[h], true, output);
	}
    output << endl;
	for(const table_row &row : tbl.rows){
		for(const string &h : tbl.headers){
			print_padded(row.at(h), maxlength[h], false, output);
		}
        output << endl;
	}
}

void table_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
    ostream &output=*cmd.output;
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
					display_table(tbl, 80, output);
				}
			}
		}
	}
}

void display_table(const string &input, ostream &output){
	stringstream in(input);
	table tbl=parsecsv(in);
	if(tbl.rows.size()){
		display_table(tbl, 80, output);
	}
}
