#include <sys/socket.h>

//! Socket Wrapper
#include "Socket.hpp"

#define FLAGS 0
#define CHUNK_SIZE 1024

void Socket::Send(int p_iSocketFd, const std::string &message)
{
  const char *data = message.c_str();
  int iSize = message.size();
  int iTotalBytesSent = 0;
  while (iTotalBytesSent < iSize)
  {
    int iSentBytes = send(p_iSocketFd, data + iTotalBytesSent, std::min(CHUNK_SIZE, iSize - iTotalBytesSent), FLAGS);
    if (-1 != iSentBytes)
    {
      iTotalBytesSent += iSentBytes;
    }
  }
  send(p_iSocketFd, "\0", 1, FLAGS);
}

std::string Socket::Recieve(int p_iSocketFd)
{
  std::string strMessage;
  int iTotalBytesRecieved = 0;
  while (true)
  {
    char buffer[CHUNK_SIZE] = {0};
    int iBytesRecieved = recv(p_iSocketFd, buffer, CHUNK_SIZE, FLAGS);
    if (-1 == iBytesRecieved)
    {
      continue;
    }
    iTotalBytesRecieved += iBytesRecieved;
    strMessage.append(buffer, iBytesRecieved);
    if ('\0' == buffer[iBytesRecieved - 1])
    {
      break;
    }
  }
  return strMessage;
}