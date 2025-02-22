#pragma once

#include "Thread.hpp"
#include "PassiveSocket.hpp"

#include <functional>

class SocketReceptionThread
{
public:
  SocketReceptionThread(uint32_t p_ui32PortNumber);
  void Start();
  void ConnectionHandler();

private:
  Thread m_oThread;
  PassiveSocket m_oSocket;
};