#pragma once
#include <stdint.h>
#include <stdlib.h>

namespace core {

#define DEBUG true

#define ArrayCount(Array) (sizeof(Array) / sizeof(Array[0]))

#if DEBUG
#define Assert(Expression) if(!(Expression)) { *(int*)0 = 0; }
#else 
	Assert(Expression)
#endif

}
