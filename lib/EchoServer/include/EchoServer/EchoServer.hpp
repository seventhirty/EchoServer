#pragma once

#include <mutex>

#include "NetworkService/NetworkService.hpp" // TODO : interface param

class EchoServer
{
public:
  EchoServer();

  int Run();
  int GetActiveConnectionsCount();

private:
  EchoServer(const EchoServer &) = delete;
  EchoServer &operator=(const EchoServer &) = delete;

  int InitListeningSocket() const;

  void AcceptNextClientConnection(int listenSocketFD);
  void HandleClientConnection(int clientConnectionSocketFD);

  void UpdateActiveConnectionsCount(int delta);

  NetworkService m_networkService;

  int m_activeConnectionsCount = 0;
  std::mutex m_activeConnectionsCountMutex;
};