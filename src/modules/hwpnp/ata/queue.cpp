#include <btos_module.h>
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
	btos_api::hwpnp::IATABus *bus;
	size_t busIndex;
	uint32_t lba;
	uint8_t *buf;
	bt_pid_t pid;
	uint64_t tid;
	size_t retval;
};

bool queueReady = false;

static bt_pid_t last_pid = 0;

bool ata_queue_proc(ata_operation *op){
	auto &processManager = API->GetProcessManager();
	if(processManager.SwitchProcess(op->pid)){
		last_pid = op->pid;
		if(op->type==ata_operation_types::Read){
			auto hl = op->bus->GetLock();
			ata_device_read_sector(op->bus, op->busIndex, op->lba, op->buf);
			op->status=ata_operation_status::Complete;
		}else if(op->type==ata_operation_types::Write){
			auto hl = op->bus->GetLock();
			ata_device_write_sector(op->bus, op->busIndex, op->lba, op->buf);
			op->status=ata_operation_status::Complete;
		}else if(op->type==ata_operation_types::Sync){
			op->status=ata_operation_status::Complete;
		}else if(op->type==ata_operation_types::ATAPIRead){
			auto hl = op->bus->GetLock();
			op->retval = atapi_device_read(op->bus, op->busIndex, op->lba, op->buf);
			op->status=ata_operation_status::Complete;
		}else{
			dbgpf("ATA: Invalid operation: %i\n", op->type);
			op->status=ata_operation_status::Error;
		}
		if(!API->GetProcessManager().SwitchProcess(0)){
			dbgout("ATA: Failed to reset PID to 0\n");
			panic("(ATA) Unable to reset PID after operation!");	
		}
	}else{
		dbgpf("ATA: Could not set pid to: %i\n", (int)op->pid);
		op->status=ata_operation_status::Error;
	}
	auto curPid = API->CurrentProcess().ID();
	if(curPid != 0){
		dbgpf("ATA: PID %i != 0\n", curPid);
		panic("(ATA) Incorrect PID after operation!");
	}
	return true;
}

void ata_yield_fn(){
	if(last_pid) API->CurrentThread().Yield();
	last_pid = 0;
}

typedef operation_queue<ata_operation, &ata_queue_proc, 128> ata_queue;
ata_queue *queue;

bool operation_blockcheck(const ata_operation &p){
	return p.status != ata_operation_status::Pending;
}

void ata_sync(){
	ata_operation op;
	op.bus = nullptr;
	op.status = ata_operation_status::Pending;
	op.type = ata_operation_types::Sync;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	queue->add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
}

void init_queue(){
	dbgout("ATA: Initialising queue...\n");
	queue = new ata_queue();
	queueReady = true;
	dbgpf("ATA: queue at: %p\n", queue);
	dbgout("ATA: Syncing...\n");
	ata_sync();
}

bool ata_queued_read(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t *buf){
	ata_operation op;
	op.status = ata_operation_status::Pending;
	op.bus = bus;
	op.busIndex = index;
	op.lba = lba;
	op.buf = buf;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	op.type = ata_operation_types::Read;
	queue->add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
	return op.status == ata_operation_status::Complete;
}

bool ata_queued_write(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t *buf){
	ata_operation op;
	op.status = ata_operation_status::Pending;
	op.bus = bus;
	op.busIndex = index;
	op.lba = lba;
	op.buf = buf;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	op.type = ata_operation_types::Write;
	queue->add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
	return op.status == ata_operation_status::Complete;
}

size_t atapi_queued_read(btos_api::hwpnp::IATABus *bus, size_t index, uint32_t lba, uint8_t *buf){
	ata_operation op;
	op.status = ata_operation_status::Pending;
	op.bus = bus;
	op.busIndex = index;
	op.lba = lba;
	op.buf = buf;
	op.pid = API->CurrentProcess().ID();
	op.tid = API->CurrentThread().ID();
	op.type = ata_operation_types::ATAPIRead;
	queue->add(&op);
	API->CurrentThread().SetBlock([&]{
		return operation_blockcheck(op);
	});
	return op.retval;
}
