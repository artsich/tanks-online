#pragma once

#include <Windows.h>

namespace core {

	class Timer
	{
	private:
		LARGE_INTEGER start;
		double frequency;

	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			this->frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&start);
		}

		void reset()
		{
			QueryPerformanceCounter(&start);
		}

		float elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned _int64 cycles = current.QuadPart - start.QuadPart;
			return (float)(cycles * frequency);
		}
	};
}