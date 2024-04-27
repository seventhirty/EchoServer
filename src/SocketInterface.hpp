#pragma once

#include <string>

namespace SocketInterface
{
  int CreateListeningSocket();
  int BindSocket(int socketFileDescriptor, int portID);
  int ListenSocket(int socketFileDescriptor, int maxPendingConnectionsInQueue);
  int Accept(int listenSocketFileDescriptor);
  int Close(int socketFileDescriptor);
  ssize_t Read(int socketFileDescriptor, std::string &out_strResult);
  int Write(int socketFileDescriptor, const std::string &str);
  int SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds);
}