#pragma once

#include <ActiveSocket.hpp>

#include <atomic>
#include <unordered_map>
#include <memory>
#include <mutex>

class ConnectionsManager
{
public:
  int RegisterNewConnection(const std::shared_ptr<ActiveSocket> &p_pNewConnection)
  {
    std::lock_guard<std::mutex> lock{m_oRegisteredConnectionsMutex};
    int iNextId = GetNextId();
    m_oRegisteredConnections.insert({iNextId, p_pNewConnection});
    return iNextId;
  }

private:
  int GetNextId()
  {
    m_iNextAvailableId++;
    return m_iNextAvailableId;
  }

  //! Connections IDs
  std::atomic<int> m_iNextAvailableId{0};

  //! Registered Connections
  std::mutex m_oRegisteredConnectionsMutex;
  std::unordered_map<int, std::shared_ptr<ActiveSocket>> m_oRegisteredConnections;
};