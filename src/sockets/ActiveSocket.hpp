#pragma once

#include "Socket.hpp"

class ActiveSocket
{
public:
	ActiveSocket(int p_iSocketFd);
	ActiveSocket();
	~ActiveSocket();

	void Send(const std::string &message);
	std::string Recieve();
	bool Connect(int p_iPortNumber, const char *p_pIPAddress);
	void Close();

private:
	Socket m_oSocket;
};