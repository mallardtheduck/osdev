#include "../../kernel.hpp"
#include "../../locks.hpp"

#include "thread.hpp"
#include "scheduler.hpp"

static char schedulerBuffer[sizeof(Scheduler)];
Scheduler *theScheduler = nullptr;

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
			hold_lock hl(theScheduler->lock);
			for(auto thread : theScheduler->threads){			
				if(thread->status == ThreadStatus::Blocked && thread->blockCheck){
					auto il = GetHAL().LockInterrupts();
					thread->status = thread->blockCheck(thread->blockCheckParam) ? ThreadStatus::Runnable : ThreadStatus::Blocked;
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
			hold_lock lck(theScheduler->lock);
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
                    release_lock(theScheduler->lock);
                    mm2_virtual_free(stackptr, stackpages + 1);
					delete thread;
                    take_lock_exclusive(theScheduler->lock);
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
	init_lock(lock);
	auto mainThread = new Thread();
	threads.push_back(mainThread);
	idleThread = dynamic_cast<Thread*>(&NewThread(TheIdleThread, nullptr, DefaultStackSize));
	idleThread->status = ThreadStatus::Special;
	reaperThread = dynamic_cast<Thread*>(&NewThread(TheReaperThread, nullptr, DefaultStackSize));

	GetHAL().RegisterScheduler(*this);
}

ThreadPointer Scheduler::NewThread(ThreadEntryFunction fn, void *param, size_t stackSize){
	auto thread = new Thread(fn, param, stackSize);
	{
		hold_lock hl(lock);
		thread->id = idCounter++;
		threads.push_back(thread);
	}
	return threads.back();
}

IThread &Scheduler::CurrentThread(){
	return *(IThread*)current;
}

ThreadPointer Scheduler::GetByID(uint64_t id){
	hold_lock hl(lock);
	for(auto thread : threads){
		if(thread->id == id) return thread;
	}
	return nullptr;
}

size_t Scheduler::GetPIDThreadCount(uint64_t pid){
	hold_lock hl(lock);
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
		hold_lock hl(lock);
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
	hold_lock hl(lock);
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
		hold_lock hl(lock);
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
	hold_lock hl(lock);
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

bool Scheduler::IsActive(){
	return true;
}

bool Scheduler::CanLock(){
	bool ret = try_take_lock_exclusive(lock);
	if(ret) release_lock(lock);
	return ret;
}

Thread *Scheduler::PlanCycle(){
	scheduleCyle++;
	uint32_t minPriority = UINT32_MAX;
	for(auto thread : threads){
		if(thread->loadModifier > 0) --thread->loadModifier;
		if(thread->status == ThreadStatus::Blocked && thread->blockCheck){
			thread->status = thread->blockCheck(thread->blockCheckParam) ? ThreadStatus::Runnable : ThreadStatus::Blocked;
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
	++current->loadModifier;
	current->dynamicPriority = current->staticPriority + current->loadModifier;
	return next->stackToken;
}

void Scheduler_Init(){
	theScheduler = new(schedulerBuffer) Scheduler();
}

IScheduler &GetScheduler(){
	return *theScheduler;
}