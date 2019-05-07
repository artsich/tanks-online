#pragma once
#include <stdio.h>
#include <WinSock2.h>
#include "../util/SocketUtil.h"

namespace core { namespace net {
		
	void initSocketApi();
	void closeSocketApi();
} }