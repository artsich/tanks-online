#include "IAllocator.h"

namespace core { namespace memory { namespace allocator {

	void* AlignForward(void* address, uint8_t alignment)
	{
		return (void*)
			((reinterpret_cast<uintptr_t>(address) +
				static_cast<uintptr_t>(alignment - 1)) &
				static_cast<uintptr_t>(~(alignment - 1)));
	}

	// returns the number of bytes needed to align the address
	uint8_t GetAdjustment(const void* address, uint8_t alignment)
	{
		uint8_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address)& static_cast<uintptr_t>(alignment - 1));

		return adjustment == alignment ? 0 : adjustment;
	}

	uint8_t  GetAdjustment(const void* address, uint8_t  alignment, uint8_t  extra)
	{
		uint8_t  adjustment = GetAdjustment(address, alignment);

		uint8_t  neededSpace = extra;

		if (adjustment < neededSpace)
		{
			neededSpace -= adjustment;

			//Increase adjustment to fit header
			adjustment += alignment * (neededSpace / alignment);

			if (neededSpace % alignment > 0)
				adjustment += alignment;
		}

		return adjustment;
	}

} } }