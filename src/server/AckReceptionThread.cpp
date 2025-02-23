#include <unistd.h>

#include "AckReceptionThread.hpp"

AckReceptionThread::AckReceptionThread(uint16_t p_ui16PortNumber, std::string &&p_strSocketName, ThreadPool &p_oThreadPool)
    : ReceptionThread(p_ui16PortNumber, std::move(p_strSocketName)),
      m_oThreadPool(p_oThreadPool)
{
}

void AckReceptionThread::ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection)
{
  std::function<void(void)> worker = [this, p_pConnection]()
  {
    sleep(5); //! Simulate processing
    p_pConnection->Send("Server, Ack Message");
  };
  m_oThreadPool.AddTask(worker);
}
