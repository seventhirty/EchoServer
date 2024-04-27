#include "EchoServer.hpp"

#include <thread>

#include "Debug.hpp"
#include "SocketInterface.hpp"
#include "EchoServerConfig.hpp"
#include "EchoServerClientConnection.hpp"

int EchoServer::InitListeningSocket()
{
  DEBUG_LOG("EchoServer creating listening socket..\n");
  auto listenSocketFD = SocketInterface::CreateListeningSocket();
  DEBUG_ASSERT(listenSocketFD >= 0, "ERROR opening socket: %s", std::strerror(errno));

  DEBUG_LOG("EchoServer binding listening socket..\n");
  DEBUG_ASSERT(SocketInterface::BindSocket(listenSocketFD, CFG_ECHO_SERVER_PORT) >= 0,
               "ERROR on binding: %s", std::strerror(errno));

  DEBUG_LOG("EchoServer preparing to accept connections (listen)..\n");
  DEBUG_ASSERT(SocketInterface::ListenSocket(listenSocketFD, CFG_ECHO_SERVER_MAX_PENDING_CLIENT_CONNECTIONS_IN) >= 0,
               "ERROR on listen: %s", std::strerror(errno));

  DEBUG_LOG("EchoServer successfully initialized listening socket..\n");
  return listenSocketFD;
}

int EchoServer::Run()
{
  DEBUG_LOG("EchoServer starting..\n");

  auto listenSocketFD = InitListeningSocket();

  // TODO (avelkov): end loop condition isRunning and a way to stop server (and free port on kill)
  while (true)
  {
    AcceptNextClientConnection(listenSocketFD);
  }

  DEBUG_LOG("EchoServer closing listening socket..\n");
  DEBUG_ASSERT(SocketInterface::Close(listenSocketFD) >= 0, "EchoServer::Run: ERROR on closing listening socket: %s", std::strerror(errno));

  DEBUG_LOG("EchoServer successful shutdown.\n");
  return EXIT_SUCCESS;
}

void EchoServer::AcceptNextClientConnection(int listenSocketFD)
{
  auto clientConnectionSocketFD = SocketInterface::Accept(listenSocketFD);

  if (clientConnectionSocketFD < 0)
  {
    DEBUG_LOG_ERROR("ERROR on accept: %s", std::strerror(errno));
    return;
  }

  DEBUG_LOG("EchoServer: new client connected. Socket ID: %d\n", clientConnectionSocketFD);

  std::thread clientThread(&EchoServer::HandleClientConnection, this, clientConnectionSocketFD);
  clientThread.detach();
}

void EchoServer::HandleClientConnection(int clientConnectionSocketFD)
{
  EchoServerClientConnection newConnection(clientConnectionSocketFD, *this);
  UpdateActiveConnectionsCount(1);
  newConnection.HandleClientEchoConnection();
  UpdateActiveConnectionsCount(-1);

  DEBUG_LOG("EchoServer: client disconnected. Closing socket %d\n", clientConnectionSocketFD);
  if (SocketInterface::Close(clientConnectionSocketFD) < 0)
  {
    DEBUG_LOG_ERROR("ERROR on closing client connection socket: %s",
                    std::strerror(errno));
  }
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