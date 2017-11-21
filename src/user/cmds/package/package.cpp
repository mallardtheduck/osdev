#include <vector>
#include <string>

#include "package.hpp"

using std::vector;
using std::string;

int main(int argc, char **argv){
    vector<string> args{argv, argv + argc};

    if(args[1] == "import" && args.size() == 4){
        ImportPackage(args[2], args[3]);
    }else if(args[1] == "refresh" && args.size() == 4){
        RefreshPackage(args[2], args[3]);
    }
}