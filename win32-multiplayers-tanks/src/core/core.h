#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <algorithm>

#define DEBUG true

#define ArrayCount(Array) (sizeof(Array) / sizeof(Array[0]))

#if DEBUG
#define Assert(Expression) if(Expression) { *(int*)0 = 0; }
#else 
Assert(Expression)
#endif

typedef float       f32;

typedef long long   i64;
typedef int			i32;
typedef short       i16;
typedef char        i8;

typedef long long   s64;
typedef int			s32;
typedef short       s16;
typedef char        s8;

typedef unsigned long long  u64;
typedef unsigned int        u32;
typedef unsigned short      u16;
typedef unsigned char       u8;

using TypeId = u32 ;
using ObjectId = u32 ;

namespace core 
{
	struct screen_buffer 
	{
		int Width;
		int Height;
		int BytesPerPixel;
		int Pitch;
		void* Memory;
	};

	struct game_memory
	{
		u64 SizeMemory;
		void* Memory;
	};
}