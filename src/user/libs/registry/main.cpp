#include <btos/registry.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;
using std::cout;
using std::endl;

namespace reg = btos_api::registry;

static bool yesno(const string &message, char def = '\0'){
	cout << message << endl;
		while(true){
		if(def == 'y'){
			cout << "(Y/n)";
		}else if(def == 'n'){
			cout << "(y/N)";
		}else{
			cout << "(y/n)";
		}
		string line;
		std::getline(std::cin, line);
		char c = line[0];
		if(c == 'y' || c == 'Y') return true;
		if(c == 'n' || c == 'N') return false;
		if(c == '\0' && def == 'y') return true;
		if(c == '\0' && def == 'n') return false;
	}
}

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
        }else if(args[1] == "bytype" && args.size() == 3){
            auto feats = reg::GetFeaturesByType(args[2]);
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
        }else if(args[1] == "assoc" && args.size() == 3){
            auto feat = reg::GetFeatureAssociation(args[2]);
            cout << feat << endl;
        }else if(args[1] == "assocpath" && args.size() == 3){
            auto path = reg::GetPathAssociation(args[2]);
            cout << path << endl;
        }else if(args[1] == "script" && args.size() >= 3){
            string path;
            if(args[2] != "-f"){
                path = args[2];
                string msg = "Run script '" + args[2] + "'?";
                if(!yesno(msg, 'n')) return 0;
            }else if(args.size() == 4){
                path = args[3];
            }
            std::ifstream ifs(path);
            if(!ifs){
                std::cerr << "Error opening file: " << path << endl;
                return 0;
            }
            vector<string> lines;
            string line;
            while(std::getline(ifs, line)) lines.push_back(line);
            auto res = reg::RunScript(lines);
            size_t lno = 0;
            for(auto r : res){
                ++lno;
                if(r) cout << "Error " << r << " on line " << lno << "." << endl;
            }
        }else{
            cout << "Unknown command: " << args[1] << endl;
        }
    }else{
        cout << "Usage: " << args[0] << " command options" << endl;
    }

    return 0;
}