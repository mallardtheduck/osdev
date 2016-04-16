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


string get_env(const string &name){
	char value[128];
	string ret;
	size_t size=bt_getenv(name.c_str(), value, 128);
	ret=value;
	if(size>128){
		char *buf=new char[size];
		bt_getenv(name.c_str(), value, size);
		ret=buf;
	}
	if(size) return ret;
	else return "";
}

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

string mount_partition(const partition_info &part){
	bt_mount("hdd", part.path.c_str(), part.fs.c_str());
	return "hdd";
}

bool copy_files(const string &mountpoint){
	string sysdrive = get_env("SYSTEMDRIVE");
	string datapath = sysdrive + ":/btos.tar";
	string destpath = mountpoint + ":/";
	string cwd = get_env("CWD");
	bt_setenv("CWD", destpath.c_str(), 0);
	char *args[] = {(char*)"xvf", (char*)datapath.c_str()};
	string tarpath = sysdrive + ":/btos/cmd/tar.elx";
	bt_spawn(sysdrive.c_str(), 2, args);
	bt_setenv("CWD", cwd.c_str(), 0);
	return true;
}

void configure_install(const string &mountpoint, const partition_info &part){
	(void)mountpoint; (void)part;
}

bool install_grub(const string &mountpoint, const partition_info &part){
	(void)mountpoint; (void)part;
	return true;
}

void write_answers(const string &mountpoint, const partition_info &part, bool rootinstall){
	(void)mountpoint; (void)part; (void)rootinstall;
}

int main(){
    cout << "BT/OS Installer" << endl << endl;
	partition_info partition = select_partition();
	string mountpoint = mount_partition(partition);
	if(copy_files(mountpoint)){
		configure_install(mountpoint, partition);
		bool rootinstall = install_grub(mountpoint, partition);
		write_answers(mountpoint, partition, rootinstall);
	}
	
    return 0;
}