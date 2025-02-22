#include "ReceptionThread.hpp"
#include "ActiveSocket.hpp"

#include <memory>

#define MAX_CONNECTIONS -1

ReceptionThread::ReceptionThread(uint32_t p_ui32PortNumber)
    : m_oSocket(p_ui32PortNumber, MAX_CONNECTIONS),
      m_oThread(std::bind(&ReceptionThread::ConnectionHandler, this))
{
}

void ReceptionThread::Start()
{
  m_oThread.Start();
}

void ReceptionThread::ConnectionHandler()
{
  while (m_oThread.isRunning())
  {
    std::shared_ptr<ActiveSocket> newConnection = m_oSocket.Accept();
    ProcessConnection(newConnection);
  }
}