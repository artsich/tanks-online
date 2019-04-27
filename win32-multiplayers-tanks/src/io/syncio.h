#pragma once
#include "../core.h"

namespace core { namespace syncio {

	void* read_file(const char* filePath);
	bool write_file(const char* fileName, uint32_t memorySize, const void* memory);
	void free_file_memory(void* Memory);

}}