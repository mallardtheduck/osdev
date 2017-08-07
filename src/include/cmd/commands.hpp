#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP

#include <string>
#include <memory>
#include <iostream>
#include <vector>

namespace btos_api{
namespace cmd{

class command{
private:
    std::shared_ptr<std::istream> input_ptr;
    std::shared_ptr<std::ostream> output_ptr;
    bool redir_input, redir_output;
public:
    std::vector<std::string> args;
    std::istream *input;
    std::ostream *output;
    std::string input_path;
    std::string output_path;

    void set_input(std::string path);
    void set_output(std::string path);
    void openio();
    void closeio();

    command();
    ~command();
};
std::vector<command> getcommands(std::vector<std::string> parsed);
bool run_command(const command &cmd);
void table_command(const command &cmd);
void display_table(const std::string &input, std::ostream &output=std::cout);
void display_file(const std::string &path, std::ostream &output=std::cout);

}
}

#endif
