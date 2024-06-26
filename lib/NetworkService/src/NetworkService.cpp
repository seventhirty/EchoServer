#include "NetworkService/NetworkService.hpp"

#include <cerrno>
#include <cstring>

#include "Core/Debug.hpp"
#include "NetworkService/ISocketInterface.hpp"

NetworkService::NetworkService(std::unique_ptr<ISocketInterface> socketInterface)
    : m_socketInterface(std::move(socketInterface))
{
}

int NetworkService::CreateListeningSocket(uint16_t portID, int maxPendingConnectionsInQueue) const
{
  int socketFD = m_socketInterface->CreateSocket(AF_INET6, SOCK_STREAM, 0);
  if (socketFD < 0)
  {
    DEBUG_LOG_ERROR("SocketInterface: ERROR opening listening socket: %s\n", std::strerror(errno));
    return -1;
  }

  int reuseAddressOption = 1;
  if (m_socketInterface->SetOption(socketFD, SOL_SOCKET, SO_REUSEADDR,
                                   &reuseAddressOption, sizeof(reuseAddressOption)) < 0)
  {
    DEBUG_LOG_ERROR("SocketInterface: ERROR setting socket reusable option: %s\n", std::strerror(errno));
    m_socketInterface->Close(socketFD);
    return -1;
  }

  int ipv6OnlyOption = 0;
  if (m_socketInterface->SetOption(socketFD, IPPROTO_IPV6, IPV6_V6ONLY,
                                   &ipv6OnlyOption, sizeof(ipv6OnlyOption)) < 0)
  {
    DEBUG_LOG_ERROR("SocketInterface: ERROR setting ipv6 only option: %s\n", std::strerror(errno));
    m_socketInterface->Close(socketFD);
    return -1;
  }

  sockaddr_in6 servAddr{};

  servAddr.sin6_family = AF_INET6;
  servAddr.sin6_addr = in6addr_any;
  servAddr.sin6_port = htons(portID);

  if (m_socketInterface->Bind(socketFD, reinterpret_cast<sockaddr *>(&servAddr), sizeof(servAddr)) < 0)
  {
    DEBUG_LOG_ERROR("SocketInterface: ERROR binding listening socket: %s\n", std::strerror(errno));
    m_socketInterface->Close(socketFD);
    return -1;
  }

  if (m_socketInterface->Listen(socketFD, maxPendingConnectionsInQueue) < 0)
  {
    DEBUG_LOG_ERROR("SocketInterface: ERROR preparing listening socket to listen: %s\n", std::strerror(errno));
    m_socketInterface->Close(socketFD);
    return -1;
  }

  return socketFD;
}

int NetworkService::Accept(int listenSocketFileDescriptor) const
{
  if (listenSocketFileDescriptor < 0)
    return -1;

  sockaddr_in6 clientAddr{};
  socklen_t clientAddrSz = sizeof(clientAddr);

  int clientSocketFD = m_socketInterface->Accept(listenSocketFileDescriptor,
                                                 reinterpret_cast<sockaddr *>(&clientAddr),
                                                 &clientAddrSz);

  if (clientSocketFD < 0)
    DEBUG_LOG_ERROR("SocketInterface: ERROR on accept: %s\n", std::strerror(errno));

  return clientSocketFD;
}

int NetworkService::Close(int socketFileDescriptor) const
{
  int res = m_socketInterface->Close(socketFileDescriptor);
  
  if (res < 0)
    DEBUG_LOG_ERROR("SocketInterface: ERROR reading: %s\n", std::strerror(errno));
  
  return res;
}

ssize_t NetworkService::ReadNextBytes(int socketFileDescriptor, std::string &out_strResult) const
{
  if (socketFileDescriptor < 0)
    return -1;

  out_strResult.clear();

  constexpr size_t readBuffSize = 256;
  char buffer[readBuffSize]{};

  ssize_t charsReadCount = m_socketInterface->Read(socketFileDescriptor, buffer, readBuffSize);

  if (charsReadCount > 0)
    out_strResult.assign(buffer, static_cast<size_t>(charsReadCount));

  if (charsReadCount < 0)
    DEBUG_LOG_ERROR("SocketInterface: ERROR reading: %s\n", std::strerror(errno));

  return charsReadCount;
}

ssize_t NetworkService::Write(int socketFileDescriptor, const std::string &str) const
{
  if (socketFileDescriptor < 0)
    return -1;

  if (str.empty())
    return 0;

  ssize_t writeResult = m_socketInterface->Write(socketFileDescriptor, str.data(), str.size());

  if (writeResult < 0)
    DEBUG_LOG_ERROR("SocketInterface: ERROR writing: %s\n", std::strerror(errno));

  return writeResult;
}

int NetworkService::SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds) const
{
  if (socketFileDescriptor < 0)
    return -1;

  if (timeoutSeconds <= 0)
    return 0;

  timeval timeout{};
  timeout.tv_sec = timeoutSeconds;

  int result = m_socketInterface->SetOption(socketFileDescriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

  if (result < 0)
    DEBUG_LOG_ERROR("SocketInterface: ERROR setting timeout: %s\n", std::strerror(errno));

  return result;
}
