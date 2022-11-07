#include "../../kernel.hpp"
#include "../../locks.hpp"

#include "thread.hpp"
#include "scheduler.hpp"

#include <util/asprintf.h>

ManualStaticAlloc<Scheduler> theScheduler;

constexpr auto MaxLoadModifier = 128;

char *Scheduler::ThreadsInfoFS(){
	auto &that = *theScheduler;

	bool showall = GetPermissionManager().HasPermission(0, kperm::SeeAllProcs);
	auto uid = CurrentProcess().GetUID();

	char *buffer = nullptr;
	asprintf(&buffer, "# ID, PID, priority, name, status, load\n");
	{ auto hl = that.lock->LockExclusive();
		for(auto t : that.threads){
			auto pid = t->GetPID();
			if(!showall){
				auto proc = GetProcess(pid);
				uint64_t tuid = proc->GetUID();
				if(tuid != uid) continue;
			}
			reasprintf_append(&buffer, "%llu, %llu, %lu, %s, %i, %li\n",
				t->ID(), pid, t->staticPriority, t->GetName(),
				(int)t->GetStatus(), t->loadModifier);
		}
	}
	return buffer;
}

void Scheduler::TheIdleThread(void*){
	Thread *myThread = theScheduler->current;
	myThread->SetName("IDLE");
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
			for(auto &h : theScheduler->idleHooks) h();
			GetHAL().HaltCPU();
			myThread->Yield(nullptr);
		}
	}
}

void Scheduler::TheReaperThread(void*){
	Thread *myThread = theScheduler->current;
	myThread->SetName("Thread Reaper");
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
					for(auto n = theScheduler->current; n != nullptr; n = n->next){
						if(n->next && n->next == thread){
							if(n->next->next) n->next = n->next->next;
							else n->next = nullptr;
						}
					}
					theScheduler->threads.erase(i);
					theScheduler->lock->Release();
					mm2_virtual_free(stackptr, stackpages + 1);
					delete thread;
					theScheduler->lock->TakeExclusive();
					changed=true;
					dbgpf("SCH: Reaped %i (%i) [thread: %p stack: %p].\n", (int)i, (int)id, thread, stackptr);
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
	mainThread->SetName("Main");
	mainThread->id = ++idCounter;
	threads.push_back(mainThread);
	auto idleThreadPointer = NewThread(TheIdleThread, nullptr, DefaultStackSize);
	idleThread = static_cast<Thread*>(idleThreadPointer.get());
	idleThread->status = ThreadStatus::Special;
	auto reaperThreadPointer = NewThread(TheReaperThread, nullptr, DefaultStackSize);
	reaperThread = static_cast<Thread*>(reaperThreadPointer.get());
	current = mainThread;
	
	GetHAL().SetSchedulerFrequency(30);

	InfoRegister("THREADS", &ThreadsInfoFS);
}

ThreadPointer Scheduler::NewThread(ThreadEntryFunction fn, void *param, size_t stackSize){
	auto thread = new Thread(fn, param, stackSize);
	{
		auto hl = lock->LockExclusive();
		thread->id = ++idCounter;
		threads.push_back(thread);
	}
	return threads.back();
}

IThread &Scheduler::CurrentThread(){
	return *(IThread*)current;
}

ThreadPointer Scheduler::GetByID(uint64_t id){
	auto hl = lock->LockExclusive();
	for(auto thread : threads){
		if(thread->id == id) return thread;
	}
	return nullptr;
}

size_t Scheduler::GetPIDThreadCount(uint64_t pid){
	auto hl = lock->LockExclusive();
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
		auto hl = lock->LockExclusive();
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
	auto hl = lock->LockExclusive();
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
	auto hl = lock->LockExclusive();
	for(auto thread : threads){
		if(thread == current) continue;
		if(thread->pid == pid){
			if(thread->status == ThreadStatus::Runnable){
				thread->status = ThreadStatus::HeldRunnable;
			}else if(thread->status == ThreadStatus::Blocked){
				thread->status = ThreadStatus::HeldBlocked;
			}
		}
	}
}

void Scheduler::UnHoldThreadsByPID(uint64_t pid){
	auto hl = lock->LockExclusive();
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

void Scheduler::AbortThreadsByPID(uint64_t pid){
	auto hl = lock->LockExclusive();
	for(auto thread : threads){
		if(thread->pid == pid) thread->Abort();
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
		if(thread->status == ThreadStatus::Blocked && thread->blockCheck && thread->blockCheck()){
			thread->status = ThreadStatus::Runnable;
			thread->blockCheck = nullptr;
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
				thread->next = nullptr;
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
	lock->Transfer(next);
	current = next;
	if(Processes_Ready()) GetProcessManager().SwitchProcessFromScheduler(next->pid);
	else if(next->pid != 0) panic("(SCH) PID != 0 before processes!");
	if(current->loadModifier < MaxLoadModifier) ++current->loadModifier;
	current->dynamicPriority = current->staticPriority + current->loadModifier;
	GetHAL().SetKernelStack(current->stackBase);
	return next->stackToken;
}

void Scheduler::EnableScheduler(){
	auto il = GetHAL().LockInterrupts();
	if(lock->IsLocked() && lock->GetOwningThreadID() == current->ID()) lock->Release(false, false);
}

bool Scheduler::DisableScheduler(){
	return lock->TryTakeExclusive();
}

bool Scheduler::CanYield(){
	return !lock->IsLocked();
}

void Scheduler::AddIdleHook(function<void()> fn){
	idleHooks.push_back(fn);
}

void Scheduler::RemoveIdleHook(function<void()> fn){
	auto i = idleHooks.find(fn);
	idleHooks.erase(i);
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