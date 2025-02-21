#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

//! sockets
#include "sockets/ServerSocket.hpp"
#include "sockets/ClientSocket.hpp"

std::string SERVER_PORT_NUMBER_ENV = getenv("SERVER_PORT_NUMBER");
int portNumber = 8080;

void clientWorker()
{
  sleep(5);
  std::cout << "Client thread " << std::endl;
  ClientSocket socket;
  bool connectionStatus = socket.Connect(portNumber, "localhost");
  std::cout << "Client connection status " << connectionStatus << std::endl;
}

int main()
{
  std::thread clientThread = std::thread(clientWorker);
  ServerSocket socket(portNumber, -1);
  int clientFd = socket.Accept();
  std::cout << "Client fd " << clientFd << std::endl;
  clientThread.join();
}