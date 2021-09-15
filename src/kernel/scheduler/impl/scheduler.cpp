#include "../../kernel.hpp"
#include "../../locks.hpp"

#include "thread.hpp"
#include "scheduler.hpp"

ManualStaticAlloc<Scheduler> theScheduler;

constexpr auto MaxLoadModifier = 128;

// char *sch_threads_infofs(){
// 	bool showall = has_perm(0, kperm::SeeAllProcs);
// 	uint64_t uid = proc_get_uid();
// 	char *buffer=nullptr;
// 	asprintf(&buffer, "# ID, PID, priority, addr, status, alevel, load\n");
// 	{hold_lock hl(sch_lock);
// 		for(size_t i=0; i<threads->size(); ++i){
// 			sch_thread *t=(*threads)[i];
// 			if(!showall){
// 				uint64_t tuid = proc_get_uid_nolock(t->pid);
// 				if(tuid != uid) continue;
// 			}
// 			reasprintf_append(&buffer, "%llu, %llu, %lu, %lx, %i, %i, %li\n", t->ext_id, t->pid, t->priority, t->eip,
// 				(int)t->status, t->abortlevel, t->modifier);
// 		}
//     }
//     return buffer;
// }

void Scheduler::TheIdleThread(void*){
	Thread *myThread = theScheduler->current;
	while(true){
		bool yield_immediately = false;
		{
			auto hl = theScheduler->lock->LockExclusive();
			for(auto thread : theScheduler->threads){			
				if(thread->status == ThreadStatus::Blocked && thread->blockCheck){
					auto il = GetHAL().LockInterrupts();
					thread->status = thread->blockCheck() ? ThreadStatus::Runnable : ThreadStatus::Blocked;
				}
				
				yield_immediately = (thread->status == ThreadStatus::Runnable);
			}
		}
		if(yield_immediately) myThread->Yield(nullptr);
		else{
			GetHAL().HaltCPU();
			myThread->Yield(nullptr);
		}
	}
}

void Scheduler::TheReaperThread(void*){
    Thread *myThread = theScheduler->current;
	myThread->SetPriority(1);
	while(true){
		bool changed=true;
		while(changed){
			auto hl = theScheduler->lock->LockExclusive();
			changed=false;
			for(size_t i = 0; i < theScheduler->threads.size(); ++i){
				auto thread = theScheduler->threads[i];
				if(thread->status == ThreadStatus::Ending){
					if(thread->refCount > 0){
						thread->awaitingDestruction = true;
						continue;
					}
					auto id = thread->id;
                    void *stackptr = thread->stackPointer;
					size_t stackpages = thread->stackPages;
					theScheduler->threads.erase(i);
                    theScheduler->lock->Release();
                    mm2_virtual_free(stackptr, stackpages + 1);
					delete thread;
                    theScheduler->lock->TakeExclusive();
					changed=true;
					dbgpf("SCH: Reaped %i (%i) [%p].\n", (int)i, (int)id, stackptr);
					break;
				}
			}
		}
		myThread->Block();
	}
}

Scheduler::Scheduler(){
	lock = NewLock();
	auto mainThread = new Thread();
	threads.push_back(mainThread);
	auto idleThreadPointer = NewThread(TheIdleThread, nullptr, DefaultStackSize);
	idleThread = static_cast<Thread*>(idleThreadPointer.get());
	idleThread->status = ThreadStatus::Special;
	auto reaperThreadPointer = NewThread(TheReaperThread, nullptr, DefaultStackSize);
	reaperThread = static_cast<Thread*>(reaperThreadPointer.get());

	GetHAL().SetSchedulerFrequency(30);
}

ThreadPointer Scheduler::NewThread(ThreadEntryFunction fn, void *param, size_t stackSize){
	auto thread = new Thread(fn, param, stackSize);
	{
		auto hl = theScheduler->lock->LockExclusive();
		thread->id = idCounter++;
		threads.push_back(thread);
	}
	return threads.back();
}

IThread &Scheduler::CurrentThread(){
	return *(IThread*)current;
}

ThreadPointer Scheduler::GetByID(uint64_t id){
	auto hl = theScheduler->lock->LockExclusive();
	for(auto thread : threads){
		if(thread->id == id) return thread;
	}
	return nullptr;
}

