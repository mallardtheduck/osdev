#ifndef _CMD_HPP
#define _CMD_HPP
#include "../../include/btos_stubs.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

void print_os_version();
std::string get_env(const std::string &name);
std::string get_env(const std::string &name, const std::string &def_value);
void set_env(const std::string &name, const std::string &value);
std::string get_prompt();
std::string get_cwd();
void set_cwd(const std::string &value);
std::string prompt_string();
std::string get_input();
void display_file(const std::string &path, std::ostream &output=std::cout);
std::vector<std::string> parse_input(const std::string &input);
std::string parse_path(std::string path);
std::string to_lower(const std::string &str);
bool is_directory(const std::string &path);
std::string path_file(const std::string &path);
std::vector<std::string> split(const std::string &str, char delim);
void trim(std::string& str);
void display_table(const std::string &input, std::ostream &output=std::cout);
std::string path_path(const std::string &fullpath);
std::vector<std::string> glob(const std::string &str);
bool is_dir(const std::string &path);
std::vector<std::string> get_paths();
bool ends_with(const std::string &str, const std::string &end);
std::string tempfile();

class command{
private:
    std::shared_ptr<std::istream> input_ptr;
    std::shared_ptr<std::ostream> output_ptr;
public:
    std::vector<std::string> args;
    std::istream *input;
    std::ostream *output;
    std::string input_path;
    std::string output_path;

    void set_input(std::istream *i, std::string path);
    void set_output(std::ostream *o, std::string path);
    void close();

    command();
    ~command();
};
std::vector<command> getcommands(std::vector<std::string> parsed);
bool run_command(const command &cmd);
void table_command(const command &cmd);

#endif
