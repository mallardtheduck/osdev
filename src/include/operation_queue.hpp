#ifndef _OPERATION_QUEUE_HPP
#define _OPERATION_QUEUE_HPP

#include "module_stubs.h"
#include "holdlock.hpp"

template<typename opT, bool (*proccessFn)(opT*), size_t queue_size> class operation_queue{
private:
    typedef operation_queue<opT, proccessFn, queue_size> this_type;

    opT *queue[queue_size];
    size_t queue_count, queue_top;
    lock queue_lock;

    static bool operation_queue_blockcheck(void *q){
        return *(size_t*)q > 0;
    }

    opT *get(){
        hold_lock hl(&queue_lock);
        while(!queue_count){
            release_lock(&queue_lock);
            thread_setblock(&operation_queue_blockcheck, (void*)&queue_count);
            take_lock(&queue_lock);
        }
        if(queue_count){
            int start=queue_top-queue_count;
            if(start < 0) {
                start+=queue_size;
            }
            queue_count--;
            return queue[start];
        }else return NULL;
    }

    static void operation_queue_process_thread(void *q) {
        this_type *op_q=(this_type*)q;
        while(true){
            opT *operation=op_q->get();
            if(!proccessFn(operation)) break;
        }
    }

    static bool operation_queue_full_blockcheck(void *q){
        return *(size_t*)q < queue_size;
    }

public:
    operation_queue(){
        queue_count=0;
        queue_top=0;
        init_lock(&queue_lock);
        new_thread(&operation_queue_process_thread, (void*)this);
    }

    void add(opT* op){
        hold_lock hl(&queue_lock);
        while(queue_count >= queue_size){
            release_lock(&queue_lock);
            thread_setblock(&operation_queue_full_blockcheck, (void*)&queue_count);
            take_lock(&queue_lock);
        }
        if(queue_count < queue_size){
            queue_count++;
            queue[queue_top] = op;
            queue_top++;
            if(queue_top == queue_size) queue_top=0;
        }
    }
};

#endif