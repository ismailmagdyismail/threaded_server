#include <iostream>
#include <thread>

#include "Server.hpp"

std::string SERVER_PORT_NUMBER_ENV = getenv("SERVER_PORT_NUMBER");
int portNumber = stoi(SERVER_PORT_NUMBER_ENV);

std::shared_ptr<Server> Server::Instance()
{
  static std::shared_ptr<Server> g_pServer(new Server);
  return g_pServer;
}

Server::Server() : m_oServerStatusReceptionThread(portNumber)
{
}

void Server::Start()
{
  m_bIsRunning = true;
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