#include "EchoServer/EchoServer.hpp"

#include <thread>

#include "Core/Debug.hpp"
#include "NetworkService/NetworkService.hpp"
#include "NetworkService/SocketInterface.hpp"
#include "EchoServer/EchoServerConfig.hpp"

EchoServer::EchoServer(std::unique_ptr<ISocketInterface> socketInterface)
  : m_networkService(std::move(socketInterface))
  , m_activeConnectionsCount(0)
{
}

int EchoServer::InitListeningSocket(int port) const
{
  DEBUG_LOG("EchoServer initializing listening socket..\n");
  auto listenSocketFD = m_networkService.CreateListeningSocket(port, CFG_ECHO_SERVER_MAX_PENDING_CLIENT_CONNECTIONS_IN);

  if (listenSocketFD > 0)
    DEBUG_LOG("EchoServer successfully initialized listening socket..\n");
    
  return listenSocketFD;
}

int EchoServer::Run(int port)
{
  DEBUG_LOG("EchoServer starting..\n");
  DEBUG_LOG("Port is: %d\n", port);
  
  auto listenSocketFD = InitListeningSocket(port);

  if (listenSocketFD < 0)
    return EXIT_FAILURE;

  while (true)
    AcceptNextClientConnection(listenSocketFD);

  return (m_networkService.Close(listenSocketFD) >= 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

void EchoServer::AcceptNextClientConnection(int listenSocketFD)
{
  auto clientConnectionSocketFD = m_networkService.Accept(listenSocketFD);

  if (clientConnectionSocketFD < 0)
    return;

  if (m_networkService.SetupConnectionTimeout(clientConnectionSocketFD, CFG_ECHO_SERVER_TIMEOUT_SECONDS) < 0)
    return;

  DEBUG_LOG("EchoServer: Client connected. Socket ID: %d\n", clientConnectionSocketFD);

  std::thread clientThread(&EchoServer::HandleClientConnection, this, clientConnectionSocketFD);
  clientThread.detach();
}

void EchoServer::HandleClientConnection(int clientConnectionSocketFD)
{
  ClientConnection clientConnection = CreateClientConnection(clientConnectionSocketFD);

  UpdateActiveConnectionsCount(1);
  clientConnection.HandleClientConnection();
  UpdateActiveConnectionsCount(-1);
  m_networkService.Close(clientConnectionSocketFD);
  DEBUG_LOG("EchoServer: Closing socket %d\n", clientConnectionSocketFD);
}

ClientConnection EchoServer::CreateClientConnection(int clientConnectionSocketFD)
{
  auto getActiveConnectionsCountCallback = [this]() { return GetActiveConnectionsCount(); };
  auto readNextBytesCallback = [this](int socketFileDescriptor, std::string &out_strResult)
  {
    return m_networkService.ReadNextBytes(socketFileDescriptor, out_strResult);
  };
  auto writeCallback = [this](int socketFileDescriptor, const std::string &str)
  { 
    return m_networkService.Write(socketFileDescriptor, str); 
  };

  return ClientConnection{clientConnectionSocketFD,
                          getActiveConnectionsCountCallback,
                          readNextBytesCallback,
                          writeCallback};
}