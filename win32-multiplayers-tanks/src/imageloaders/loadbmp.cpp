#include "loadbmp.h"

namespace core
{
	static bitmap_header* loadbmp_header(const char* filePath)
	{
		bitmap_header* header = { 0 };

		uint8_t* content = (uint8_t*)core::syncio::read_file(filePath);

		if (content)
		{
			header = (bitmap_header*)content;
		}
		return header;
	}

	BmpImage::BmpImage(const char* filePath)
	{
		this->filePath = filePath;
	}

	BmpImage ::~BmpImage()
	{
		release();
	}

	uint8_t* BmpImage::getPixels()
	{
		if (!header)
		{
			header = loadbmp_header(filePath);
			if (!header)
			{
				return NULL;
			}
		}

		return ((uint8_t*)header) + header->BitmapOffset;
	}

	const bitmap_header* BmpImage::getBitmapHeader()
	{
		if (!header)
		{
			header = loadbmp_header(filePath);
			if (!header)
			{
				return NULL;
			}
		}

		return header;
	}

	void BmpImage::release()
	{
		core::syncio::free_file_memory(header);
	}
}