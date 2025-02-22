

//! PassiveSocket Wrapper
#include "PassiveSocket.hpp"

//! socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define TCP 0

PassiveSocket::PassiveSocket(uint16_t p_ui16PortNumber, int p_iMaxConnections) : m_ui16PortNumber(p_ui16PortNumber), m_iMaxConnections(p_iMaxConnections)
{
	m_oSocket.m_iSocketFd = socket(AF_INET, SOCK_STREAM, TCP);
	if (-1 == m_oSocket.m_iSocketFd)
	{
		std::cerr << "Error opening socket " << std::endl;
	}
	bool bBindStatus = Bind();
	if (!bBindStatus)
	{
		std::cerr << "Error in binding to PORT " << m_ui16PortNumber << '\n';
	}
	bool bListenStatus = Listen();
	if (!bListenStatus)
	{
		std::cerr << "Error in listening on socket \n";
	}
}

bool PassiveSocket::Bind()
{
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(m_ui16PortNumber);
	address.sin_addr.s_addr = INADDR_ANY;
	int errorCode = bind(m_oSocket.m_iSocketFd, (sockaddr *)&address, sizeof address);
	return (-1 != errorCode);
}

bool PassiveSocket::Listen()
{
	int ierrorCode = listen(m_oSocket.m_iSocketFd, m_iMaxConnections);
	return (-1 != ierrorCode);
}

std::shared_ptr<ActiveSocket> PassiveSocket::Accept()
{
	sockaddr_in clientAddress;
	uint32_t ui32Size = sizeof(clientAddress);
	int iClientFd = accept(m_oSocket.m_iSocketFd, (sockaddr *)&clientAddress, &ui32Size);
	return std::make_shared<ActiveSocket>(iClientFd);
}

void PassiveSocket::Close()
{
	m_oSocket.Close();
}

PassiveSocket::~PassiveSocket()
{
	Close();
}