#pragma once

#include <mutex>
#include <memory>

#include "NetworkService/INetworkService.hpp"

class EchoServer
{
public:
  explicit EchoServer(std::unique_ptr<INetworkService> networkService);

  int Run();
  int GetActiveConnectionsCount();

private:
  EchoServer(const EchoServer &) = delete;
  EchoServer &operator=(const EchoServer &) = delete;

  int InitListeningSocket() const;

  void AcceptNextClientConnection(int listenSocketFD);
  void HandleClientConnection(int clientConnectionSocketFD);

  void UpdateActiveConnectionsCount(int delta);

  std::unique_ptr<INetworkService> m_networkService;
  int m_activeConnectionsCount;
  std::mutex m_activeConnectionsCountMutex;
};