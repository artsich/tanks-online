#include "LinearAllocator.h"

namespace core { namespace memory {

	LinearAllocator::LinearAllocator(u64 MemorySize, void* Memory) :
		IAllocator(MemorySize, Memory)
	{
	}

	LinearAllocator::~LinearAllocator()
	{
		Clear();
	}

	void* LinearAllocator::Allocate(u64 NeedMemory, uint8_t Alignment)
	{
		Assert(NeedMemory > 0 && "allocate called with memSize = 0.");

		union
		{
			void* AsVoidPtr;
			u32* AsU32Ptr;
		};

		AsVoidPtr = (void*)this->MemoryFirstAddress;
		AsU32Ptr += AllocatedMemory;

		u8 Adjustment = GetAdjustment(AsVoidPtr, Alignment);

		if (AllocatedMemory + NeedMemory + Adjustment > MemorySize)
		{
			return nullptr;
		}

		//Determine aligned memory address
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