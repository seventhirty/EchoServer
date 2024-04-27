#include "EchoServer/EchoServer.hpp"

#include <thread>

#include "Core/Debug.hpp"
#include "SocketInterface/SocketInterface.hpp"
#include "EchoServer/EchoServerConfig.hpp"
#include "EchoServer/ClientConnectionHandler.hpp"

int EchoServer::InitListeningSocket() const
{
  DEBUG_LOG("EchoServer initializing listening socket..\n");
  auto listenSocketFD = SocketInterface::CreateListeningSocket(CFG_ECHO_SERVER_PORT, CFG_ECHO_SERVER_MAX_PENDING_CLIENT_CONNECTIONS_IN);

  DEBUG_LOG("EchoServer successfully initialized listening socket..\n");
  return listenSocketFD;
}

int EchoServer::Run()
{
  DEBUG_LOG("EchoServer starting..\n");

  auto listenSocketFD = InitListeningSocket();

  if (listenSocketFD < 0)
    return EXIT_FAILURE;

  // TODO (avelkov): end loop condition isRunning and a way to stop server (and free port on kill)
  while (true)
    AcceptNextClientConnection(listenSocketFD);

  DEBUG_LOG("EchoServer closing listening socket..\n");

  return (SocketInterface::Close(listenSocketFD) >= 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

void EchoServer::AcceptNextClientConnection(int listenSocketFD)
{
  auto clientConnectionSocketFD = SocketInterface::Accept(listenSocketFD);

  if (clientConnectionSocketFD < 0)
    return;

  DEBUG_LOG("EchoServer: new client connected. Socket ID: %d\n", clientConnectionSocketFD);

  std::thread clientThread(&EchoServer::HandleClientConnection, this, clientConnectionSocketFD);
  clientThread.detach();
}

void EchoServer::HandleClientConnection(int clientConnectionSocketFD)
{
  ClientConnectionHandler newConnection(clientConnectionSocketFD,
                                        [this]()
                                        { return GetActiveConnectionsCount(); });
  UpdateActiveConnectionsCount(1);
  newConnection.HandleClientEchoConnection();
  UpdateActiveConnectionsCount(-1);

  DEBUG_LOG("EchoServer: client disconnected. Closing socket %d\n", clientConnectionSocketFD);
  SocketInterface::Close(clientConnectionSocketFD);
}

int EchoServer::GetActiveConnectionsCount()
{
  std::lock_guard<std::mutex> lock(m_activeConnectionsCountMutex);
  return m_activeConnectionsCount;
}

void EchoServer::UpdateActiveConnectionsCount(int delta)
{
  std::lock_guard<std::mutex> lock(m_activeConnectionsCountMutex);
  m_activeConnectionsCount += delta;
}