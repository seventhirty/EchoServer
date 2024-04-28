#pragma once

#include <memory>

#include "NetworkService/INetworkService.hpp"
#include "NetworkService/ISocketInterface.hpp"

class NetworkService : public INetworkService
{
public:
  explicit NetworkService(std::unique_ptr<ISocketInterface> socketInterface);

  int CreateListeningSocket(uint16_t portID, int maxPendingConnectionsInQueue) const override;
  int Accept(int listenSocketFileDescriptor) const override;
  int Close(int socketFileDescriptor) const override;
  ssize_t ReadNextBytes(int socketFileDescriptor, std::string &out_strResult) const override;
  ssize_t Write(int socketFileDescriptor, const std::string &str) const override;
  int SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds) const override;

private:
  NetworkService(const NetworkService &) = delete;
  NetworkService &operator=(const NetworkService &) = delete;

  std::unique_ptr<ISocketInterface> m_socketInterface;
};