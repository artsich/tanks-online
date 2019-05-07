#pragma once

#include <WinSock2.h>
#include "AbstractSocket.h"
#include "../../util/SocketUtil.h"
#include "../SocketAddress.h"

#define BAC_LOG 1000

namespace net
{
	class TcpSocket : public AbstractSocket
	{
	public:
		TcpSocket();
		TcpSocket(SOCKET socket);
		~TcpSocket();

		void Connect(const SocketAddress* address);
		void Listen();
		TcpSocket* Accept();
		int Send(const char* data, const int& size);
		int Recieve(char* data, int& size);

		SocketAddress remoteAddress;
	};
}