#pragma once
#include "../core.h"

namespace core { namespace memory { namespace allocator {
	
	// returns address aligned
	void* AlignForward(void* address, uint8_t alignment);
	// returns the number of bytes needed to align the address
	uint8_t GetAdjustment(const void* address, uint8_t alignment);
	uint8_t  GetAdjustment(const void* address, uint8_t  alignment, uint8_t  extra);

	class IAllocator
	{
	protected:

		const size_t m_MemorySize;
		const void*	m_MemoryFirstAddress;

		size_t m_MemoryUsed;
		uint64_t m_MemoryAllocations;

		IAllocator(const size_t memSize, const void* mem);
		virtual ~IAllocator();

	public:
		virtual void* allocate(size_t size, uint8_t alignment) = 0;
		virtual void free(void* p) = 0;
		virtual void clear() = 0;

		inline size_t GetMemorySize() const
		{
			return this->m_MemorySize;
		}

		inline const void* GetMemoryAddress0() const
		{
			return this->m_MemoryFirstAddress;
		}

		inline size_t GetUsedMemory() const
		{
			return this->m_MemoryUsed;
		}

		inline uint64_t GetAllocationCount() const
		{
			return this->m_MemoryAllocations;
		}

	};



}}}