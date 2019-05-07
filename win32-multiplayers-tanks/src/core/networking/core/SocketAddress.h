#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>

namespace net
{
	class SocketAddress
	{
	protected:
		sockaddr address;	
	
		void init(unsigned long inAddress, unsigned short inPort);

	public:

		SocketAddress() = default;
		SocketAddress(unsigned long inAddress, unsigned short inPort);
		SocketAddress(const char* inStrAddress, unsigned short inPort);
		SocketAddress(const sockaddr* addr);

		sockaddr_in* getAddressIpv4() const { return (sockaddr_in*)&address; }
		sockaddr* getAddress() const { return (sockaddr*) &address; }
		int getSize() const { return sizeof(sockaddr); }
	};
}