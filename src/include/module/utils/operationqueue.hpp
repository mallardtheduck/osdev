#ifndef MODULE_UTIL_OPERATIONQUEUE_HPP
#define MODULE_UTIL_OPERATIONQUEUE_HPP

#include <btos_module.h>

template< typename opT, size_t QueueSize> class OperationQueue{
protected:
	virtual bool Process(opT *op) = 0;

	virtual bool Batch(opT **batch, size_t size){
		for(size_t i = 0; i < size; ++i){
			if(!Process(batch[i])) return false;
		}
		return true;
	}

	virtual void Idle(){
		API->CurrentThread().Yield();
	}
private:
	opT *queue[QueueSize];
	opT *batch[QueueSize];
	size_t queueCount = 0;
	size_t queueTop = 0;
	ILock *queueLock;
	uint64_t threadId;

	size_t MakeBatch(){
		auto hl = queueLock->LockExclusive();
		while(!queueCount){
			queueLock->Release();
			Idle();
			API->CurrentThread().SetBlock([&]{
				return queueCount > 0;
			});
			queueLock->TakeExclusive();
		}
		size_t batchSize = 0;
		while(queueCount){
			int start = queueTop - queueCount;
			if(start < 0) {
				start += QueueSize;
			}
			queueCount--;
			batch[batchSize++] = queue[start];
		}
		return batchSize;
	}

	void ProcessThread() {
		API->CurrentThread().SetName("Operation Queue");
		while(true){
			size_t batchSize = MakeBatch();
			if(!Batch(batch, batchSize)) return;
		}
	}

public:
	OperationQueue(){
		queueLock = API->NewLock();
		threadId = API->GetScheduler().NewThread([&]{
			ProcessThread();
		})->ID();
	}

	void Add(opT* op){
		if(threadId == 0) return;
		auto hl = queueLock->LockExclusive();
		while(queueCount >= QueueSize){
			queueLock->Release();
			API->CurrentThread().SetBlock([&]{
				return queueCount < QueueSize;
			});
			queueLock->TakeExclusive();
		}
		if(queueCount < QueueSize){
			queueCount++;
			queue[queueTop] = op;
			queueTop++;
			if(queueTop == QueueSize) queueTop=0;
		}
	}
	
	void WaitForEnd(){
		API->GetScheduler().JoinThread(threadId);
		threadId = 0;
	}
};

#endif
