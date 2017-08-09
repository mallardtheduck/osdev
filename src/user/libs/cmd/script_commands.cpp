#include <cmd/script_commands.hpp>
#include <cmd/utils.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include <stack>
#include <deque>
#include <cmath>
#include <cstdlib>

using namespace std;

namespace btos_api{
namespace cmd{

void echo_command(const command &cmd){
    const vector<string> &commandline=cmd.args;
    ostream &output=*cmd.output;
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
	ostream &out=*cmd.output;
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

}
}
