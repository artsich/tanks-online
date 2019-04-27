#include "syncio.h"
#include <Windows.h>

namespace core { namespace syncio {

	static inline uint32_t SafeTruncateUInt64(uint64_t Value)
	{
		Assert(Value <= 0xffffffff);
		uint32_t Result = (uint32_t)Value;

		return(Result);
	}

	void* read_file(const char* filePath)
	{
		void* buffer = nullptr;
		HANDLE fileHandle = CreateFile(filePath, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		DWORD offset = 0;

		if (fileHandle != INVALID_HANDLE_VALUE)
		{
			LARGE_INTEGER fileSize;
			if (GetFileSizeEx(fileHandle, &fileSize))
			{
				DWORD bytesRead = 0;
				uint32_t fileSize32 = SafeTruncateUInt64(fileSize.QuadPart);

				buffer = VirtualAlloc(0, fileSize32 - offset, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
				ReadFile(fileHandle, buffer, fileSize32, &bytesRead, 0);

				Assert(fileSize32 == bytesRead);
			}
		}

		CloseHandle(fileHandle);
		return (buffer);
	}

	bool write_file(const char* fileName, uint32_t memorySize, const void* memory)
	{
		HANDLE fileHandle = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		BOOL result = false;

		if (fileHandle)
		{
			DWORD bytesWritten = 0;
			if (WriteFile(fileHandle, memory, memorySize, &bytesWritten, 0))
			{
				result = (bytesWritten == memorySize);
			}
		}

		CloseHandle(fileHandle);
		return result;
	}

	void free_file_memory(void* Memory)
	{
		if (Memory)
		{
			VirtualFree(Memory, 0, MEM_RELEASE);
		}
	}
}}