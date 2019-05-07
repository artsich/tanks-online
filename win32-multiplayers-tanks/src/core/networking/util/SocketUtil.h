#pragma once

#include "../core/SocketAddress.h"

namespace net { 
namespace util {

#define abstract

	class SocketUtil
	{
	public: 
		static void Error(const char* message, int code);
		static void Log(const char* message);
		static void PrintAddress(const SocketAddress* addr);
	};
}}