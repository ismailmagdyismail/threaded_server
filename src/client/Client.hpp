#pragma once

#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <string>

//! sockets
#include "ActiveSocket.hpp"
#include "Thread.hpp"

#define ID_FIELD_SIZE 2
#define DELIMETER_SIZE 1

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
      std::string strClientId = m_oAckSocket.Recieve();
      std::string iID = ParseId(strClientId);
      m_strAssignedId = iID;
      std::cout << "[Client-ACK]" << m_strAssignedId << std::endl;
    };
    m_oAckConnectionThread.SetHandler(fAckConnectionHandler);
    m_oAckConnectionThread.Start();
  }

  std::string ParseId(std::string &p_strID)
  {
    std::string strID = p_strID.substr(ID_FIELD_SIZE + DELIMETER_SIZE);
    return strID;
  }

  //! AckConnection Handling
  ActiveSocket m_oAckSocket;

  Thread m_oAckConnectionThread{[]() {}};
  std::atomic<bool> m_bIsRunning{false};

  //! ID
  std::string m_strAssignedId;
};