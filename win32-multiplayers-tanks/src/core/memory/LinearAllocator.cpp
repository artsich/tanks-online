#include "LinearAllocator.h"

namespace core { namespace memory {

	LinearAllocator::LinearAllocator(void* Memory, u64 MemorySize):
		IAllocator(Memory, MemorySize)
	{
	}

	LinearAllocator::~LinearAllocator()
	{
		Clear();
	}

	//TODO: AsU32Ptr - u32 , needmemory = u64
	void* LinearAllocator::Allocate(u64 NeedMemory, u8 Alignment)
	{
		Assert(NeedMemory <= 0 && "allocate called with memSize = 0.");

		union
		{
			void* AsVoidPtr;
			u32* AsU32Ptr;
		};

		AsVoidPtr = (void*)MemoryFirstAddress;
		AsU32Ptr += AllocatedMemory;

		u8 Adjustment = GetAdjustment(AsVoidPtr, Alignment);

		if (AllocatedMemory + NeedMemory + Adjustment > MemorySize)
		{
			return nullptr;
		}

		AsU32Ptr += Adjustment;
		AllocatedMemory += NeedMemory + Adjustment;
		MemoryAllocations++;

		return AsVoidPtr;
	}

	void LinearAllocator::Free(void* Address)
	{
		Assert(false && "Lineaer allocators do not support free operations. Use clear instead.");
	}

	void LinearAllocator::Clear()
	{
		AllocatedMemory = 0;
		MemoryAllocations = 0;
	}
}}