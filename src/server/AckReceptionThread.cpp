#include <unistd.h>

#include "AckReceptionThread.hpp"

AckReceptionThread::AckReceptionThread(uint16_t p_ui16PortNumber, std::string &&p_strSocketName, ThreadPool &p_oThreadPool, ConnectionsManager &p_oConnectionsManager)
    : ReceptionThread(p_ui16PortNumber, std::move(p_strSocketName)),
      m_oThreadPool(p_oThreadPool),
      m_oConnectionsManager(p_oConnectionsManager)
{
}

void AckReceptionThread::ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection)
{
  std::function<void(void)> worker = [this, p_pConnection]()
  {
    //! Simulate processing
    sleep(2);

    //! Get Next Available ID
    int iNextId = m_oConnectionsManager.RegisterNewConnection(p_pConnection);

    //! Send it to client
    p_pConnection->Send(std::string("ID=") + std::to_string(iNextId));
  };
  m_oThreadPool.AddTask(worker);
}
