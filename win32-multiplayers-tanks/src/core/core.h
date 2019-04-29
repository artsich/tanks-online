#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>

namespace core {

#define DEBUG true

#define ArrayCount(Array) (sizeof(Array) / sizeof(Array[0]))

#if DEBUG
#define Assert(Expression) if(!(Expression)) { *(int*)0 = 0; }
#else 
	Assert(Expression)
#endif

	struct screen_buffer 
	{
		int Width;
		int Height;
		int BytesPerPixel;
		int Pitch;
		void* Memory;
	};
	
	using TypeID = uint32_t;
	using ObjectID = uint32_t;

	using EntityId = TypeID;
	using EntityTypeId = uint32_t;

	using ComponentId = TypeID;
	using ComponentTypeId = uint32_t;

	using SystemTypeId = TypeID;

	static const ObjectID	INVALID_OBJECT_ID = std::numeric_limits<ObjectID>::max();
	static const TypeID		INVALID_TYPE_ID = std::numeric_limits<TypeID>::max();

}