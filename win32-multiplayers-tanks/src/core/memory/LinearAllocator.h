#pragma once

#include "IAllocator.h"

namespace core { namespace memory { namespace allocator {

	class LinearAllocator : public IAllocator
	{


		LinearAllocator(size_t memSize, const void* mem);
		virtual ~LinearAllocator();

	public:
		virtual void* allocate(size_t size, uint8_t alignment) override;
		virtual void free(void* p) override;
		virtual void clear() override;
	};

} } }