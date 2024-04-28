#include "EchoServer/EchoServer.hpp"

#include <thread>

#include "Core/Debug.hpp"
#include "NetworkService/NetworkService.hpp"
#include "NetworkService/LinuxSocketInterface.hpp"
#include "EchoServer/EchoServerConfig.hpp"
#include "EchoServer/ClientConnectionHandler.hpp"

EchoServer::EchoServer()
    : m_networkService(std::move(std::make_unique<LinuxSocketInterface>()))
{
}

int EchoServer::InitListeningSocket() const
{
  DEBUG_LOG("EchoServer initializing listening socket..\n");
  auto listenSocketFD = m_networkService.CreateListeningSocket(CFG_ECHO_SERVER_PORT, CFG_ECHO_SERVER_MAX_PENDING_CLIENT_CONNECTIONS_IN);

  if (listenSocketFD > 0)
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

  return (m_networkService.Close(listenSocketFD) >= 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

void EchoServer::AcceptNextClientConnection(int listenSocketFD)
{
  auto clientConnectionSocketFD = m_networkService.Accept(listenSocketFD);

  if (clientConnectionSocketFD < 0)
    return;

  DEBUG_LOG("EchoServer: new client connected. Socket ID: %d\n", clientConnectionSocketFD);

  std::thread clientThread(&EchoServer::HandleClientConnection, this, clientConnectionSocketFD);
  clientThread.detach(); // TODO : check for lifetime issues (error on close)
}

void EchoServer::HandleClientConnection(int clientConnectionSocketFD)
{
  m_networkService.SetupConnectionTimeout(clientConnectionSocketFD, CFG_ECHO_SERVER_TIMEOUT_SECONDS);

  auto getActiveConnectionsCountCallback = [this]() { return GetActiveConnectionsCount(); };

  auto readNextBytesCallback =
    [this](int socketFileDescriptor, std::string &out_strResult)
    {
      return m_networkService.ReadNextBytes(socketFileDescriptor, out_strResult);
    };

  auto writeCallback = 
    [this](int socketFileDescriptor, const std::string &str)
    { 
      return m_networkService.Write(socketFileDescriptor, str); 
    };

  ClientConnectionHandler newConnection(clientConnectionSocketFD,
                                        getActiveConnectionsCountCallback,
                                        readNextBytesCallback,
                                        writeCallback);

  UpdateActiveConnectionsCount(1);
  newConnection.HandleClientEchoConnection();
  UpdateActiveConnectionsCount(-1);

  DEBUG_LOG("EchoServer: client disconnected. Closing socket %d\n", clientConnectionSocketFD);
  m_networkService.Close(clientConnectionSocketFD);
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