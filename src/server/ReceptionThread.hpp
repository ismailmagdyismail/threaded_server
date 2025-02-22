#pragma once

#include "Thread.hpp"
#include "PassiveSocket.hpp"

#include <functional>

class ReceptionThread
{
public:
  ReceptionThread(uint32_t p_ui32PortNumber);
  virtual ~ReceptionThread() = default;

  void Start();
  void ConnectionHandler();

protected:
  //! Template Method
  virtual void ProcessConnection(std::shared_ptr<ActiveSocket> &p_pConnection) = 0;

private:
  Thread m_oThread;
  PassiveSocket m_oSocket;
};