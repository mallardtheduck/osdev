#include <btos_module.h>
#include <util/holdlock.hpp>
#include <util/operation_queue.hpp>
extern "C" {
    #include "fat_filelib.h"
}

namespace fat_operation_types{
    enum Enum{
        Read,
        Write,
        Seek,
        Sync,
        Shutdown,
    };
}

namespace fat_operation_status{
    enum Enum{
        Pending,
        Error,
        Complete,
    };
}

struct fat_operation{
    fat_operation_types::Enum type;
    fat_operation_status::Enum status;
    void *flh;
    uint32_t pos;
    int origin;
    uint8_t *buf;
    size_t size;
    pid_t pid;
};


bool fat_queue_proc(fat_operation *op){
    pid_t pid=getpid();
    setpid(op->pid);
    if(op->type==fat_operation_types::Read){
        op->size=fl_fread(op->buf, op->size, 1, op->flh);
        op->status=fat_operation_status::Complete;
    }else if(op->type==fat_operation_types::Write) {
        op->size = fl_fwrite(op->buf, op->size, 1, op->flh);
        op->status = fat_operation_status::Complete;
    }else if(op->type==fat_operation_types::Seek){
        fl_fseek(op->flh, op->pos, op->origin);
        op->pos=fl_ftell(op->flh);
        op->status=fat_operation_status::Complete;
    }else if(op->type==fat_operation_types::Sync){
        op->status=fat_operation_status::Complete;
    }else{
        return false;
    }
    setpid(pid);
    return true;
}

typedef operation_queue<fat_operation, &fat_queue_proc, 128> fat_queue;
fat_queue *queue;

bool operation_blockckeck(void *p){
    return ((fat_operation*)p)->status!=fat_operation_status::Pending;
}

void fat_sync(){
    fat_operation op;
    op.status=fat_operation_status::Pending;
    op.type=fat_operation_types::Sync;
    op.pid=getpid();
    queue->add(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
}

void init_queue(){
    dbgout("FAT: Initialising queue...\n");
    queue=new fat_queue();
    dbgout("FAT: Syncing...\n");
    fat_sync();
}

size_t fat_queued_read(void *flh, uint8_t *buf, size_t size){
    fat_operation op;
    op.status=fat_operation_status::Pending;
    op.flh=flh;
    op.buf=buf;
    op.size=size;
    op.pid=getpid();
    op.type=fat_operation_types::Read;
    queue->add(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
    return op.size;
}

size_t fat_queued_write(void *flh, uint8_t *buf, size_t size){
    fat_operation op;
    op.status=fat_operation_status::Pending;
    op.flh=flh;
    op.buf=buf;
    op.size=size;
    op.pid=getpid();
    op.type=fat_operation_types::Write;
    queue->add(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
    return op.size;
}

size_t fat_queued_seek(void *flh, uint32_t pos, int origin){
    fat_operation op;
    op.status=fat_operation_status::Pending;
    op.flh=flh;
    op.pos=pos;
    op.origin=origin;
    op.pid=getpid();
    op.type=fat_operation_types::Seek;
    queue->add(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
    return op.pos;
}