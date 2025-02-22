//! ActiveSocket Wrapper
#include "ActiveSocket.hpp"
#include "Socket.hpp"

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <cstring>

#define TCP 0

ActiveSocket::ActiveSocket()
{
  m_oSocket.m_iSocketFd = socket(AF_INET, SOCK_STREAM, TCP);
}

ActiveSocket::ActiveSocket(int p_iSocketFd)
{
  m_oSocket.m_iSocketFd = p_iSocketFd;
}

bool ActiveSocket::Connect(int p_iPortNumber, const char *p_pIPAddress)
{
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(p_iPortNumber);
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  int iStatus = connect(m_oSocket.m_iSocketFd, (sockaddr *)&address, sizeof address);
  return (-1 != iStatus);
}

void ActiveSocket::Send(const std::string &message)
{
  m_oSocket.Send(m_oSocket.m_iSocketFd, message);
}

std::string ActiveSocket::Recieve()
{
  return m_oSocket.Recieve(m_oSocket.m_iSocketFd);
}

void ActiveSocket::Close()
{
  close(m_oSocket.m_iSocketFd);
}

ActiveSocket::~ActiveSocket()
{
  Close();
}