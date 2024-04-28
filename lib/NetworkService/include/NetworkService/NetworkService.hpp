#pragma once

#include <string>
#include <cstdint>
#include <memory>

#include "NetworkService/ISocketInterface.hpp"

class NetworkService
{
public:
  explicit NetworkService(std::unique_ptr<ISocketInterface> socketInterface);

  int CreateListeningSocket(uint16_t portID, int maxPendingConnectionsInQueue) const;
  int Accept(int listenSocketFileDescriptor) const;
  int Close(int socketFileDescriptor) const;
  ssize_t ReadNextBytes(int socketFileDescriptor, std::string &out_strResult) const;
  ssize_t Write(int socketFileDescriptor, const std::string &str) const;
  int SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds) const;

protected:
  std::unique_ptr<ISocketInterface> m_socketInterface;
};