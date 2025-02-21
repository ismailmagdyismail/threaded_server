#pragma once

#include <iostream>

class ServerSocket
{
public:
	ServerSocket(uint16_t p_ui16PortNumber, int p_iMaxNumberOfConnections);
	~ServerSocket();

	int Accept();
	void Close();

private:
	bool Bind();
	bool Listen();

	int m_iSocketFd;
	int m_iMaxConnections;
	uint16_t m_ui16PortNumber;
};