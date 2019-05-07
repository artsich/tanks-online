#pragma once
#include "../core.h"

#define KB(x) (x     * 1024)
#define MB(x) (KB(x) * 1024)
#define GB(x) (MB(x) * 1024)

#ifdef WIN32
	#define DEFAULT_ALIGNMENT_OF_MEMORY 4
#elif WIN64
	#define DEFAULT_ALIGNMENT_OF_MEMORY 8
#endif

namespace core { namespace memory {

	// returns address aligned
	void* AlignForward(void* address, u8 alignment);

	// returns the number of bytes needed to align the address
	u8 GetAdjustment(void* address, u8 alignment);
	u8 GetAdjustment(void* address, u8 alignment, u8 extra);

	class IAllocator
	{
	public:
		const u64 MemorySize;
		const void*	MemoryFirstAddress;

		u64 AllocatedMemory;
		u64 MemoryAllocations;

		IAllocator(void* Memory, u64 MemorySize);
		virtual ~IAllocator();

		virtual void* Allocate(u64 size, u8 alignment) = 0;
		virtual void Free(void* p) = 0;
		virtual void Clear() = 0;

		friend void DEBUGPrintMemoryStatus(IAllocator* Memory);
	};

}}