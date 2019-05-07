#include "SocketAddress.h"
#include "../util/SocketUtil.h"

namespace net
{
	SocketAddress::SocketAddress(const sockaddr* addr)
	{
		memcpy(&address, addr, sizeof(sockaddr));
	}

	SocketAddress::SocketAddress(unsigned long inAddress, unsigned short inPort)
	{
		inAddress = htonl(inAddress);
		init(inAddress, inPort);
	}

	SocketAddress::SocketAddress(const char* inStrAddress, unsigned short inPort)
	{
		unsigned long inAddress;
		int result = InetPton(AF_INET, inStrAddress, &inAddress);

		if (result != 1)
		{
			util::SocketUtil::Error("method InnetPton()", WSAGetLastError());
		}
		else
		{
			init(inAddress, inPort);
		}
	}

	void SocketAddress::init(unsigned long inAddress, unsigned short inPort)
	{
		sockaddr_in* addr = (sockaddr_in*)&address;
		*addr = { 0 };
		addr->sin_family = AF_INET;
		addr->sin_addr.S_un.S_addr = inAddress;
		addr->sin_port = htons(inPort);
	}
}