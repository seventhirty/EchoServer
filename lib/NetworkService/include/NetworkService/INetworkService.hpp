#pragma once

#include <string>
#include <cstdint>

class INetworkService
{
public:
  virtual int CreateListeningSocket(uint16_t portID, int maxPendingConnectionsInQueue) const = 0;
  virtual int Accept(int listenSocketFileDescriptor) const = 0;
  virtual int Close(int socketFileDescriptor) const = 0;
  virtual ssize_t ReadNextBytes(int socketFileDescriptor, std::string &out_strResult) const = 0;
  virtual ssize_t Write(int socketFileDescriptor, const std::string &str) const = 0;
  virtual int SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds) const = 0;

  virtual ~INetworkService() = default;
};