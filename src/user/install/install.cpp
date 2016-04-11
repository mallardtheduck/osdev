#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <limits>
#include <parted/parted.h>
#include <btos.h>

using namespace std;

string human_size(uint64_t size){
	stringstream ss;
	if(size < 1024){
		ss << size << " Bytes";
	}else if(size < 1048576){
		ss << size / 1024 << " KB";
	}else if(size < 1073741824){
		ss << size / 1048576 << " MB";
	}else if(size < 1099511627776){
		ss << size / 1073741824 << " GB";
	}else{
		ss << size / 1099511627776 << " TB";
	}
	return ss.str();
}

struct partition_info{
	string path;
	string devicepath;
	string fs;
};

bool yesno(string message, char def = '\0'){
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
		getline(cin, line);
		char c = line[0];
		if(c == 'y' || c == 'Y') return true;
		if(c == 'n' || c == 'N') return false;
		if(c == '\n' && def == 'y') return true;
		if(c == '\n' && def == 'y') return false;
	}
}

partition_info select_partition(){
	map<int, partition_info> selectmap;
	int counter = 0;
	cout << "Please select a partition to install to:" << endl;
	PedDevice *device = NULL;
	ped_device_probe_all();
	while((device = ped_device_get_next(device))){
		cout << device->path << ":" << endl;
		PedDiskType *type = ped_disk_probe(device);
		if(string(type->name) == "msdos"){
			PedDisk *disk = ped_disk_new(device);
			PedPartition *part = ped_disk_next_partition(disk, NULL);
			while(part){
				if(part->num > 0){
					uint64_t size = part->geom.length * device->sector_size;
					stringstream devstream;
					devstream << device->path << "P" << part->num - 1;
					partition_info info;
					info.path = devstream.str();
					info.devicepath = device->path;
					info.fs = ((part->fs_type) ? part->fs_type->name : "unformatted");
					int index = ++counter;
					selectmap[index] = info;
					cout << index << ": " << devstream.str() << ": "<< human_size(size) << " " << ((part->fs_type) ? part->fs_type->name : "unformatted") << endl;
				}
				part = ped_disk_next_partition(disk, part);
			}
		}else{
			cout << "Missing or incompatible partition table." << endl;
		}
	}
	cout <<  endl;
	partition_info ret;
	cout << "Select a partition by number or 'q' to quit (use 'parted' to create/modify paritions)." << endl;
	while(true){
		string line;
		getline(cin, line);
		if(line[0] == 'q') exit(0);
		stringstream ss(line);
		int partno;
		ss >> partno;
		if(partno > 0){
			try{
				ret = selectmap.at(partno);
				break;
			}catch(out_of_range){}
		}
	}
	if(ret.fs != "fat16" && ret.fs != "fat32"){
		if(yesno("This partition does not have a compatible filesystem. Format it? (This WILL destroy all data in the partition.)", 'n')){
			bt_format("FAT", ret.path.c_str(), NULL);
		}else{
			exit(0);
		}
	}
	return ret;
}

int main(){
    cout << "BT/OS Installer" << endl << endl;
	partition_info partition = select_partition();
    return 0;
}