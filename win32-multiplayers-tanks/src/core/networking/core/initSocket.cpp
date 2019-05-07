#include "initSocket.h"

namespace coere { namespace net {

	void initSocketApi()
	{
#if defined(_WIN32)
		WSAData wsaData;
		int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("Init socket api", WSAGetLastError());
			return;
		}

		//util::SocketUtil::Log("Socket api init");
#endif
	}

	void closeSocketApi()
	{
#if defined(_WIN32)
		WSACleanup();
#endif
		//util::SocketUtil::Log("Socket api cleanup..");
	}
}}