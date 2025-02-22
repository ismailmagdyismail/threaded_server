#include <iostream>
#include <unistd.h>
#include <string>

//! sockets
#include "PassiveSocket.hpp"
#include "ActiveSocket.hpp"

std::string SERVER_PORT_NUMBER_ENV = getenv("SERVER_PORT_NUMBER");
int portNumber = stoi(SERVER_PORT_NUMBER_ENV);

int main()
{
  PassiveSocket socket(portNumber, -1);
  ActiveSocket newConnection = socket.Accept();
  std::string messageRecieved = newConnection.Recieve();
  std::cout << "[Server]: Recieved this message " << messageRecieved << std::endl;
  newConnection.Send("Server ack message");
}