size_t Scheduler::GetPIDThreadCount(uint64_t pid){
	auto hl = theScheduler->lock->LockExclusive();
	size_t ret = 0;
	for(auto thread : threads){
		if(thread->pid == pid) ++ret;
	}
	return ret;
}

void Scheduler::DebugStopThreadsByPID(uint64_t pid){
	if(current->pid == pid){
		panic("(SCH) Cannot debug-stop current PID!");
	}else{
		auto hl = theScheduler->lock->LockExclusive();
		for(auto thread : threads){
			if(thread->pid == pid){
				if(thread->status == ThreadStatus::Runnable){
					thread->status = ThreadStatus::DebugStopped;
				}else if(thread->status == ThreadStatus::Blocked){
					thread->status = ThreadStatus::DebugBlocked;
				}
			}
		}
	}
}

void Scheduler::DebugResumeThreadsByPID(uint64_t pid){
	auto hl = theScheduler->lock->LockExclusive();
	for(auto thread : threads){
		if(thread->pid == pid){
			if(thread->status == ThreadStatus::DebugStopped){
				thread->status = ThreadStatus::Runnable;
			}else if(thread->status == ThreadStatus::DebugBlocked){
				thread->status = ThreadStatus::Blocked;
			}
		}
	}
}

void Scheduler::HoldThreadsByPID(uint64_t pid){
	if(current->pid == pid){
		panic("(SCH) Cannot hold current PID!");
	}else{
		auto hl = theScheduler->lock->LockExclusive();
		for(auto thread : threads){
			if(thread->pid == pid){
				if(thread->status == ThreadStatus::Runnable){
					thread->status = ThreadStatus::HeldRunnable;
				}else if(thread->status == ThreadStatus::Blocked){
					thread->status = ThreadStatus::HeldBlocked;
				}
			}
		}
	}
}

void Scheduler::UnHoldThreadsByPID(uint64_t pid){
	auto hl = theScheduler->lock->LockExclusive();
	for(auto thread : threads){
		if(thread->pid == pid){
			if(thread->status == ThreadStatus::HeldRunnable){
				thread->status = ThreadStatus::Runnable;
			}else if(thread->status == ThreadStatus::HeldBlocked){
				thread->status = ThreadStatus::Blocked;
			}
		}
	}
}

bool Scheduler::CanLock(){
	bool ret = lock->TryTakeExclusive();
	if(ret) lock->Release();
	return ret;
}

Thread *Scheduler::PlanCycle(){
	scheduleCyle++;
	uint32_t minPriority = UINT32_MAX;
	for(auto thread : threads){
		if(thread->loadModifier > 0) --thread->loadModifier;
		if(thread->status == ThreadStatus::Blocked && thread->blockCheck){
			thread->status = thread->blockCheck() ? ThreadStatus::Runnable : ThreadStatus::Blocked;
		}
		if(thread->status == ThreadStatus::Runnable && thread->dynamicPriority < minPriority) minPriority = thread->dynamicPriority;
	}
	Thread *head = nullptr;
	Thread *last = nullptr;
	for(auto thread : threads){
		if(thread->status == ThreadStatus::Runnable){
			thread->dynamicPriority -= minPriority;
			if(thread->dynamicPriority == 0){
				thread->scheduleCycle = scheduleCyle;
				++current->loadModifier;
				if(!head) head = thread;
				if(last) last->next = thread;
				last = thread;
			}
		}
	}
	if(!head) head = idleThread;
	return head;
}

uint64_t Scheduler::Schedule(uint64_t stackToken){
	current->stackToken = stackToken;
	auto next = current->next;
	while(next && next->status != ThreadStatus::Runnable){
		next = next->next;
	}
	if(!next) next = PlanCycle();
	current = next;
	if(current->loadModifier < MaxLoadModifier) ++current->loadModifier;
	current->dynamicPriority = current->staticPriority + current->loadModifier;
	return next->stackToken;
}

void Scheduler::EnableScheduler(){
	auto il = GetHAL().LockInterrupts();
	if(lock->IsLocked() && lock->GetOwningThreadID() == current->ID()) lock->Release();
}

bool Scheduler::DisableScheduler(){
	return lock->TryTakeExclusive();
}

bool Scheduler_Ready(){
	return theScheduler;
}

void Scheduler_Init(){
	theScheduler.Init();
}

IScheduler &GetScheduler(){
	return *theScheduler;
}