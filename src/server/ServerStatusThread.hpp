#pragma once

#include "ReceptionThread.hpp"
#include "ThreadPool.hpp"
#include "PassiveSocket.hpp"
#include "ConnectionsManager.hpp"

class ServerStatusThread final : public ReceptionThread
{
public:
  ServerStatusThread(uint32_t p_ui32PortNumber, std::string &&p_strSocketName, ThreadPool &p_oThreadPool, ConnectionsManager &p_oConnectionsManager);
  virtual void ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection) override;

private:
  ThreadPool &m_oThreadPool;
  ConnectionsManager &m_oConnectionManager;
};