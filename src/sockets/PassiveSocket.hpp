#pragma once

#include "Socket.hpp"
#include "ActiveSocket.hpp"

#include <iostream>

class PassiveSocket
{
public:
	PassiveSocket(uint16_t p_ui16PortNumber, int p_iMaxNumberOfConnections);
	~PassiveSocket();

	ActiveSocket Accept();
	void Close();

private:
	bool Bind();
	bool Listen();

	int m_iMaxConnections;
	uint16_t m_ui16PortNumber;
	Socket m_oSocket;
};