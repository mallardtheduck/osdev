#include <btos/registry.hpp>
#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

namespace reg = btos_api::registry;

int main(int argc, char **argv){
    vector<string> args(argv, argv + argc);

    if(args.size() > 1){
        if(args[1] == "packages"){
            auto pkgs = reg::GetAllPackages();
            for(auto &p : pkgs){
                cout << p << endl;
            }
        }else{
            cout << "Unknown command: " << args[1] << endl;
        }
    }else{
        cout << "Usage: " << args[0] << " command options" << endl;
    }

    return 0;
}