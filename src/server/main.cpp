#include <iostream>
#include <unistd.h>
#include <string>

//! sockets
#include "ServerSocket.hpp"
#include "ClientSocket.hpp"

std::string SERVER_PORT_NUMBER_ENV = getenv("SERVER_PORT_NUMBER");
int portNumber = 8080;

int main()
{
  ServerSocket socket(portNumber, -1);
  int clientFd = socket.Accept();
  std::string messageRecieved = socket.Recieve(clientFd);
  std::cout << "Server Recieved this message " << messageRecieved << std::endl;
}