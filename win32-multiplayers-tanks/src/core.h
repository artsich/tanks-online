#pragma once
#include <stdint.h>
#include <stdlib.h>

namespace core {

#define DEBUG true

#if DEBUG
#define Assert(Expression) if(!(Expression)) { *(int*)0 = 0; }
#else 
	Assert(Expression)
#endif

}
