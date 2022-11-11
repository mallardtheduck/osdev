#ifndef MODULE_HANDLES_HPP
#define MODULE_HANDLES_HPP

#include <module/handle.hpp>
#include <module/kernelsys/scheduler.hpp>

class ILock;
class IFileHandle;
class IDirectoryHandle;
class IAtom;
class WaitList;
class WaitOptions;
class IMessageRecieveHandle;

namespace KernelHandles{
	template<uint32_t ID, typename HandleT> struct HandleMapping{
		static_assert(std::is_convertible<HandleT*, IHandle*>::value || std::is_null_pointer<HandleT>::value, "HandleT is not a handle?!?");
		static constexpr uint32_t id = ID;
		using handleType = HandleT;

		private:
			HandleMapping();
	};

	using Invald =			HandleMapping<0, nullptr_t>;
	using Lock = 			HandleMapping<1, GenericHandle<ILock*>>;
	using File = 			HandleMapping<2, IFileHandle>;
	using Directory = 		HandleMapping<3, IDirectoryHandle>;
	using Thread = 			HandleMapping<4, GenericHandle<WeakThreadRef>>;
	using MemoryMapping = 	HandleMapping<5, GenericHandle<uint64_t>>;
	using SHMSpace =		HandleMapping<6, GenericHandle<uint64_t>>;
	using SHMMapping =		HandleMapping<7, GenericHandle<uint64_t>>;
	using Atom =			HandleMapping<8, GenericHandle<IAtom*>>;
	using Wait = 			HandleMapping<9, GenericHandle<WaitList*>>;
	using AtomWait =		HandleMapping<10, GenericHandle<WaitOptions*>>;
	using MessageRecive	=	HandleMapping<11, IMessageRecieveHandle>;
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

enum class HandleDependencyCheckResult{
	Present, Absent, NotAvailable
};

#endif