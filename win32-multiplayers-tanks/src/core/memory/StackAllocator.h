#pragma once

#include "IAllocator.h"

namespace core { namespace memory {

	class StackAllocator : public IAllocator
	{
	private:

		struct AllocMetaInfo
		{
			u8 Adjustment;
		};

	public:

		StackAllocator(void* Memory, u64 MemorySize);

		virtual ~StackAllocator();

		virtual void* Allocate(u64 NeedMemory, u8 Alignment) override;
		virtual void Free(void* Memory) override;
		virtual void Clear() override;

	};

} }