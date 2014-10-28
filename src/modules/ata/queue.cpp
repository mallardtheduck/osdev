#include <module_stubs.h>
#include <holdlock.hpp>
#include "ata.hpp"

namespace ata_operation_types{
    enum Enum{
        Read,
        Write,
        Sync,
        Shutdown,
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
};

const size_t QUEUE_SIZE=128;
static ata_operation *queue[QUEUE_SIZE];
static size_t queue_top=0, queue_count=0;
lock queue_lock;

ata_operation *get_operation(){
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

void queue_opeation(ata_operation *op){
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

void ata_queue_thread(void*){
    while(true){
        thread_setblock(&queue_blockcheck, (void*)&queue_count);
        {
            hold_lock hl(&queue_lock);
            ata_operation *op=get_operation();
            pid_t pid=getpid();
            setpid(op->pid);
            if(op->type==ata_operation_types::Read){
                ata_device_read_sector(op->device, op->lba, op->buf);
                op->status=ata_operation_status::Complete;
            }else if(op->type==ata_operation_types::Write){
                ata_device_write_sector_retry(op->device, op->lba, op->buf);
                op->status=ata_operation_status::Complete;
            }else if(op->type==ata_operation_types::Sync){
                op->status=ata_operation_status::Complete;
            }else{
                break;
            }
            setpid(pid);
        }
    }
}

bool operation_blockckeck(void *p){
    return ((ata_operation*)p)->status!=ata_operation_status::Pending;
}

void ata_sync(){
    ata_operation op;
    op.status=ata_operation_status::Pending;
    op.type=ata_operation_types::Sync;
    op.pid=getpid();
    queue_opeation(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
}

void init_queue(){
    init_lock(&queue_lock);
    dbgout("ATA: Starting queue thread...\n");
    new_thread(&ata_queue_thread, NULL);
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
    queue_opeation(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
}

void ata_queued_write(ata_device *dev, uint32_t lba, uint8_t *buf){
    ata_operation op;
    op.status=ata_operation_status::Pending;
    op.device=dev;
    op.lba=lba;
    op.buf=buf;
    op.pid=getpid();
    op.type=ata_operation_types::Write;
    queue_opeation(&op);
    thread_setblock(&operation_blockckeck, (void*)&op);
}