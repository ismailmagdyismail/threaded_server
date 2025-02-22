#pragma once

#include "Socket.hpp"

#include <iostream>

class ServerSocket
{
public:
	ServerSocket(uint16_t p_ui16PortNumber, int p_iMaxNumberOfConnections);
	~ServerSocket();

	void Send(int p_iSocketFd, const std::string &message);
	std::string Recieve(int p_iSocketFd);
	int Accept();
	void Close();

private:
	bool Bind();
	bool Listen();

	int m_iMaxConnections;
	uint16_t m_ui16PortNumber;
	Socket m_oSocket;
};