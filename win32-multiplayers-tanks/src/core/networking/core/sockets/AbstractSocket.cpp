#include "AbstractSocket.h"

namespace net
{
	AbstractSocket::AbstractSocket(AddressFamily af, SocketType st, ProtocolType pt)
	{
		_socket = socket(af, st, pt);
	}

	AbstractSocket::AbstractSocket(SOCKET socket) : _socket(socket) { }

	AbstractSocket::~AbstractSocket()
	{
		closesocket(_socket);
	}

	void AbstractSocket::SetNonBlockingMode(bool flag)
	{
		u_long args = flag;
		int result = ioctlsocket(_socket, 0, &args);
		if (result == SOCKET_ERROR)
		{
		//	util::SocketUtil::Error("set block/non-block method()", WSAGetLastError());
		}
	}

	int AbstractSocket::Bind(const SocketAddress* address)
	{
		int result = bind(_socket, address->getAddress(), address->getSize());
		if (result == SOCKET_ERROR)
		{
			//util::SocketUtil::Error("method bind()", WSAGetLastError());
		}
		return result;
	}
	



	fd_set* FillSetFromVector(fd_set& outSet, const std::vector<AbstractSocket*>* inSockets)
	{
		if (inSockets)
		{
			FD_ZERO(&outSet);

			for (auto& socket : *inSockets)
			{
				FD_SET(socket->_socket, &outSet);
			}
			return &outSet;
		}
		else
		{
			return nullptr;
		}
	}

	void FillVectorFromSet(
		std::vector<AbstractSocket*>* outSockets,  
		const std::vector<AbstractSocket*>* inSockets, 
		const fd_set* inSet)
	{
		if (inSet && outSockets)
		{
			outSockets->clear();
			outSockets->resize(inSet->fd_count);
			for (AbstractSocket* socket : *inSockets)
			{
				if (FD_ISSET(socket->_socket, inSet)) 
				{
					outSockets->push_back(socket);
				}
			}
		}
	}

	int AbstractSocket::Select(
		const std::vector<AbstractSocket*>* inReadSet,
		std::vector<AbstractSocket*>* outReadSet,
		const std::vector<AbstractSocket*>* inWriteSet,
		std::vector<AbstractSocket*>* outWriteSet,
		const std::vector<AbstractSocket*>* inErrorSet,
		std::vector<AbstractSocket*>* outErrorSet)
	{
		fd_set read, write, except;

		fd_set* readable = FillSetFromVector(read, inReadSet);
		fd_set* writable = FillSetFromVector(write, inWriteSet);
		fd_set* exceptable = FillSetFromVector(except, inErrorSet);

		int selectedSockets = select(0, readable, writable, exceptable, nullptr);

		if (selectedSockets > 0)
		{
			FillVectorFromSet(outReadSet, inReadSet, readable);
			FillVectorFromSet(outWriteSet, inWriteSet, writable);
			FillVectorFromSet(outErrorSet, inErrorSet, exceptable);
		}

		return selectedSockets;
	}
}