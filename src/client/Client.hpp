#pragma once

#include <iostream>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <string>
#include <condition_variable>

//! sockets
#include "ActiveSocket.hpp"
#include "Thread.hpp"

#define ID_FIELD_SIZE 2
#define DELIMETER_SIZE 1

static std::string ACK_PORT_NUMBER = getenv("ACK_PORT_NUMBER");
static std::string STATUS_PORT_NUMBER = getenv("STATUS_PORT_NUMBER");
static int ackPortNumber = stoi(ACK_PORT_NUMBER);
static int statusPortNumber = stoi(STATUS_PORT_NUMBER);

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
    m_oAckConnectionThread.Start();
    m_oServerStatusConnectionThread.Start();

    //! Terminate thread after the Handshaking process is done
    m_oAckConnectionThread.Wait();
    m_oAckConnectionThread.Stop();
  }

private:
  ////////////////////////////////////////////////////////////////////////////////////////////
  //! AckConnection Handler and hand-shaking
  void AckConnectionHandler()
  {
    bool bConnectionStatus = m_oAckSocket.Connect(ackPortNumber, "localhost");
    std::cout << "[Client-Connection]: " << bConnectionStatus << std::endl;
    m_oAckSocket.Send("Connection Init from client");
    std::string strClientId = m_oAckSocket.Recieve();
    std::string iID = ParseId(strClientId);
    m_strAssignedId = iID;
    m_oIdConditionVariable.notify_all();
    std::cout << "[Client-ACK]" << m_strAssignedId << std::endl;
  }

  std::string ParseId(std::string &p_strID)
  {
    std::string strID = p_strID.substr(ID_FIELD_SIZE + DELIMETER_SIZE);
    return strID;
  }
  ////////////////////////////////////////////////////////////////////////////////////////////

  void ServerStatusConnectionHandler()
  {
    std::unique_lock<std::mutex> lock{m_oIdMutex};
    m_oIdConditionVariable.wait(lock, [this]()
                                { return m_strAssignedId.size() != 0; });
    bool bConnectionStatus = m_oServerStatusSocket.Connect(statusPortNumber, "localhost");
    std::cout << "[Client-Request]:" << bConnectionStatus << std::endl;
    if (!bConnectionStatus)
    {

      return;
    }
    std::string strStatusRequest = BuildRequestID();
    m_oServerStatusSocket.Send(strStatusRequest);
    std::string strConnectionsAvailable = m_oServerStatusSocket.Recieve();
    std::cout << "[Client-Response][Registered Connections] :" << strConnectionsAvailable << std::endl;
  }

  ////////////////////////////////////////////////////////////////////////////////////////////

  std::string BuildRequestID()
  {
    return std::string("ID=" + m_strAssignedId);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////
  //! Sockets
  ActiveSocket m_oAckSocket;          //! Initial connection handling and ID registration (Hand-shake)
  ActiveSocket m_oServerStatusSocket; //! Request status from server

  //! Thread to Handle AckScocket and handshaking process
  Thread m_oAckConnectionThread{std::bind(&Client::AckConnectionHandler, this)};

  //! Thread to Handle ServerStatus; getting on demand updates status about server
  Thread m_oServerStatusConnectionThread{std::bind(&Client::ServerStatusConnectionHandler, this)};

  //! EventLoop Status
  std::atomic<bool> m_bIsRunning{false};

  //! ID
  std::mutex m_oIdMutex;
  std::string m_strAssignedId;
  std::condition_variable m_oIdConditionVariable;
};