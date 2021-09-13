#ifndef _HANDLES_HPP
#define _HANDLES_HPP

#include <module/handle.hpp>

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

class IDirectoryHandle;
class IAtom;
class WaitList;
class WaitOptions;
class msg_recv_handle;

namespace KernelHandles{
	template<uint32_t ID, typename HandleT> struct HandleMapping{
		static_assert(std::is_convertible<HandleT*, IHandle*>::value || std::is_null_pointer<HandleT>::value, "HandleT is not a handle?!?");
		static constexpr uint32_t id = ID;
		using handleType = HandleT;
	};

	using Invald =			HandleMapping<0, nullptr_t>;
	using Lock = 			HandleMapping<1, GenericHandle<ILock*>>;
	using File = 			HandleMapping<2, IFileHandle>;
	using Directory = 		HandleMapping<3, IDirectoryHandle>;
	using Thread = 			HandleMapping<4, GenericHandle<ThreadPointer>>;
	using MemoryMapping = 	HandleMapping<5, GenericHandle<uint64_t>>;
	using SHMSpace =		HandleMapping<6, GenericHandle<uint64_t>>;
	using SHMMapping =		HandleMapping<7, GenericHandle<uint64_t>>;
	using Atom =			HandleMapping<8, GenericHandle<IAtom*>>;
	using Wait = 			HandleMapping<9, GenericHandle<WaitList*>>;
	using AtomWait =		HandleMapping<10, GenericHandle<WaitOptions*>>;
	using MessageRecive	=	HandleMapping<11, GenericHandle<msg_recv_handle*>>;
	using Elf =				HandleMapping<12, nullptr_t>;
};

template<typename T, typename Tclose = nullptr_t, typename Twait = nullptr_t>
typename T::handleType *MakeKernelGenericHandle(typename T::handleType::dataType data, Tclose close = nullptr, Twait wait = nullptr){
	static_assert(IsGenericHandle<typename T::handleType>::value, "MakeKernelGenericHandle only works for GenericHandle handles!");
	return MakeGenericHandle(T::id, data, close, wait);
}

template<typename T> typename T::handleType *KernelHandleCast(IHandle *handle){
	if(handle && handle->GetType() == T::id) return static_cast<typename T::handleType *>(handle);
	else return nullptr;
}

void init_handles();

void AddHandleDependencyOn(IHandle *h);
void RemoveHandleDependencyOn(IHandle *h);

enum class HandleDependencyCheckResult{
	Present, Absent, NotAvailable
};

HandleDependencyCheckResult HandleDependencyCheck(IHandle *h);

void WaitOnHandle(IHandle *h);

#endif
