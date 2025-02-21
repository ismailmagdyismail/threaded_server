//! ClientSocket Wrapper
#include "sockets/ClientSocket.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <cstring>

#define TCP 0

ClientSocket::ClientSocket()
{
  m_iSocketFd = socket(AF_INET, SOCK_STREAM, TCP);
}

ClientSocket::ClientSocket(int p_iSocketFd)
{
  m_iSocketFd = p_iSocketFd;
}

bool ClientSocket::Connect(int p_iPortNumber, const char *p_pIPAddress)
{
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(p_iPortNumber);
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  int iStatus = connect(m_iSocketFd, (sockaddr *)&address, sizeof address);
  return (-1 != iStatus);
}

void ClientSocket::Close()
{
  close(m_iSocketFd);
}

ClientSocket::~ClientSocket()
{
  Close();
}