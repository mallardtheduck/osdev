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
static const string Out = "out";
static const string Var = "var";
static const string Let = "let";
static const string Comment = "#";

template<typename T> static unique_ptr<T> unique_copy(const T &v){
	return unique_ptr<T> { new T(v) };
}

template<typename T> static vector<T> getrest(const vector<T> &in, size_t idx){
	vector<T> ret;
	for(size_t i = idx; i < in.size(); ++i) ret.push_back(in[i]);
	return ret;
}

static pair<string, vector<string>> ParseFunctionDef(const vector<string> line){
	string name;
	vector<string> params;
	if(line.size() > 1){
		name = to_lower(line[1]);
		params = getrest(line, 2);
	}
	return {name, params};
}

static pair<string, vector<string>> ParseFunctionCall(const vector<string> line){
	string name;
	vector<string> args;
	if(line.size() > 1){
		name = to_lower(line[1]);
		args = getrest(line, 2);
	}
	return {name, args};
}

static bool IsTruthy(const string &q){
	auto ql = to_lower(q);
	trim(ql);
	if(ql == "" || ql == "false" || ql == "no" || ql == "0"){
		return false;
	}else{
		return true;
	}
}

__attribute__((unused))
static void OutLine(const vector<string> &line, bool nl = true){
	bool first = true;
	for(auto &s : line){
		if(!first) cout << ", ";
		first = false;
		cout << '\'' << s << '\'';
	}
	if(nl) cout << endl;
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

string RunCMDCommand(const vector<string> &tokens, bool capture){
	string outputfile;
	vector<command> commands;
	if(capture){
		outputfile = tempfile();
		commands = getcommands(tokens, outputfile);
	}else{
		commands = getcommands(tokens);
	}
	for(auto c : commands) {
		c.openio();
		run_command(c);
		c.closeio();
	}
	if(capture){
		ifstream t(outputfile);
		string ret((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
		t.close();
		remove(outputfile.c_str());
		if(ends_with(ret, "\n")) ret.pop_back();
		trim(ret);
		return ret;
	}else{
		return "";
	}
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
	auto ret = scope.Run();
	if(ends_with(ret, "\n")) ret.pop_back();
	trim(ret);
	return ret;
}

string ScriptScope::RunLine(const vector<string> &line){
	if(!line.empty()){
		vector<string> interpolated;
		for(auto &l : line){
			auto li = Interpolate(l, [&](const string &v) -> string{
				if(starts_with(v, "(") && ends_with(v, ")")){
					string cmd = v.substr(1, v.length() - 2);
					return RunLine(parse_command(cmd));
				}else{
					return GetVar(v);
				}
			});
			interpolated.push_back(li);
		}
		if(context && context->IsDebugOutput()){
			cout << "Running: ";
			OutLine(interpolated);
		}
		auto s = to_lower(interpolated[0]);
		if(s == Call){
			auto c = ParseFunctionCall(interpolated);
			auto fn = GetFunction(c.first);
			if(fn.first){
				return fn.second.Run(*this, c.second);
			}
		}else if(s == Var){
			if(interpolated.size() == 3){
				auto name = interpolated[1];
				auto value = interpolated[2];
				AddVar(name, value);
			}else if(interpolated.size() == 2){
				auto name = interpolated[1];
				AddVar(name, "");
			}
		}else if(s == Let){
			if(interpolated.size() >= 3){
				auto name = interpolated[1];
				vector<string> rest = getrest(interpolated, 2);
				auto value = RunLine(rest);
				AddVar(name, value);
			}
		}else{
			bool capture = true;
			if(s == Out){
				capture = false;
				interpolated = getrest(interpolated, 1);
			}
			if(context) return context->RunCommand(interpolated, capture);
		}
	}
	return "";
}

ScriptScope::ScriptScope(ScriptContext *c) : context(c)
{}

ScriptScope::ScriptScope(ScriptScope *p) : parent(p), context(p->context)
{}

void ScriptScope::Parse(const vector<vector<string>> &clines){
	unique_ptr<pair<string, vector<string>>> pending_fn;
	vector<vector<string>> fn_lines;
	for(auto p : clines){
		if(!p.empty()){
			auto s = to_lower(p[0]);
			if(starts_with(p[0], Comment)) continue;
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
	bool ignoreLine = false;
	for(size_t i = 0; i < lines.size(); ++i){
		auto &line = lines[i];
		if(resume){
			if(resume(line)) resume = nullptr;
			else continue;
		}
		if(context && context->IsDebugOutput()){
			cout << "Processing: ";
			OutLine(line);
		}
		if(!line.empty()){
			auto s = to_lower(line[0]);
			if(s == Goto){
				if(line.size() == 2){
					auto label = to_lower(line[1]);
					if(labels.find(label) != labels.end() && labels.at(label) < lines.size()) i = labels.at(label) - 1;
				}
			}else if(s == If){
				vector<string> rest = getrest(line, 1);
				auto result = RunLine(rest);
				if(!IsTruthy(result)){
					resumeCounter = 1;
					resume = [&](const vector<string> &l) -> bool{
						if(resumeCounter == 1 && IsExact(Else, l)){
							ignoreLine = true;
							return true;
						}
						else if(IsStart(If, l)) ++resumeCounter;
						else if(IsEnd(If, l)) --resumeCounter;
						if(resumeCounter) return false;
						return true;
					};
				}	
			}else if(s == Else){
				if(!ignoreLine){
					resumeCounter = 1;
					resume = [&](const vector<string> &l) -> bool{
						if(IsStart(If, l)) ++resumeCounter;
						else if(IsEnd(If, l)) --resumeCounter;
						if(resumeCounter) return false;
						return true;
					};
				}
			}else if(s == Loop){
				vector<string> rest = getrest(line, 1);
				auto result = RunLine(rest);
				if(IsTruthy(result)){
					loopStack.push(i);
				}else{
					resumeCounter = 1;
					resume = [&](const vector<string> &l) -> bool{
						if(IsStart(Loop, l)) ++resumeCounter;
						else if(IsEnd(Loop, l)) --resumeCounter;
						if(resumeCounter) return false;
						ignoreLine = true;
						return true;
					};
				}
			}else if(s == End){
				if(line.size() == 2){
					auto b = to_lower(line[1]);
					if(b == Function) break;
					else if(b == Loop){
						if(!ignoreLine){
							i = loopStack.top() - 1;
							loopStack.pop();
						}
					}else if(b == If){
						//ignore
					}
				}
			}else{
				output << RunLine(line) << endl;
			}
			ignoreLine = false;
		}
	}
	return output.str();
}
	
void ScriptScope::AddVar(const string &name, const string &value){
	if(!SetVar(name, value)){
		if(value != "")	locals[name] = value;
		else locals.erase(name);
	}
}
bool ScriptScope::SetVar(const string &name, const string &value){
	if(locals.find(name) != locals.end()){
		locals[name] = value;
		return true;
	}else if(parent) return parent->SetVar(name, value);
	else return false;
}
string ScriptScope::GetVar(const string &name){
	if(locals.find(name) != locals.end()) return locals.at(name);
	else if(parent) return parent->GetVar(name);
	else if(context) return context->GetVar(name);
	else return "";
}

pair<bool, ScriptFunction> ScriptScope::GetFunction(const string &name){
	if(functions.find(name) != functions.end()) return {true, functions.at(name)};
	else if(parent) return parent->GetFunction(name);
	else return {false, {}};
}

ScriptContext::ScriptContext(istream &is, const function<string(const vector<string>&, bool)> run, const function<string(const string&)> get) 
	: ScriptContext([&]() -> vector<string>{
		vector<string> ret;
		while(!is.eof()){
			string line;
			getline(is, line);
			if(line != "") ret.push_back(line);
		}
		return ret;
	}(), run, get) {}
ScriptContext::ScriptContext(const vector<string> script, const function<string(const vector<string>&, bool)> run, const function<string(const string&)> get)
: runCommand(run), getVar(get), globalScope(this){
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

string ScriptContext::RunCommand(const vector<string> &args, bool capture){
	if(runCommand) return runCommand(args, capture);
	else return "";
}

string ScriptContext::GetVar(const string &name){
	if(getVar) return getVar(name);
	else return "";
}

void ScriptContext::SetDebugOutput(bool value){
	debugOutput = value;
}
bool ScriptContext::IsDebugOutput(){
	return debugOutput;
}

}
}
