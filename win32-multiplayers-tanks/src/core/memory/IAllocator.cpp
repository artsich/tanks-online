#include "IAllocator.h"
#ifdef DEBUG
#include <iostream>
#endif

namespace core { namespace memory { 

	void* AlignForward(void* address, u8 alignment)
	{
		return (void*)
			((reinterpret_cast<uintptr_t>(address) +
				static_cast<uintptr_t>(alignment - 1)) &
				static_cast<uintptr_t>(~(alignment - 1)));
	}

	u8 GetAdjustment(void* address, u8 alignment)
	{
		u8 adjustment = alignment - (reinterpret_cast<uintptr_t>(address)& static_cast<uintptr_t>(alignment - 1));

		return adjustment == alignment ? 0 : adjustment;
	}

	u8  GetAdjustment(void* Address, u8  Alignment, u8  Offset)
	{
		u8  Adjustment = GetAdjustment(Address, Alignment);
		u8  NeededSpace = Offset;

		if (Adjustment < NeededSpace)
		{
			NeededSpace -= Adjustment;

			//Increase adjustment to fit header
			Adjustment += Alignment * (NeededSpace / Alignment);

			if (NeededSpace % Alignment > 0)
				Adjustment += Alignment;
		}

		return Adjustment;
	}

	IAllocator::IAllocator(void* Memory, const u64 MemorySize) :
		MemorySize(MemorySize),
		MemoryFirstAddress(Memory)
	{
	}

	IAllocator::~IAllocator()
	{
	}


	void DEBUGPrintMemoryStatus(IAllocator* Memory)
	{
		std::cout << "---------MEMORY DEBUG---------" << std::endl;
		std::cout << "Allocated: " << Memory->AllocatedMemory << std::endl;
		std::cout << "MemorySize: " << Memory->MemorySize << std::endl;
		std::cout << "Poiner: " << Memory->MemoryFirstAddress << std::endl;
		std::cout << "---------MEMORY DEBUG---------" << std::endl;
	}

} }