#include <cmd/scripting.hpp>
#include <cmd/commands.hpp>
#include <cmd/utils.hpp>

#include <streambuf>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <stack>

using namespace std;

namespace btos_api{
namespace cmd{
	
static const string Label = "label";
static const string Function = "function";
static const string Loop = "loop";
static const string End = "end";
static const string Local = "local";
static const string Call = "call";
static const string Goto = "goto";
static const string If = "if";
static const string Else = "else";

template<typename T> static unique_ptr<T> unique_copy(const T &v){
	return unique_ptr<T> { new T(v) };
}

static pair<string, vector<string>> ParseFunctionDef(const vector<string> line){
	string name;
	vector<string> params;
	if(line.size() > 1){
		name = to_lower(line[1]);
		for(size_t i = 2; i < line.size(); ++i) params.push_back(line[i]);
	}
	return {name, params};
}

static pair<string, vector<string>> ParseFunctionCall(const vector<string> line){
	string name;
	vector<string> args;
	if(line.size() > 1){
		name = to_lower(line[1]);
		for(size_t i = 2; i < line.size(); ++i) args.push_back(line[i]);
	}
	return {name, args};
}

static bool IsTruthy(const string &q){
	auto ql = to_lower(q);
	if(ql == "" || ql == "false" || ql == "no" || ql == "0") return false;
	else return true;
}

static bool IsStart(const string &block, const vector<string> &line){
	return (!line.empty() && to_lower(line[0]) == block);
}

static bool IsEnd(const string &block, const vector<string> &line){
	return (line.size() == 2 && to_lower(line[0]) == End && to_lower(line[1]) == block);
}

static bool IsExact(const string &block, const vector<string> &line){
	return (line.size() == 1 && to_lower(line[0]) == block);
}

string RunCMDCommand(const vector<string> &tokens){
	auto outputfile = tempfile();
	auto commands = getcommands(tokens, outputfile);
	for(auto c : commands) {
		c.openio();
		run_command(c);
		c.closeio();
	}
	ifstream t(outputfile);
	string ret((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	t.close();
	remove(outputfile.c_str());
	return ret;
}

ScriptFunction::ScriptFunction(const vector<vector<string>> &c, const vector<string> &p) : content(c), params(p)
{}
std::string ScriptFunction::Run(ScriptScope &parent, vector<string> args){
	ScriptScope scope {&parent};
	for(size_t i = 0; i < params.size(); ++i){
		if(args.size() > i){
			scope.AddVar(params[i], args[i]);
		}else break;
	}
	scope.Parse(content);
	return scope.Run();
}

string ScriptScope::RunLine(const vector<string> &line){
	if(!line.empty()){
		auto s = to_lower(line[0]);
		if(s == Call){
			auto c = ParseFunctionCall(line);
			auto fn = GetFunction(c.first);
			if(fn.first){
				return fn.second.Run(*this, c.second);
			}
		}
	}
	//TODO: Finish...
	return "";
}

ScriptScope::ScriptScope(ScriptScope *p) : parent(p)
{}

void ScriptScope::Parse(const vector<vector<string>> &clines){
	unique_ptr<pair<string, vector<string>>> pending_fn;
	vector<vector<string>> fn_lines;
	for(auto p : clines){
		if(!p.empty()){
			auto s = to_lower(p[0]);
			if(!pending_fn){
				if(s == Function){
					auto fn = ParseFunctionDef(p);
					if(fn.first != "") pending_fn = unique_copy(fn);
				}else if(s == Label){
					if(p.size() > 1){
						labels.insert({to_lower(p[1]), lines.size()});
					}
				}else{
					lines.push_back(p);
				}
			}else{
				if(IsEnd(Function , p)){
					functions.insert({pending_fn->first, {fn_lines, pending_fn->second}});
					pending_fn.reset();
					fn_lines.clear();
				}else{
					fn_lines.push_back(p);
				}
			}
		}
	}
}
	
void ScriptScope::Parse(const vector<string> &content){
	vector<vector<string>> lines;
	for(auto c : content){
		lines.push_back(parse_command(c));
	}
	Parse(lines);
}
string ScriptScope::Run(){
	stringstream output;
	stack<size_t> loopStack;
	function<bool(const vector<string>&)> resume;
	int resumeCounter = 0;
	for(size_t i = 0; i < lines.size(); ++i){
		auto &line = lines[i];
		if(resume){
			if(resume(line)) resume = nullptr;
			else continue;
		}
		if(!line.empty()){
			auto s = to_lower(line[0]);
			if(s == Goto){
				if(line.size() == 2){
					auto label = to_lower(line[1]);
					if(labels.find(label) != labels.end() && labels.at(label) < lines.size()) i = labels.at(label) - 1;
				}
			}else if(s == If){
				vector<string> rest;
				for(size_t j = 1; j < line.size(); ++j) rest.push_back(line[i]);
				auto result = RunLine(rest);
				if(!IsTruthy(result)){
					resumeCounter = 1;
					resume = [&](const vector<string> &l) -> bool{
						if(resumeCounter == 1 && IsExact(Else, l)) return true;
						else if(IsStart(If, l)) ++resumeCounter;
						else if(IsEnd(If, l)) --resumeCounter;
						if(resumeCounter) return false;
						return true;
					};
				}	
			}else if(s == Else){
				resumeCounter = 1;
				resume = [&](const vector<string> &l) -> bool{
					if(IsStart(If, l)) ++resumeCounter;
					else if(IsEnd(If, l)) --resumeCounter;
					if(resumeCounter) return false;
					return true;
				};
			}else if(s == Loop){
				vector<string> rest;
				for(size_t j = 1; j < line.size(); ++j) rest.push_back(line[i]);
				auto result = RunLine(rest);
				if(IsTruthy(result)){
					loopStack.push(i);
				}else{
					resumeCounter = 1;
					resume = [&](const vector<string> &l) -> bool{
						if(IsStart(Loop, l)) ++resumeCounter;
						else if(IsEnd(Loop, l)) --resumeCounter;
						if(resumeCounter) return false;
						return true;
					};
				}
			}else if(s == End){
				if(line.size() == 2){
					auto b = to_lower(line[1]);
					if(b == Function) break;
					else if(b == Loop){
						i = loopStack.top() - 1;
						loopStack.pop();
					}else if(b == If){
						//ignore
					}
				}
			}else{
				output << RunLine(line);
			}
		}
	}
	return output.str();
}
	
void ScriptScope::AddVar(const string &name, const string &value){
	if(value != "") locals.insert({name, value});
	else locals.erase(name);
}
string ScriptScope::GetVar(const string &name){
	if(locals.find(name) != locals.end()) return locals.at(name);
	else if(parent) return parent->GetVar(name);
	else return "";
}

pair<bool, ScriptFunction> ScriptScope::GetFunction(const string &name){
	if(functions.find(name) != functions.end()) return {true, functions.at(name)};
	else if(parent) return parent->GetFunction(name);
	else return {false, {}};
}

ScriptContext::ScriptContext(istream &is, const function<string(const vector<string>&)> run) 
	: ScriptContext([&]() -> vector<string>{
		vector<string> ret;
		while(!is.eof()){
			string line;
			getline(is, line);
			if(line != "") ret.push_back(line);
		}
		return ret;
	}(), run) {}
ScriptContext::ScriptContext(const vector<string> script, const function<string(const vector<string>&)> run) : runCommand(run){
	globalScope.Parse(script);
}
	
std::string ScriptContext::Run(const vector<string> args){
	stringstream argss;
	argss << "[";
	bool first = true;
	for(auto a : args){
		if(!first) argss << ",";
		first = false;
		argss << "\"" << a << "\"";
	}
	argss << "]";
	globalScope.AddVar("args", argss.str());
	return globalScope.Run();
}

}
}
