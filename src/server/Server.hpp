#pragma once

//! system includes
#include <memory>
#include <mutex>
#include <atomic>

#include "PassiveSocket.hpp"
#include "AckReceptionThread.hpp"
#include "ServerStatusThread.hpp"
#include "ConnectionsManager.hpp"

class Server
{
public:
  static std::shared_ptr<Server> Instance();
  void Start();
  bool IsRunning();

  ~Server();

private:
  Server();
  AckReceptionThread m_oAckReceptionThread;
  ServerStatusThread m_oServerStatusReceptionThread;
  std::atomic<bool> m_bIsRunning{false};
  ThreadPool m_oThreadPool;
  ConnectionsManager m_oConnectionsManager;
};