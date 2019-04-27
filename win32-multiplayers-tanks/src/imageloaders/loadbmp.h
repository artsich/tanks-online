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
}