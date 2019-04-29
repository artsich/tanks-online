#pragma once

#include "IAllocator.h"

namespace core { namespace memory { namespace allocator {

	class StackAllocator : public IAllocator
	{
	private:

		struct AllocMetaInfo
		{
			uint8_t adjustment;
		};

	public:

		StackAllocator(size_t memSize, const void* mem);

		virtual ~StackAllocator();

		virtual void* allocate(size_t size, uint8_t alignment) override;
		virtual void free(void* p) override;
		virtual void clear() override;

	};

} } }