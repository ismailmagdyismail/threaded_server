#pragma once

//! system includes
#include <memory>
#include <mutex>
#include <atomic>

#include "PassiveSocket.hpp"
#include "SocketReceptionThread.hpp"

class Server
{
public:
  static std::shared_ptr<Server> Instance();
  void Start();
  bool IsRunning();

  ~Server();

private:
  Server();
  SocketReceptionThread m_oServerStatusReceptionThread;
  std::atomic<bool> m_bIsRunning{false};
};