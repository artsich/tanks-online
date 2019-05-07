#include "StackAllocator.h"

namespace core { namespace memory {

	StackAllocator::StackAllocator(void* Memory, u64  MemorySize) :
		IAllocator(Memory, MemorySize)
	{}

	StackAllocator::~StackAllocator()
	{
		Clear();
	}

	void* StackAllocator::Allocate(u64 NeedMemory, u8 Alignment)
	{
		Assert(NeedMemory > 0 && "allocate called with memSize = 0.");

		union
		{
			void* AsVoidPtr;
			u32* AsU32Ptr;
			AllocMetaInfo* AsMeta;
		};

		AsVoidPtr = (void*)this->MemoryFirstAddress;
		AsU32Ptr += AllocatedMemory;

		u8 Adjustment = GetAdjustment(AsVoidPtr, Alignment, sizeof(AllocMetaInfo));

		if (AllocatedMemory + NeedMemory + Adjustment > MemorySize)
		{
			return nullptr;
		}

		AsMeta->Adjustment = Adjustment;
		AsU32Ptr += Adjustment;

		AllocatedMemory += NeedMemory + Adjustment;
		MemoryAllocations++;

		return AsVoidPtr;
	}

	void StackAllocator::Free(void* DeletingAddress)
	{
		union
		{
			void* AsVoidPtr;
			u32* AsU32Ptr;
			AllocMetaInfo* AsMeta;
		};

		AsVoidPtr = DeletingAddress;
		AsU32Ptr -= sizeof(AllocMetaInfo);
		AllocatedMemory -= ((u32*)MemoryFirstAddress + AllocatedMemory) -
							((u32*)DeletingAddress + AsMeta->Adjustment);

		MemoryAllocations--;
	}

	void StackAllocator::Clear()
	{
		AllocatedMemory = 0;
		MemoryAllocations = 0;
	}
} }