#include <cmd/script_commands.hpp>
#include <cmd/utils.hpp>
#include <btos/table.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <deque>
#include <cmath>
#include <cstdlib>

namespace btos_api{
namespace cmd{

using std::vector;
using std::ostream;
using std::string;
using std::cout;
using std::endl;
using std::deque;
using std::stack;
using std::find;

void echo_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
    ostream &output=cmd.OutputStream();
	if(commandline.size() < 2 || (commandline[1]=="-f" && commandline.size() < 3)){
		cout << "Usage:" << endl;
		cout << commandline[0] << " [-f filename] text" << endl;
	}else{
		ostream *out=&output;
		bool skip = true;
		bool first = true;
		for(const string &s : commandline){
			if(skip){
				skip = false;
				continue;
			}
			if(!first){
				*out << ' ';
				first = false;
			}
			*out << s;
		}
		*out << endl;
	}
}

template<typename T> static size_t get_index(const vector<T> &v, const T &a){
	for(size_t i = 0; i < v.size(); ++i) if(v[i] == a) return i;
	return -1;
}

void int_command(const command &cmd){
	ostream &out=cmd.OutputStream();
	vector<string> ops = { "^", "/", "%", "*", "+", "-", "gt", "lt", "==", "=", "!=", "and", "or" };
	deque<string> output;
	stack<string> opstack;
	bool first = true;
	for(auto &a : cmd.args){
		auto t = to_lower(a);
		if(first){
			first = false;
			continue;
		}
		if(is_integer(t)){
			output.push_back(t);
		}else if(get_index(ops, t) != (size_t)-1){
			if(!opstack.empty()){
				while(get_index(ops, opstack.top()) <= get_index(ops, t)){
					output.push_back(opstack.top());
					opstack.pop();
					if(opstack.empty()) break;
				}
			}
			opstack.push(t);
		}else if(t == "("){
			opstack.push(t);
		}else if(t == ")"){
			if(!opstack.empty()){
				while(opstack.top() != "("){
					output.push_back(opstack.top());
					opstack.pop();
					if(opstack.empty()){
						cout << "Unmatched brackets." << endl;
						return;
					}
				}
				opstack.pop();
			}else{
				cout << "Unmatched brackets." << endl;
				return;
			}
		}else{
			cout << "Unknown token: " << t << endl;;
			return;
		}
	}
	while(!opstack.empty()){
		if(opstack.top() == "("){
			cout << "Unmatched brackets." << endl;
			return;
		}
		output.push_back(opstack.top());
		opstack.pop();
	}

	stack<int> evalstack;
	while(!output.empty()){
		auto &t = output.front();
		if(is_integer(t)){
			evalstack.push(strtol(t.c_str(), NULL, 10));
		}else{
			if(evalstack.size() < 2){
				cout << "Syntax error." << endl;
				return;
			}
			int a = evalstack.top();
			evalstack.pop();
			int b = evalstack.top();
			evalstack.pop();
			int r = 0;
			if(t == "^"){
				r = pow(b, a);
			}else if(t == "/"){
				r = b / a;
			}else if(t == "%"){
				r = b % a;
			}else if(t == "*"){
				r = b * a;
			}else if(t == "+"){
				r = b + a;
			}else if(t == "-"){
				r = b - a;
			}else if (t == "gt"){
				if(b > a) r = 1;
				else r = 0;
			}else if (t == "lt"){
				if(b < a) r = 1;
				else r = 0;
			}else if (t == "==" || t == "="){
				if(b == a) r = 1;
				else r = 0;
			}else if (t == "!="){
				if(b != a) r = 1;
				else r = 0;
			}else if(t == "and"){
				if(b && a) r = 1;
				else r = 0;
			}else if(t == "or"){
				if(b || a) r = 1;
				else r = 0;
			}
			evalstack.push(r);
		}
		output.pop_front();
	}
	if(evalstack.size() != 1){
		cout << "Syntax error." << endl;
		return;
	}
	out << evalstack.top() << endl;
}

void str_command(const command &cmd){
	ostream &out=cmd.OutputStream();
	if(cmd.args.size() < 3) return;
	auto req = to_lower(cmd.args[1]);
	
	if(req == "len"){
		out << cmd.args[2].length() << endl;
	}else if(req == "eq"){
		if(cmd.args.size() < 4) return;
		int r = (cmd.args[2] == cmd.args[3])? 1 : 0;
		out << r << endl;
	}else if(req == "find"){
		if(cmd.args.size() < 4) return;
		auto r = cmd.args[3].find(cmd.args[2]);
		if(r == string::npos) out << -1 << endl;
		else out << r << endl;
	}else if(req == "sub"){
		if(cmd.args.size() < 5) return;
		auto posstr = cmd.args[2];
		auto countstr = cmd.args[3];
		auto source = cmd.args[4];
		if(!is_integer(posstr) || !is_integer(countstr)) return;
		size_t pos = strtoul(posstr.c_str(), NULL, 10);
		size_t count = strtoul(countstr.c_str(), NULL, 10);
		if(count == 0) count = string::npos;
		if(pos > source.length()) return;
		out << source.substr(pos, count) << endl;
	}
}

static vector<string> parse_array(const string &str){
	vector<string> ret;	
	if(str.front()=='[' && str.back()==']'){
		string cut=str.substr(1, str.length()-2);
		bool inQuotes = false;
		bool justQuote = false;
		string cur;
		for(const auto c : cut){
			if(c == '"'){
				inQuotes = !inQuotes;
				if(justQuote){
					cur += c;
					justQuote = false;
				}else{
					justQuote = true;
				}
				continue;
			}else justQuote = false;
			
			if(inQuotes || c != ',') cur += c;
			else{
				trim(cur);
				ret.push_back(cur);
				cur = "";
			}
		}
		trim(cur);
		if(!cur.empty()) ret.push_back(cur);
	}
	return ret;
}

static void deparse_array(const vector<string> &arr, ostream &out){
	out << "[";
	bool first = true;
	for(const auto &a : arr){
		if(!first) out << ",";
		first = false;
		auto e = replace(a, "\"", "\"\"");
		out << '"' << e << '"';
	}
	out << "]";
}

void arr_command(const command &cmd){
	ostream &out=cmd.OutputStream();
	if(cmd.args.size() < 3) return;
	auto req = to_lower(cmd.args[1]);

	if(req == "size"){
		out << parse_array(cmd.args[2]).size() << endl;
	}else if(req == "get"){
		if(cmd.args.size() < 4) return;
		auto idxstr = cmd.args[2];
		auto array = parse_array(cmd.args[3]);
		if(!is_integer(idxstr)) return;
		size_t idx = strtoul(idxstr.c_str(), NULL, 10);
		if(idx >= array.size()) return;
		out << array[idx] << endl;
	}else if(req == "add" || req == "push"){
		if(cmd.args.size() < 4) return;
		auto newval = cmd.args[2];
		auto array = parse_array(cmd.args[3]);
		array.push_back(newval);
		deparse_array(array, out);
		out << endl;
	}else if(req == "set"){
		if(cmd.args.size() < 5) return;
		auto idxstr = cmd.args[2];
		auto newval = cmd.args[3];
		auto array = parse_array(cmd.args[4]);
		if(!is_integer(idxstr)) return;
		size_t idx = strtoul(idxstr.c_str(), NULL, 10);
		if(idx >= array.size()) array.resize(idx + 1);
		array[idx] = newval;
		deparse_array(array, out);
		out << endl;
	}else if(req == "pop"){
		auto array = parse_array(cmd.args[2]);
		if(array.empty()) return;
		array.pop_back();
		deparse_array(array, out);
		out << endl;
	}else if(req == "back"){
		auto array = parse_array(cmd.args[2]);
		if(array.empty()) return;
		out << array.back() << endl;
	}
}

void tab_command(const command &cmd){
	ostream &out=cmd.OutputStream();
	if(cmd.args.size() < 3) return;
	auto req = to_lower(cmd.args[1]);
	
	if(req == "rows"){
		auto tbl = parsecsv(cmd.args[2]);
		out << tbl.rows.size() << endl;
	}else if(req == "head"){
		auto tbl = parsecsv(cmd.args[2]);
		deparse_array(tbl.headers, out);
		out << endl;
	}else if(req == "row"){
		if(cmd.args.size() < 4) return;
		auto rowstr = cmd.args[2];
		if(!is_integer(rowstr)) return;
		size_t rowno = strtoul(rowstr.c_str(), nullptr, 10);
		auto tbl = parsecsv(cmd.args[3]);
		if(rowno >= tbl.rows.size()) return;
		vector<string> rowvals;
		for(const auto &cell : tbl.rows[rowno]) rowvals.push_back(cell.second);
		deparse_array(rowvals, out);
		out << endl;
	}else if(req == "cell"){
		if(cmd.args.size() < 5){
			auto rowstr = cmd.args[2];
			auto colstr = cmd.args[3];
			if(!is_integer(rowstr)) return;
			auto tbl = parsecsv(cmd.args[4]);
			size_t row = strtoul(rowstr.c_str(), nullptr, 10);
			if(row >= tbl.rows.size()) return;
			if(tbl.rows[row].find(colstr) == tbl.rows[row].end()) return;
			out << tbl.rows[row][colstr] << endl;
		}
	}
}

}
}
