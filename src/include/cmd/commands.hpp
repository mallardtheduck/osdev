#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <btos/envvars.hpp>

namespace btos_api{
namespace cmd{

class command{
public:
	enum class IOMode{
		Standard,
		Path,
		Temp
	};

private:
	IOMode input_mode = IOMode::Standard;
	IOMode output_mode = IOMode::Standard;
	
    mutable std::shared_ptr<std::istream> input_ptr;
    mutable std::shared_ptr<std::ostream> output_ptr;

    mutable std::istream *input = nullptr;
    mutable std::ostream *output = nullptr;
    mutable std::string input_path;
    mutable std::string output_path;
public:
    std::vector<std::string> args;
	
	std::istream &InputStream() const;
	std::ostream &OutputStream() const;
    void CloseStreams() const;

	std::string InputPath() const;
	std::string OutputPath() const;

    void SetInputPath(const std::string &path);
	void SetInputTemp();
    void SetOutputPath(const std::string &path);
	void SetOutputTemp();

	IOMode GetInputMode();
	IOMode GetOutputMode();

    command(const std::vector<std::string> &tokens);
    ~command();
};
std::vector<command> getcommands(const std::vector<std::string> &parsed, const std::string &default_output = "", const std::string &default_input = "");
bool run_command(const command &cmd);
void table_command(const command &cmd);
void display_table(const std::string &input, std::ostream &output=std::cout);
void display_file(const std::string &path, std::ostream &output=std::cout);
void list_files(std::string path, std::ostream &out=std::cout, char sep='\t');

void display_command(const command &cmd);
void ls_command(const command &cmd);
void cd_command(const command &cmd);
void path_command(const command &cmd);
void touch_command(const command &cmd);
void mkdir_command(const command &cmd);
void del_command(const command &cmd);
void rmdir_command(const command &cmd);
void copy_command(const command &cmd);
void move_command(const command &cmd);
void ver_command(const command &cmd);
void list_command(const command &cmd);
void setenv_command(const command &cmd);
void time_command(const command &cmd);

bool run_builtin(const command &cmd);
bool run_program(const command &cmd);

}
}

#endif
