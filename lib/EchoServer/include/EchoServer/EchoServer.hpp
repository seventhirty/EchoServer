#pragma once

#include <mutex>

class EchoServer
{
public:
  EchoServer() = default;

  int Run();
  int GetActiveConnectionsCount();

private:
  EchoServer(const EchoServer &) = delete;
  EchoServer &operator=(const EchoServer &) = delete;

  int InitListeningSocket() const;

  void AcceptNextClientConnection(int listenSocketFD);
  void HandleClientConnection(int clientConnectionSocketFD);

  void UpdateActiveConnectionsCount(int delta);

  int m_activeConnectionsCount = 0;
  std::mutex m_activeConnectionsCountMutex;
};