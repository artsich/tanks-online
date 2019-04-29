#pragma once
#include <stdint.h>

class IImageLoader
{
public:
	virtual uint8_t* getPixels() = 0;
	virtual void release() = 0;
};

