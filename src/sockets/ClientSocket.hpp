#pragma once

#include "Socket.hpp"

class ClientSocket
{
public:
	ClientSocket(int p_iSocketFd);
	ClientSocket();
	~ClientSocket();

	void Send(const std::string &message);
	std::string Recieve();
	bool Connect(int p_iPortNumber, const char *p_pIPAddress);
	void Close();

private:
	Socket m_oSocket;
};