#pragma once

#include <string>

namespace SocketInterface
{
  int CreateListeningSocket(int portID, int maxPendingConnectionsInQueue);
  int Accept(int listenSocketFileDescriptor);
  int Close(int socketFileDescriptor);
  ssize_t Read(int socketFileDescriptor, std::string &out_strResult);
  ssize_t Write(int socketFileDescriptor, const std::string &str);
  int SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds);
}