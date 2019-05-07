#pragma once

#include "IAllocator.h"

namespace core { namespace memory {

	class LinearAllocator : public IAllocator
	{
	public:
		LinearAllocator(u64 MemorySize, void* mem);
		virtual ~LinearAllocator();

		virtual void* Allocate(u64 NeedMemory, u8 Alignment) override;
		virtual void Free(void* Address) override;
		virtual void Clear() override;
	};

} } 