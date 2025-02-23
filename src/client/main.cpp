#include "Client.hpp"

int main()
{
  Client client;
  client.Start();
  while (client.IsRunning())
  {
    continue;
  }
}