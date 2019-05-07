#pragma once
#define FD_SETSIZE 1000

#include <vector>
#include "../../util/SocketUtil.h"
#include "../SocketAddress.h"

namespace net
{
	enum AddressFamily
	{
		IPV4 = AF_INET,
		IPV6 = AF_INET6
	};

	enum SocketType
	{
		STREAM,
		DGRAM
	};

	enum ProtocolType
	{
		TCP = IPPROTO_TCP,
		UDP = IPPROTO_UDP
	};

	abstract class AbstractSocket
	{
	protected: 
		SOCKET _socket;

		friend static fd_set* FillSetFromVector(fd_set& outSet, const std::vector<AbstractSocket*>* inSockets);
		friend static 	void FillVectorFromSet(
			std::vector<AbstractSocket*>* outSockets, 
			const std::vector<AbstractSocket*>* inSockets, 
			const fd_set* inSet);

	public:

		AbstractSocket(AddressFamily af, SocketType st, ProtocolType pt);
		AbstractSocket(SOCKET socket);
		~AbstractSocket();

		void SetNonBlockingMode(bool flag);
		int Bind(const SocketAddress* address);

		static int Select(
			const std::vector<AbstractSocket*>* inReadSet,
			std::vector<AbstractSocket*>* outReadSet,
			const std::vector<AbstractSocket*>* inWriteSet,
			std::vector<AbstractSocket*>* outWriteSet,
			const std::vector<AbstractSocket*>* inErrorSet,
			std::vector<AbstractSocket*>* outErrorSet);
	};
}