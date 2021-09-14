#include "kernel.hpp"

class VisibleDeviceIterator;

class VisibleDeviceManager : public IVisibleDeviceManager{
private:
	friend class VisibleDeviceIterator;

	mutable ILock *lock = NewLock();
	map<string, IVisibleDevice*> devices;
public:
	void AddVisibleDevice(IVisibleDevice *device) override{
		auto hl = lock->LockExclusive();
		auto name = to_upper(device->GetName());
		int counter = 0;
		for(; devices.has_key(name + itoa(counter)); ++counter);
		auto finalName = name + itoa(counter);
		device->SetName(finalName.c_str());
		devices[finalName] = device;
	}

	IVisibleDevice *GetVisibleDevice(const char *name) override{
		auto hl = lock->LockExclusive();
		if(devices.has_key(name)) return devices[name];
		else return nullptr;
	}

	VisibleDeviceIteratorWrapper begin() const override;

	VisibleDeviceIteratorWrapper end() const override;
};

class VisibleDeviceIterator : public IVisibleDeviceIterator{
private:
	const VisibleDeviceManager &manager;
	string index;
public:
	VisibleDeviceIterator(const VisibleDeviceManager &m, string i) : manager(m), index(i) {}

	IVisibleDevice &Get() const override{
		auto hl = manager.lock->LockExclusive();
		return *manager.devices.get(index).second;
	}

	void Increment() override{
		if(index == "") return;
		auto hl = manager.lock->LockExclusive();
		bool found = false;
		for(auto &device : manager.devices){
			if(found){
				index = device.first;
				return;
			}
			if(device.first == index) found = true;
		}
		index = "";
	}

	void Decrement() override{
		auto hl = manager.lock->LockExclusive();
		if(index == ""){
			auto it = manager.devices.end();
			--it;
			index = it->first;
		}else{
			auto prev = manager.devices.begin()->first;
			for(auto &device : manager.devices){
				if(device.first == index){
					index = prev;
					return;
				}
				prev = device.first;
			}
		}
	}

	IVisibleDeviceIterator *Clone() const override{
		return new VisibleDeviceIterator(manager, index);
	}

	bool IsEqual(IVisibleDeviceIterator &o) const override{
		auto &other = static_cast<VisibleDeviceIterator&>(o);
		if(other.index == index) return true;
		else return false;
	}
};

VisibleDeviceIteratorWrapper VisibleDeviceManager::begin() const{
	return new VisibleDeviceIterator(*this, devices.begin()->first);
}

VisibleDeviceIteratorWrapper VisibleDeviceManager::end() const{
	return new VisibleDeviceIterator(*this, "");
}

StaticAlloc<VisibleDeviceManager> vdm;

IVisibleDeviceManager &GetVisibleDeviceManager(){
	return *vdm;
}

void Devices_Init(){
	vdm.Init();
}