#include "virt_handles.hpp"
#include <unistd.h>
#include <cstring>
#include <sys/errno.h>

//#include <util/tinyformat.hpp>

struct MemData{
	const char *data;
	size_t size;
	
	size_t pos;
};

int Mem_close(void *data){
	delete (MemData*)data;
	return 0;
}

int Mem_isatty(void *){
	return 0;
}

off_t Mem_lseek(void *data, off_t offset, int whence){
	//tfm::printf("Mem_lseek(%p, %s, %s)\n", data, offset, whence);
	MemData *mdata = (MemData*)data;
	errno = 0;
	ptrdiff_t startpos;
	switch(whence){
		case SEEK_SET: startpos = 0; break;
		case SEEK_CUR: startpos = mdata->pos; break;
		case SEEK_END: startpos = mdata->size; break;
		default: 
			errno = EINVAL;
			return (off_t)-1;
	}
	//tfm::printf("Mem_lseek pos: %s\n", mdata->pos);
	if(startpos + offset <= (ptrdiff_t)mdata->size && startpos + offset >= 0) mdata->pos = startpos + offset;
	else {
		errno = EINVAL;
		return (off_t)-1;
	}
	//tfm::printf("Mem_lseek pos: %s\n", mdata->pos);
	return mdata->pos;
}

int Mem_read(void *data, char *buf, int size){
	//tfm::printf("Mem_read(%p, %p, %s)\n", data, buf, size);
	MemData *mdata = (MemData*)data;
	if(mdata->pos + size > mdata->size && mdata->pos < mdata->size - 1) size = mdata->size - mdata->pos;
	if(mdata->pos + size <= mdata->size){
		if(size == 1){
			*buf = mdata->data[mdata->pos];
			++mdata->pos;
		}else{
			//tfm::printf("Mem_read: memcpy(%p, %p, %s)\n", buf, mdata->data + mdata->pos, size);
			memcpy(buf, mdata->data + mdata->pos, size);
			mdata->pos += size;
		}
		return size;
	}else return 0;
}

int Mem_write(void*, char*, int){
	return 0;
}

int Mem_fsync(void*){
	return 0;
}

virtual_handle MemoryVirtualHandle(const char *data, const size_t size){
	MemData *mdata = new MemData;
	mdata->data = data;
	mdata->size = size;
	mdata->pos = 0;
	
	virtual_handle ret;
	ret.type = HANDLE_VIRT;
	ret.virt.data = mdata;
	ret.virt.close = &Mem_close;
	ret.virt.isatty = &Mem_isatty;
	ret.virt.lseek = &Mem_lseek;
	ret.virt.read = &Mem_read;
	ret.virt.write = &Mem_write;
	ret.virt.fsync = &Mem_fsync;
	
	return ret;
}

struct OffsetData{
	int fd;
	off_t offset;
	off_t size;
	off_t pos;
	bool close;
};

int Off_close(void *data){
	OffsetData *odata = (OffsetData*)data;
	if(odata->close) close(odata->fd);
	delete odata;
	return 0;
}

int Off_isatty(void *){
	return 0;
}

off_t Off_lseek(void *data, off_t offset, int whence){
	OffsetData *odata = (OffsetData*)data;
	errno = 0;
	off_t startpos;
	switch(whence){
		case SEEK_SET: startpos = 0; break;
		case SEEK_CUR: startpos = odata->pos; break;
		case SEEK_END: startpos = odata->size; break;
		default: 
			errno = EINVAL;
			return (off_t)-1;
	}
	
	if(startpos + offset <= odata->size && startpos + offset >= 0) odata->pos = startpos + offset;
	else{
		errno = EINVAL;
		return (off_t)-1;
	}
	return odata->pos;
}

int Off_read(void *data, char *buf, int size){
	OffsetData *odata = (OffsetData*)data;
	if(odata->pos + size > odata->size && odata->pos < odata->size - 1) size = odata->size - odata->pos;
	if(odata->pos + size <= odata->size){
		lseek(odata->fd, odata->offset + odata->pos, SEEK_SET);
		int ret = read(odata->fd, buf, size);
		odata->pos += ret;
		return ret;
	}else return 0;
}

int Off_write(void*, char*, int){
	return 0;
}

int Off_fsync(void*){
	return 0;
}

virtual_handle FileOffsetVirtualHandle(int fd, off_t offset, off_t size, bool close){
	OffsetData *odata = new OffsetData;
	odata->fd = fd;
	odata->offset = offset;
	odata->size = size;
	odata->pos = 0;
	odata->close = close;
	
	virtual_handle ret;
	ret.type = HANDLE_VIRT;
	ret.virt.data = odata;
	ret.virt.close = &Off_close;
	ret.virt.isatty = &Off_isatty;
	ret.virt.lseek = &Off_lseek;
	ret.virt.read = &Off_read;
	ret.virt.write = &Off_write;
	ret.virt.fsync = &Off_fsync;
	
	return ret;
}