#pragma once

#include "ReceptionThread.hpp"
#include "ThreadPool.hpp"

class AckReceptionThread : public ReceptionThread
{
public:
  AckReceptionThread(uint16_t p_ui16PortNumber, ThreadPool &p_pThreadPool);
  virtual void ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection) override;

private:
  ThreadPool &m_oThreadPool;
};