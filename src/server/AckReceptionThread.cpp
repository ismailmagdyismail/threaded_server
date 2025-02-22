#include "AckReceptionThread.hpp"

AckReceptionThread::AckReceptionThread(uint16_t p_ui16PortNumber, ThreadPool &p_oThreadPool)
    : ReceptionThread(p_ui16PortNumber),
      m_oThreadPool(p_oThreadPool)
{
}

void AckReceptionThread::ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection)
{
  std::cout << "About to handle connection " << std::endl;
  std::function<void(void)> worker = [this]()
  {
    std::cout << "Handling connection\n";
  };
  m_oThreadPool.AddTask(worker);
}
