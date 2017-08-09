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
private:
    mutable std::shared_ptr<std::istream> input_ptr;
    mutable std::shared_ptr<std::ostream> output_ptr;
    bool redir_input = false;
    bool redir_output = false;
public:
    std::vector<std::string> args;
    mutable std::istream *input;
    mutable std::ostream *output;
    std::string input_path;
    std::string output_path;

    void set_input(std::string path);
    void set_output(std::string path);
    void openio() const;
    void closeio() const;

    command(const std::string &default_input, const std::string &default_output);
    ~command();
};
std::vector<command> getcommands(const std::vector<std::string> &parsed, const std::string &default_output = "", const std::string &default_input = "");
bool run_command(const command &cmd);
void table_command(const command &cmd);
void display_table(const std::string &input, std::ostream &output=std::cout);
void display_file(const std::string &path, std::ostream &output=std::cout);

}
}

#endif
