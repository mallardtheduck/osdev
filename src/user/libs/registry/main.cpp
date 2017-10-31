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
        }else if(args[1] == "features" && args.size() == 3){
            auto pkg = reg::GetPackageByName(args[2]);
            auto feats = reg::GetFeatures(pkg.id);
            for(auto &f : feats){
                cout << f << endl;
            }
        }else if(args[1] == "packageinfo" && args.size() == 3){
            auto pkg = reg::GetPackageByName(args[2]);
            cout << "ID: " << pkg.id << endl;
            cout << "Name: " << pkg.name << endl;
            cout << "Description: " << pkg.description << endl;
            cout << "Path: " << pkg.path << endl;
            cout << "Version: " << pkg.ver << endl;
        }else if(args[1] == "featureinfo" && args.size() == 3){
            auto feat = reg::GetFeatureByName(args[2]);
            cout << "ID: " << feat.id << endl;
            cout << "Package ID: " << feat.package << endl;
            cout << "Name: " << feat.name << endl;
            cout << "Description: " << feat.description << endl;
            cout << "Type: " << feat.type << endl;
            cout << "Path: " << feat.path << endl;
            cout << "File: " << feat.file << endl;
            cout << "Version: " << feat.ver << endl;
            cout << "Flags: " << feat.flags << endl;
        }else{
            cout << "Unknown command: " << args[1] << endl;
        }
    }else{
        cout << "Usage: " << args[0] << " command options" << endl;
    }

    return 0;
}