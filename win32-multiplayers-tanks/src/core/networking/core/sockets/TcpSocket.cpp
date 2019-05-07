#include "TcpSocket.h"

namespace net
{
	TcpSocket::TcpSocket() : AbstractSocket(IPV4, STREAM, TCP)
	{
	}

	TcpSocket::TcpSocket(SOCKET socket) : AbstractSocket(socket) { }

	TcpSocket::~TcpSocket()
	{}

	void TcpSocket::Connect(const SocketAddress* address)
	{
		int result = connect(_socket, address->getAddress(), address->getSize());
		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method connect()", WSAGetLastError());
		}
	}
	
	void TcpSocket::Listen()
	{
		int result = listen(_socket, BAC_LOG);
		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method listen()", WSAGetLastError());
		}
	}
	
	//If you user Accept, need delete (TcpSocket) 
	TcpSocket* TcpSocket::Accept()
	{
		SocketAddress remoteAddress;
		int len = remoteAddress.getSize();
		SOCKET clientSocket = accept(_socket, remoteAddress.getAddress(), &len);

		if (clientSocket == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method accept()", WSAGetLastError());
			return nullptr;
		}

		//TODO: AAAAAAA pointer -> memory leak nonononon
		TcpSocket* result = new TcpSocket(clientSocket);
		result->remoteAddress = remoteAddress;

		return result;
	}
	
	int TcpSocket::Send(const char* data, const int& size)
	{
		int result = send(_socket, data, size, 0);
		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method send()", WSAGetLastError());
		}
		return result;
	}
	
	int TcpSocket::Recieve(char* data, int& size)
	{
		int result = recv(_socket, data, size, 0);
		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method recv()", WSAGetLastError());
		}
		return result;
	}
}