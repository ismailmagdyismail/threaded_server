#pragma once

class ClientSocket
{
public:
	ClientSocket(int p_iSocketFd);
	ClientSocket();
	~ClientSocket();

	bool Connect(int p_iPortNumber, const char *p_pIPAddress);
	void Close();

private:
	int m_iSocketFd;
};