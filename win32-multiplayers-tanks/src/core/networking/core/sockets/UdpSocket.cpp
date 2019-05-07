#include "UdpSocket.h"

namespace net
{
	UdpSocket::UdpSocket() : AbstractSocket(IPV4, DGRAM, UDP)
	{
	}

	UdpSocket::~UdpSocket() { }

	int UdpSocket::SendTo(const SocketAddress* outAddress, const char* data, unsigned short size)
	{
		int result = sendto(_socket, data, size, 0, outAddress->getAddress(), outAddress->getSize());

		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method sendto()", WSAGetLastError());
		}
		return result;
	}

	int UdpSocket::ReceiveFrom(char* data, int& size, SocketAddress* outFrom)
	{
		sockaddr* addr = outFrom->getAddress();
		int lenFrom = outFrom->getSize();
		int result = recvfrom(_socket, data, size, 0, addr, &lenFrom);

		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method receiveFrom()", WSAGetLastError());
		}
		return result;
	}
}