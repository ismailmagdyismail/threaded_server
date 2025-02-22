#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>

//! sockets
#include "ActiveSocket.hpp"

std::string SERVER_PORT_NUMBER_ENV = getenv("SERVER_PORT_NUMBER");
int portNumber = stoi(SERVER_PORT_NUMBER_ENV);

int main()
{
  std::cout << "Client thread " << std::endl;
  ActiveSocket socket;
  bool connectionStatus = socket.Connect(portNumber, "localhost");
  std::cout << "Client connection status " << connectionStatus << std::endl;
  socket.Send("This a message from the client");
  std::string message = socket.Recieve();
  std::cout << "[Client]: Recieved " << message << std::endl;
}