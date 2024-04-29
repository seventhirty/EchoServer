#pragma once

#include <atomic>
#include <memory>

#include "NetworkService/NetworkService.hpp"
#include "NetworkService/ISocketInterface.hpp"

class EchoServer
{
public:
  explicit EchoServer(std::unique_ptr<ISocketInterface> socketInterface);

  int Run(int port);
  inline int GetActiveConnectionsCount();

private:
  EchoServer(const EchoServer &) = delete;
  EchoServer &operator=(const EchoServer &) = delete;

  int InitListeningSocket(int port) const;

  void AcceptNextClientConnection(int listenSocketFD);
  void HandleClientConnection(int clientConnectionSocketFD);

  inline void UpdateActiveConnectionsCount(int delta);

  NetworkService m_networkService;
  std::atomic_int m_activeConnectionsCount;
};

int EchoServer::GetActiveConnectionsCount()
{
  return m_activeConnectionsCount;
}

void EchoServer::UpdateActiveConnectionsCount(int delta)
{
  m_activeConnectionsCount += delta;
}