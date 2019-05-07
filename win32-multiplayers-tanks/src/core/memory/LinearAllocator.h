#pragma once

#include "IAllocator.h"

namespace core { namespace memory {

	class LinearAllocator : public IAllocator
	{
	public:
		LinearAllocator(void* Memory, u64 MemorySize);
		~LinearAllocator();

		virtual void* Allocate(u64 NeedMemory, u8 Alignment) override;
		virtual void Free(void* Address) override;
		virtual void Clear() override;
	};

} } 