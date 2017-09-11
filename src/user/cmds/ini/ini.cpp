#include <btos/ini.hpp>
#include <iostream>
#include <string>
#include <vector>

using std::string; 
using std::vector;
using std::cout;
using std::endl;

int main(int argc, char **argv){
    vector<string> args{argv + 1, argv + argc};
    if(args.size() < 4) return 0;

    if(args[0] == "get"){
        auto section = args[1];
        auto value = args[2];
        auto file = args[3];

        auto ini = btos_api::ReadIniFile(file);
        if(ini.find(section) != ini.end() && ini[section].find(value) != ini[section].end()){
            cout << ini[section][value] << endl;
        }
    }
    return 0;
}