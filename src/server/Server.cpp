#include <iostream>
#include <thread>

#include "Server.hpp"

std::string ACK_PORT_NUMBER = getenv("ACK_PORT_NUMBER");
std::string STATUS_PORT_NUMBER = getenv("STATUS_PORT_NUMBER");

int ackPortNumber = stoi(ACK_PORT_NUMBER);
int statusPortNumber = stoi(STATUS_PORT_NUMBER);

std::shared_ptr<Server> Server::Instance()
{
  static std::shared_ptr<Server> g_pServer(new Server);
  return g_pServer;
}

Server::Server()
    : m_oAckReceptionThread(ackPortNumber, "Ack", m_oThreadPool, m_oConnectionsManager),
      m_oServerStatusReceptionThread(statusPortNumber, "Status", m_oThreadPool, m_oConnectionsManager)
{
}

void Server::Start()
{
  m_bIsRunning = true;
  m_oAckReceptionThread.Start();
  m_oServerStatusReceptionThread.Start();
}

bool Server::IsRunning()
{
  return m_bIsRunning;
}

Server::~Server()
{
  std::cout << "Server Shut down " << std::endl;
}