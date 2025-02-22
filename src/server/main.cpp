#include <iostream>
#include <unistd.h>
#include <string>

#include "Server.hpp"

int main()
{
  std::shared_ptr<Server> pServer = Server::Instance();
  pServer->Start();
  while (pServer->IsRunning())
  {
    continue;
  }
}