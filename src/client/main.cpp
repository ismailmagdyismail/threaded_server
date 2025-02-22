#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

//! sockets
#include "ClientSocket.hpp"

std::string SERVER_PORT_NUMBER_ENV = getenv("SERVER_PORT_NUMBER");
int portNumber = 8080;

int main()
{
  std::cout << "Client thread " << std::endl;
  ClientSocket socket;
  bool connectionStatus = socket.Connect(portNumber, "localhost");
  std::cout << "Client connection status " << connectionStatus << std::endl;
  socket.Send("This a message from the client");
}