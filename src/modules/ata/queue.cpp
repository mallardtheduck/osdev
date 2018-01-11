#include <btos_module.h>
#include <util/holdlock.hpp>
#include <util/operation_queue.hpp>
#include "ata.hpp"

namespace ata_operation_types{
    enum Enum{
        Read,
        Write,
        Sync,
        Shutdown,
		ATAPIRead,
    };
}

namespace ata_operation_status{
    enum Enum{
        Pending,
        Error,
        Complete,
    };
}

struct ata_operation{
    ata_operation_types::Enum type;
    ata_operation_status::Enum status;
    ata_device *device;
    uint32_t lba;
    uint8_t *buf;
    pid_t pid;
	size_t retval;
};

bool ata_queue_proc(ata_operation *op){
    pid_t pid=getpid();
    if(setpid(op->pid)){
		if(op->type==ata_operation_types::Read){
		    ata_device_read_sector(op->device, op->lba, op->buf);
		    op->status=ata_operation_status::Complete;
		}else if(op->type==ata_operation_types::Write){
		    ata_device_write_sector_retry(op->device, op->lba, op->buf);
		    op->status=ata_operation_status::Complete;
		}else if(op->type==ata_operation_types::Sync){
		    op->status=ata_operation_status::Complete;
		}else if(op->type==ata_operation_types::ATAPIRead){
			op->retval = atapi_device_read(op->device, op->lba, op->buf);
			op->status=ata_operation_status::Complete;
		}else{
			dbgpf("ATA: Invalid operation: %i\n", op->type);
		    op->status=ata_operation_status::Error;
		}
		setpid(pid);
	}else{
		dbgpf("ATA: Could not set pid to: %i (current pid: %i)\n", (int)op->pid, (int)pid);
		op->status=ata_operation_status::Error;
	}
    return true;
}

typedef operation_queue<ata_operation, &ata_queue_proc, 128> ata_queue;
ata_queue *queue;

bool operation_blockcheck(void *p){
    return ((ata_operation*)p)->status!=ata_operation_status::Pending;
}

void ata_sync(){
    ata_operation op;
    op.status=ata_operation_status::Pending;
    op.type=ata_operation_types::Sync;
    op.pid=getpid();
    queue->add(&op);
    thread_setblock(&operation_blockcheck, (void*)&op);
}

void init_queue(){
    dbgout("ATA: Initialising queue...\n");
    queue=new ata_queue();
	dbgpf("ATA: queue at: %p\n", queue);
    dbgout("ATA: Syncing...\n");
    ata_sync();
}

void ata_queued_read(ata_device *dev, uint32_t lba, uint8_t *buf){
    ata_operation op;
    op.status=ata_operation_status::Pending;
    op.device=dev;
    op.lba=lba;
    op.buf=buf;
    op.pid=getpid();
    op.type=ata_operation_types::Read;
    queue->add(&op);
    thread_setblock(&operation_blockcheck, (void*)&op);
}

void ata_queued_write(ata_device *dev, uint32_t lba, uint8_t *buf){
    ata_operation op;
    op.status=ata_operation_status::Pending;
    op.device=dev;
    op.lba=lba;
    op.buf=buf;
    op.pid=getpid();
    op.type=ata_operation_types::Write;
    queue->add(&op);
    thread_setblock(&operation_blockcheck, (void*)&op);
}

size_t atapi_queued_read(ata_device *dev, uint32_t lba, uint8_t *buf){
    ata_operation op;
    op.status=ata_operation_status::Pending;
    op.device=dev;
    op.lba=lba;
    op.buf=buf;
    op.pid=getpid();
    op.type=ata_operation_types::ATAPIRead;
    queue->add(&op);
    thread_setblock(&operation_blockcheck, (void*)&op);
	return op.retval;
}

