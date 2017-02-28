#include <util/operation_queue.hpp>
#include "ops.hpp"
#include "modes.hpp"
#include "device.hpp"

namespace vga_operation_types{
	enum Enum{
		Write,
		Sync,
		Shutdown,
	};
}

namespace vga_operation_status{
    enum Enum{
        Pending,
        Error,
        Complete,
    };
}

struct vga_operation{
	vga_operation_types::Enum type;
	vga_operation_status::Enum status;
	size_t offset;
	size_t size;
	uint8_t data[];
};

bool vga_queue_proc(vga_operation *op){
	if(op->type == vga_operation_types::Write){
		current_mode->write_pixels(op->offset, op->size, op->data);
		op->status = vga_operation_status::Complete;
		free(op);
		return true;
	}else if(op->type == vga_operation_types::Sync){
		op->status = vga_operation_status::Complete;
		return true;
	}else if(op->type == vga_operation_types::Shutdown){
		op->status = vga_operation_status::Complete;
		return false;
	}
	return true;
}

typedef operation_queue<vga_operation, &vga_queue_proc, 128> vga_queue;
vga_queue *queue = 0;

bool operation_blockcheck(void *p){
    return ((vga_operation*)p)->status!=vga_operation_status::Pending;
}

void q_sync(){
	if(!queue) return;
	vga_operation op;
	op.type = vga_operation_types::Sync;
	op.status = vga_operation_status::Pending;
	queue->add(&op);
	thread_setblock(&operation_blockcheck, (void*)&op);
}

size_t graphics_read(vga_instance *inst, size_t bytes, char *buf){
	q_sync();
    size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    size_t maxbytes=maxpix - inst->pos;
    if(bytes > maxpix) bytes=0;
    if(bytes > maxbytes) bytes=maxbytes;
    size_t pixpos=inst->pos;
    size_t pixcount=bytes;
    if(current_mode->vidmode.bpp == 4) {
        pixpos = inst->pos * 2;
        pixcount=bytes * 2;
    }
    current_mode->read_pixels(pixpos, pixcount, (uint8_t*)buf);
    inst->pos+=bytes;
    return bytes;
}

size_t graphics_write(vga_instance *inst, size_t bytes, char *buf){
    size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    size_t maxbytes=maxpix - inst->pos;
    if(bytes > maxpix) bytes=0;
    if(bytes > maxbytes) bytes=maxbytes;
    size_t pixpos=inst->pos;
    size_t pixcount=bytes;
    if(current_mode->vidmode.bpp == 4) {
        pixpos = inst->pos * 2;
        pixcount=bytes * 2;
    }
	if(!queue) queue = new vga_queue();
	vga_operation *op = (vga_operation*)malloc(sizeof(vga_operation) + bytes);
	op->type = vga_operation_types::Write;
	op->offset = pixpos;
	op->size = pixcount;
	op->status = vga_operation_status::Pending;
	memcpy(op->data, buf, bytes);
	queue->add(op);
    //current_mode->write_pixels(pixpos, pixcount, (uint8_t*)buf);
    inst->pos+=bytes;
    return bytes;
}

size_t graphics_seek(vga_instance *inst, size_t pos, uint32_t flags){
	size_t maxpix=current_mode->vidmode.width * current_mode->vidmode.height;
    if(flags & FS_Relative){
        inst->pos+=pos;
	}else if(flags & FS_Backwards){
		inst->pos=maxpix - pos;
	}else if(flags == (FS_Relative | FS_Backwards)){
		inst->pos-=pos;
    }else{
        inst->pos=pos;
    }
    if(inst->pos > maxpix) inst->pos=maxpix;
    if(current_mode->vidmode.bpp == 4 && inst->pos > maxpix/2) inst->pos=maxpix/2;
    return inst->pos;
}

void graphics_end(){
	if(!queue) return;
	vga_operation op;
	op.type = vga_operation_types::Shutdown;
	op.status = vga_operation_status::Pending;
	queue->add(&op);
	thread_setblock(&operation_blockcheck, (void*)&op);
	queue->wait_for_end();
	delete queue;
	queue = NULL;
}