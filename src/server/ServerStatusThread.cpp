#include "ServerStatusThread.hpp"

#define ID_FEILD_LENGTH 2
#define DELIMETER_LENGTH 1

ServerStatusThread::ServerStatusThread(uint32_t p_ui32PortNumber, std::string &&p_strSocketName, ThreadPool &p_oThreadPool, ConnectionsManager &p_oConnectionsManager)
    : ReceptionThread(p_ui32PortNumber, std::move(p_strSocketName)),
      m_oThreadPool(p_oThreadPool),
      m_oConnectionManager(p_oConnectionsManager)
{
}

void ServerStatusThread::ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection)
{
  std::function<void(void)> fConnectionHandlerTask = [this, p_pConnection]() -> void
  {
    std::string strMessage = p_pConnection->Recieve();
    int iID = stoi(strMessage.substr(ID_FEILD_LENGTH + DELIMETER_LENGTH));
    std::cout << "[ServerStatus]: Request ID " << iID << std::endl;
    bool bIsRegistered = m_oConnectionManager.IsRegistered(iID);
    if (!bIsRegistered)
    {
      p_pConnection->Send("UN-AUTHORIZED");
      return;
    }
    std::vector<int> vRegisteredConnections = m_oConnectionManager.GetAvailableConnections();
    std::string strResponse = "ConnectionsCount: ";
    for (int i = 0; i < vRegisteredConnections.size(); i++)
    {
      strResponse += std::to_string(vRegisteredConnections[i]);
      strResponse += std::string(",");
    }
    p_pConnection->Send(strResponse);
  };
  m_oThreadPool.AddTask(fConnectionHandlerTask);
}
