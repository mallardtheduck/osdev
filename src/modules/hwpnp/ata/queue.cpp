#include <btos_module.h>
#include <module/utils/operationqueue.hpp>
#include "ata.hpp"

enum class ATAOperationType{
		Read,
		Write,
		Sync,
		Shutdown,
		ATAPIRead,
};

enum class ATAOperationStatus{
		Pending,
		Error,
		Complete,
};

struct ATAOperation{
	ATAOperationType type = ATAOperationType::Sync;
	ATAOperationStatus status = ATAOperationStatus::Pending;
	btos_api::hwpnp::IATABus *bus = nullptr;
	size_t busIndex = 0;
	uint32_t lba = 0;
	uint8_t *buf = nullptr;
	bt_pid_t pid = 0;
	uint64_t tid = 0;
	size_t retval = 0;
	size_t readSize = 0;
};

bool queueReady = false;

class ATAOperationQueue : public OperationQueue<ATAOperation, 256>{
private:
	uint8_t cacheBuffer[4096];

	ATAOperation lastOperation = {
		ATAOperationType::Sync, ATAOperationStatus::Complete, nullptr, 0, 0, nullptr, 0, 0, 0, 0
	};
	ATAOperation idleOp;

protected:
	bool Process(ATAOperation *op) override{
		API->CurrentThread().SetPriority(100);
		if(!op) return true;
		auto &processManager = API->GetProcessManager();
		if(op != &idleOp){
			lastOperation = *op;
			if(
				op->type == ATAOperationType::Read && idleOp.status == ATAOperationStatus::Complete
				&& op->bus == idleOp.bus && op->busIndex == idleOp.busIndex && op->lba == idleOp.lba
				&& processManager.SwitchProcess(op->pid)
			){
				memcpy(op->buf, cacheBuffer, op->readSize);
				op->status = ATAOperationStatus::Complete;
				processManager.SwitchProcess(0);
				return true;
			}
		}

		if(processManager.SwitchProcess(op->pid)){
			switch(op->type){
				case ATAOperationType::Read:{
					auto hl = op->bus->GetLock();
					ata_device_read_sector(op->bus, op->busIndex, op->lba, op->buf);
					op->status = ATAOperationStatus::Complete;
				}break;
				case ATAOperationType::Write:{
					auto hl = op->bus->GetLock();
					ata_device_write_sector(op->bus, op->busIndex, op->lba, op->buf);
					op->status = ATAOperationStatus::Complete;
				}break;
				case ATAOperationType::ATAPIRead:{
					auto hl = op->bus->GetLock();
					op->retval = atapi_device_read(op->bus, op->busIndex, op->lba, op->buf);
					op->status=ATAOperationStatus::Complete;
				}break;
				case ATAOperationType::Sync:{
					op->status = ATAOperationStatus::Complete;
				}break;
				case ATAOperationType::Shutdown:{
					return false;
				}break;
			}
		}else{
			dbgpf("ATA: Could not set pid to: %i\n", (int)op->pid);
			op->status = ATAOperationStatus::Error;
		}
		processManager.SwitchProcess(0);
		auto curPid = API->CurrentProcess().ID();
		if(curPid != 0){
			dbgpf("ATA: PID %i != 0\n", curPid);
			panic("(ATA) Incorrect PID after operation!");
		}
		return true;
	}

	void Idle() override{
		if(lastOperation.type == ATAOperationType::Read){
			idleOp = lastOperation;
			idleOp.buf = cacheBuffer;
			idleOp.pid = 0;
			idleOp.tid = 0;
			idleOp.lba++;
			idleOp.status = ATAOperationStatus::Pending;
			Add(&idleOp);
			lastOperation.type = ATAOperationType::Sync;
		}
		API->CurrentThread().Yield();
	}

	bool Batch(ATAOperation **batch, size_t size) override{
		size_t done = 0;
		while(done < size){
			ATAOperation *next = nullptr;
			for(size_t i = 0; i < size; ++i){
				if(batch[i]->status != ATAOperationStatus::Pending) continue;
				if(!next || batch[i]->lba < next->lba) next = batch[i];
			}
			if(!Process(next)) return false;
			++done;
		}
		return true;
	}
};

ATAOperationQueue *queue;

bool operation_blockcheck(const ATAOperation &p){
	return p.status != ATAOperationStatus::Pending;
}

void ata_sync(){
	ATAOperation op;
	op.bus = nullptr;
	op.status = ATAOperationStatus::Pending;
	op.type = ATAOperationType::Sync;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	queue->Add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
}

void init_queue(){
	dbgout("ATA: Initialising queue...\n");
	queue = new ATAOperationQueue();
	queueReady = true;
	dbgpf("ATA: queue at: %p\n", queue);
	dbgout("ATA: Syncing...\n");
	ata_sync();
}

bool ata_queued_read(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t *buf){
	ATAOperation op;
	op.status = ATAOperationStatus::Pending;
	op.bus = bus;
	op.busIndex = index;
	op.lba = lba;
	op.buf = buf;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	op.readSize = ATA_SECTOR_SIZE;
	op.type = ATAOperationType::Read;
	queue->Add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
	return op.status == ATAOperationStatus::Complete;
}

bool ata_queued_write(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t *buf){
	ATAOperation op;
	op.status = ATAOperationStatus::Pending;
	op.bus = bus;
	op.busIndex = index;
	op.lba = lba;
	op.buf = buf;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	op.type = ATAOperationType::Write;
	queue->Add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
	return op.status == ATAOperationStatus::Complete;
}

size_t atapi_queued_read(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t *buf){
	ATAOperation op;
	op.status = ATAOperationStatus::Pending;
	op.bus = bus;
	op.busIndex = index;
	op.lba = lba;
	op.buf = buf;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	op.type = ATAOperationType::ATAPIRead;
	queue->Add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
	return op.retval;
}
