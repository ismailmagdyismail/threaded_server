#include "SocketReceptionThread.hpp"
#include "ActiveSocket.hpp"

#include <memory>

#define MAX_CONNECTIONS -1

SocketReceptionThread::SocketReceptionThread(uint32_t p_ui32PortNumber)
    : m_oSocket(p_ui32PortNumber, MAX_CONNECTIONS),
      m_oThread(std::bind(&SocketReceptionThread::ConnectionHandler, this))
{
}

void SocketReceptionThread::Start()
{
  m_oThread.Start();
}

void SocketReceptionThread::ConnectionHandler()
{
  while (m_oThread.isRunning())
  {
    std::shared_ptr<ActiveSocket> newConnection = m_oSocket.Accept();
  }
}