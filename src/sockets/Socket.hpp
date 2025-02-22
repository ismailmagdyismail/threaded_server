#pragma once

#include <string>

class Socket
{
public:
  std::string Recieve(int p_iSocketFd);
  void Send(int p_iSocketFd, const std::string &message);
  int m_iSocketFd;
};