#pragma once

#include "ReceptionThread.hpp"
#include "ThreadPool.hpp"
#include "ConnectionsManager.hpp"
class AckReceptionThread : public ReceptionThread
{
public:
  AckReceptionThread(uint16_t p_ui16PortNumber, std::string &&p_strSocketName, ThreadPool &p_oThreadPool, ConnectionsManager &p_oConnectionsManager);
  virtual void ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection) override;

private:
  ThreadPool &m_oThreadPool;
  ConnectionsManager &m_oConnectionsManager;
};