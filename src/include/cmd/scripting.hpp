#ifndef _SCRIPTING_HPP
#define _SCRIPTING_HPP

#include <string>
#include <map>
#include <vector>
#include <functional>
#include <iostream>
#include <utility>
#include <btos/envvars.hpp>

namespace btos_api{
namespace cmd{

class ScriptScope;
class ScriptContext;

std::string RunCMDCommand(const std::vector<std::string> &tokens, bool capture);

class ScriptFunction{
private:
	std::vector<std::vector<std::string>> content;
	std::vector<std::string> params;

public:
	ScriptFunction() = default;
	ScriptFunction(const std::vector<std::vector<std::string>> &content, const std::vector<std::string> &params);
	std::string Run(ScriptScope &parent, std::vector<std::string> args);
};

class ScriptScope{
private:
	std::vector<std::vector<std::string>> lines;
	std::map<std::string, ScriptFunction> functions;
	std::map<std::string, size_t> labels;
	std::map<std::string, std::string> locals;
	
	ScriptScope *parent = nullptr;
	ScriptContext *context = nullptr;
	std::string RunLine(const std::vector<std::string> &line);
public:
	ScriptScope(ScriptContext *c);
	ScriptScope(ScriptScope *p);
	
	void Parse(const std::vector<std::string> &content);
	void Parse(const std::vector<std::vector<std::string>> &lines);
	std::string Run();
	
	void AddVar(const std::string &name, const std::string &value);
	std::string GetVar(const std::string &name);
	std::pair<bool, ScriptFunction> GetFunction(const std::string &name);
};

class ScriptContext{
private:
	std::function<std::string(const std::vector<std::string>&, bool)> runCommand;
	std::function<std::string(const std::string&)> getVar;

	ScriptScope globalScope;
public:
	ScriptContext(std::istream &is, const std::function<std::string(const std::vector<std::string>&, bool)> run = &RunCMDCommand, std::function<std::string(const std::string&)> = &GetEnv);
	ScriptContext(const std::vector<std::string> script, const std::function<std::string(const std::vector<std::string>&, bool)> run = &RunCMDCommand, std::function<std::string(const std::string&)> = &GetEnv);
	
	std::string Run(const std::vector<std::string> args);
	std::string RunCommand(const std::vector<std::string> &args, bool);
	std::string GetVar(const std::string &name);
};
	
}
}

#endif
