#ifndef MODULE_DEVICES_HPP
#define MODULE_DEVICES_HPP

#include <cstddef>
#include <cstdint>
#include <util/noncopyable.hpp>
#include <btos/fs_interface.h>

class IVisibleDeviceInstance : private nonmovable{
public:
	virtual size_t Read(size_t bytes, char *buffer) = 0;
	virtual size_t Write(size_t bytes, const char *buffer) = 0;

	virtual bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) = 0;

	virtual int IOCtl(int fn, size_t bytes, char *buffer) = 0;

	virtual int GetType() = 0;
	virtual const char *GetDescription() = 0;

	virtual bool Close() = 0;

	virtual ~IVisibleDeviceInstance() {}
};

class IVisibleDevice : private nonmovable{
public:
	virtual IVisibleDeviceInstance *Open() = 0;
	virtual int GetType() = 0;
	virtual const char *GetDescription() = 0;
	virtual const char *GetName() = 0;
	virtual void SetName(const char *name) = 0;

	virtual ~IVisibleDevice() {}
};

class IVisibleDeviceIterator : private nonmovable{
public:
	virtual IVisibleDevice &Get() const = 0;
	virtual void Increment() = 0;
	virtual void Decrement() = 0;
	virtual IVisibleDeviceIterator *Clone() const = 0;

	virtual bool IsEqual(IVisibleDeviceIterator &other) const = 0;

	virtual ~IVisibleDeviceIterator() {}
};

class VisibleDeviceIteratorWrapper{
private:
	IVisibleDeviceIterator *it;
public:
	VisibleDeviceIteratorWrapper(IVisibleDeviceIterator *i) : it(i) {}
	VisibleDeviceIteratorWrapper(const VisibleDeviceIteratorWrapper &other) : it(other.it->Clone()) {}
	VisibleDeviceIteratorWrapper(VisibleDeviceIteratorWrapper &&other) : it(other.it){
		other.it = nullptr;
	}

	virtual VisibleDeviceIteratorWrapper &operator=(const VisibleDeviceIteratorWrapper &other){
		if(&other != this){
			delete it;
			it = other.it->Clone();
		}
		return *this;
	}

	virtual VisibleDeviceIteratorWrapper &operator=(VisibleDeviceIteratorWrapper &&other){
		if(&other != this){
			delete it;
			it = other.it;
			other.it = nullptr;
		}
		return *this;
	}

	IVisibleDevice &operator*() const{
		return it->Get();
	}

	IVisibleDevice *operator->() const{
		return &it->Get();
	}

	operator IVisibleDevice*(){
		return &it->Get();
	}

	VisibleDeviceIteratorWrapper &operator++(){
		it->Increment();
		return *this;
	}

	VisibleDeviceIteratorWrapper operator++(int){
		auto ret = *this;
		it->Increment();
		return ret;
	}

	VisibleDeviceIteratorWrapper &operator--(){
		it->Decrement();
		return *this;
	}

	VisibleDeviceIteratorWrapper operator--(int){
		auto ret = *this;
		it->Decrement();
		return ret;
	}

	bool operator==(const VisibleDeviceIteratorWrapper &o) const{
		return it->IsEqual(*o.it);
	}

	bool operator!=(const VisibleDeviceIteratorWrapper &o) const{
		return !(*this == o);
	}

	~VisibleDeviceIteratorWrapper(){
		if(it) delete it;
	}
};

class IVisibleDeviceManager : private nonmovable{
public:
	virtual void AddVisibleDevice(IVisibleDevice *device) = 0;
	virtual IVisibleDevice *GetVisibleDevice(const char *name) = 0;

	virtual VisibleDeviceIteratorWrapper begin() const = 0;
	virtual VisibleDeviceIteratorWrapper end() const = 0;

	virtual ~IVisibleDeviceManager() {}
};

#endif