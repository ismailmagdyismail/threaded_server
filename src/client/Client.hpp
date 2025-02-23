#pragma once

#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <string>

//! sockets
#include "ActiveSocket.hpp"
#include "Thread.hpp"

std::string ACK_PORT_NUMBER = getenv("ACK_PORT_NUMBER");
int ackPortNumber = stoi(ACK_PORT_NUMBER);

class Client
{
public:
  bool IsRunning()
  {
    return m_bIsRunning;
  }

  void Start()
  {
    m_bIsRunning = true;
    StartAckConnection();
  }

private:
  void StartAckConnection()
  {
    std::function<void(void)> fAckConnectionHandler = [this]()
    {
      bool bConnectionStatus = m_oAckSocket.Connect(ackPortNumber, "localhost");
      std::cout << "[Client-Connection]: " << bConnectionStatus << std::endl;
      m_oAckSocket.Send("Connection Init from client");
      std::string strAckMessage = m_oAckSocket.Recieve();
      std::cout << "[Client-ACK]" << strAckMessage << std::endl;
    };
    m_oAckConnectionThread.SetHandler(fAckConnectionHandler);
    m_oAckConnectionThread.Start();
  }

  //! AckConnection Handling
  Thread m_oAckConnectionThread{[]() {}};
  ActiveSocket m_oAckSocket;

  std::atomic<bool> m_bIsRunning{false};
};