#pragma once

#include <string>
#include <functional>
#include <atomic>

class Socket
{
public:
  // Socket(std::function<void(void)> p_fDisconnectCallback);
  std::string Recieve(int p_iSocketFd);
  void Send(int p_iSocketFd, const std::string &message);
  int m_iSocketFd;
  void Close();

private:
  std::function<void(void)> m_fDisconnectCallback;
};