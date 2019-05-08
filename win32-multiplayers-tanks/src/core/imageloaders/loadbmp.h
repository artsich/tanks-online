#pragma once

#include <Windows.h>

#include "IImageLoader.h"
#include "../io/syncio.h"

namespace core
{
#pragma pack(push, 1)
	struct bitmap_header
	{
		WORD  FileType;     
		DWORD FileSize;     
		WORD  Reserved1;    
		WORD  Reserved2;    
		DWORD BitmapOffset; 
		DWORD Size;          
		LONG  Width;           
		LONG  Height;          
		WORD  Planes;          
		WORD  BitsPerPixel;
	};
#pragma pack(pop)
	 
	class BmpImage : public IImageLoader
	{
	private:
		const char* filePath;
		uint8_t* imageBuffer;
		bitmap_header* header;

	public:
		BmpImage(const char* filePath);
		~BmpImage();

		void release() override;
		uint8_t* getPixels() override;
		
		const bitmap_header* getBitmapHeader();
	};

	//core::graphics::texture* cut_texture(core::graphics::texture* source_texture, int x, int y, int w, int h)
	//{
	//	uint32_t* source_buffer = (uint32_t*)source_texture->buffer;
	//	core::graphics::texture* result = (core::graphics::texture*)malloc(sizeof(core::graphics::texture));
	//	result->width = w;
	//	result->height = h;

	//	uint32_t* result_buffer = (uint32_t*)malloc(sizeof(uint32_t)*w*h);

	//	for (int yy = y; yy < y + h; ++yy)
	//	{
	//		uint32_t next_row = x + yy * source_texture->width;
	//		uint32_t* row = (source_buffer + next_row);
	//		for (int xx = x; xx < x + w; ++xx)
	//		{
	//			*result_buffer++ = *row++;
	//		}
	//	}

	//	result->buffer = result_buffer;
	//	return result;
	//}


}