#include <btos/table.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::endl;

struct device{
	string id;
	string parent;
	string index;
	string devid;
	string type;
	string description;
	string driver;
	string node;
};

void print_device(const device &d, int level){
	string idt;
	for(int i = 0; i < level; ++i) idt += (char)179;
	cout << idt << (char)195 << "ID: " << d.id << endl;
	cout << idt << (char)179 << "Device ID: " << d.devid << endl;
	cout << idt << (char)179 << "Description: " << d.description << endl;
	cout << idt << (char)179 << "Type: " << d.type << " Driver: " << d.driver << " Node: " << d.node << endl;
}

void print_children(const vector<device> devices, const device &parent, int level){
	auto finder = [&](const device &x){return x.parent == parent.id;};
	auto it = std::find_if(devices.begin(), devices.end(), finder);
	while(it != devices.end()){
		print_device(*it, level);
		if(it->id != "0x0") print_children(devices, *it, level + 1);
		it = std::find_if(++it, devices.end(), finder);
	}
}

int main(){
	std::ifstream file("INFO:/PNPDEVICES");
	auto tbl = btos_api::parsecsv(file);
	vector<device> devices;
	for(auto &r : tbl.rows){
		device dev;
		dev.id = r["id"];
		dev.parent = r["parent"];
		dev.index = r["index"];
		dev.devid = r["devid"];
		dev.type = r["type"];
		dev.description = r["description"];
		dev.driver = r["driver"];
		dev.node = r["node"];
		devices.push_back(dev);
	}
	auto root = *std::find_if(devices.begin(), devices.end(), [](const device &x){return x.parent == "0x0";});
	print_device(root, 0);
	print_children(devices, root, 1);
}
