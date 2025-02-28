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

  bool IsRegistered(int p_iID)
  {
    std::lock_guard<std::mutex> lock{m_oRegisteredConnectionsMutex};
    return m_oRegisteredConnections.find(p_iID) != m_oRegisteredConnections.end();
  }

  std::vector<int> GetAvailableConnections()
  {
    std::lock_guard<std::mutex> lock{m_oRegisteredConnectionsMutex};
    std::vector<int> vRegisteredConnections(m_oRegisteredConnections.size());
    int i = 0;
    for (auto &connection : m_oRegisteredConnections)
    {
      vRegisteredConnections[i] = connection.first; //! id;
      i++;
    }
    return vRegisteredConnections;
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