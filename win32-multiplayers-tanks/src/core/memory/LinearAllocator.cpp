#include "LinearAllocator.h"

namespace core { namespace memory { namespace allocator {

	LinearAllocator::LinearAllocator(size_t memSize, const void* mem) :
		IAllocator(memSize, mem)
	{}

	LinearAllocator::~LinearAllocator()
	{
		this->clear();
	}

	void* LinearAllocator::allocate(size_t memSize, uint8_t alignment)
	{
		Assert(memSize > 0 && "allocate called with memSize = 0.");

		union
		{
			void* asVoidPtr;
			uintptr_t asUptr;
		};

		asVoidPtr = (void*)this->m_MemoryFirstAddress;

		// current address
		asUptr += this->m_MemoryUsed;

		// get adjustment to align address
		uint8_t adjustment = GetAdjustment(asVoidPtr, alignment);

		// check if there is enough memory available
		if (this->m_MemoryUsed + memSize + adjustment > this->m_MemorySize)
		{
			// not enough memory
			return nullptr;
		}

		// determine aligned memory address
		asUptr += adjustment;

		// update book keeping
		this->m_MemoryUsed += memSize + adjustment;
		this->m_MemoryAllocations++;

		// return aligned memory address
		return asVoidPtr;
	}

	void LinearAllocator::free(void* mem)
	{
		Assert(false && "Lineaer allocators do not support free operations. Use clear instead.");
	}

	void LinearAllocator::clear()
	{
		// simply reset memory
		this->m_MemoryUsed = 0;
		this->m_MemoryAllocations = 0;
	}

}}}