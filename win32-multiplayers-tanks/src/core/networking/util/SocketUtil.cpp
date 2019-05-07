#include "SocketUtil.h"
#include <iostream>

namespace net {
namespace util {

	void SocketUtil::Error(const char* message, int code)
	{
		std::cout << "Socket error: " << message << " : code " << code << std::endl;
	}

	void SocketUtil::Log(const char* message)
	{
		std::cout << "Log info: " << message << std::endl;
	}

	void SocketUtil::PrintAddress(const SocketAddress* addr)
	{
		char ip[INET_ADDRSTRLEN];
		int port = ntohs(addr->getAddressIpv4()->sin_port);
		inet_ntop(AF_INET, &(addr->getAddressIpv4()->sin_addr), ip, INET_ADDRSTRLEN);
		std::cout << "Ip: " << ip << ", port: " << port << std::endl;
	}
}}