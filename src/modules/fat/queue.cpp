#include <module_stubs.h>
#include <holdlock.hpp>
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

const size_t QUEUE_SIZE=128;
static fat_operation *queue[QUEUE_SIZE];
static size_t queue_top=0, queue_count=0;
lock queue_lock;

fat_operation *get_operation(){
    hold_lock hl(&queue_lock, false);
    if(queue_count){
        int start=queue_top-queue_count;
        if(start < 0) {
            start+=QUEUE_SIZE;
        }
        queue_count--;
        return queue[start];
    }else return NULL;
}

bool queue_full_blockcheck(void *){
    return queue_count < QUEUE_SIZE;
}

void queue_opeation(fat_operation *op){
    hold_lock hl(&queue_lock);
    while(queue_count >= QUEUE_SIZE){
        release_lock(&queue_lock);
        thread_setblock(&queue_full_blockcheck, NULL);
        take_lock(&queue_lock);
    }
    if(queue_count < QUEUE_SIZE){
        queue_count++;
        queue[queue_top] = op;
        queue_top++;
        if(queue_top == QUEUE_SIZE) queue_top=0;
    }
}


bool queue_blockcheck(void *p){
    return (*(size_t*)p) > 0;
}

void fat_queue_thread(void*){
    pid_t pid=getpid();
    while(true){
        thread_setblock(&queue_blockcheck, (void*)&queue_count);
        {
            hold_lock hl(&queue_lock);
            fat_operation *op=get_operation();
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
                break;
            }
            setpid(pid);
        }
    }
}

bool operation_blockckeck(void *p){
    return ((fat_operation*)p)->status!=fat_operation_status::Pending;
}

void fat_sync(){
    fat_operation op;
    op.status=fat_operation_status::Pending;
    op.type=fat_operation_types::Sync;
    op.pid=getpid();
    queue_opeation(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
}

void init_queue(){
    init_lock(&queue_lock);
    dbgout("FAT: Starting queue thread...\n");
    new_thread(&fat_queue_thread, NULL);
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
    queue_opeation(&op);
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
    queue_opeation(&op);
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
    queue_opeation(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
    return op.pos;
}