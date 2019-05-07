#pragma once
#include <WinSock2.h>
#include "AbstractSocket.h"
#include "../SocketAddress.h"

namespace net
{
	class UdpSocket : public AbstractSocket
	{
	public: 
		UdpSocket();
		~UdpSocket();
		
		int SendTo(const SocketAddress* inTo, const char* data, unsigned short size);
		int ReceiveFrom(char* data, int& size, SocketAddress* outFrom);
	};
}