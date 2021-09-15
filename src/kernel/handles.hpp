#ifndef _HANDLES_HPP
#define _HANDLES_HPP

#include <module/handle.hpp>
#include <module/kernelsys/handles.hpp>

//TODO: Will be removed eventually.
namespace kernel_handle_types{
	//static const uint32_t invalid=0;
	//static const uint32_t lock=1;
	//static const uint32_t file=2;
	//static const uint32_t directory=3;
	//static const uint32_t thread=4;
	//static const uint32_t memory_mapping=5;
	//static const uint32_t shm_space=6;
	//static const uint32_t shm_mapping=7;
	//static const uint32_t atom=8;
	//static const uint32_t wait=9;
	//static const uint32_t atomwait=10;
	//static const uint32_t msg_recv=11;
	static const uint32_t elf = 12;
};

void init_handles();

void AddHandleDependencyOn(IHandle *h);
void RemoveHandleDependencyOn(IHandle *h);

HandleDependencyCheckResult HandleDependencyCheck(IHandle *h);

void WaitOnHandle(IHandle *h);

#endif
