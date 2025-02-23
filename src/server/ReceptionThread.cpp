#include "ReceptionThread.hpp"
#include "ActiveSocket.hpp"

#include <memory>

#define MAX_CONNECTIONS -1

ReceptionThread::ReceptionThread(uint32_t p_ui32PortNumber, std::string &&p_strSocketName)
    : m_oSocket(p_ui32PortNumber, MAX_CONNECTIONS),
      m_oThread(std::bind(&ReceptionThread::ConnectionHandler, this)),
      m_strSocketName(std::move(p_strSocketName))
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
    std::cout << "[Server-" << m_strSocketName << "-NewConnection]" << std::endl;
    ProcessConnection(newConnection);
  }
}