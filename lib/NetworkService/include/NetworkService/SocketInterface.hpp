#pragma once

#include "NetworkService/ISocketInterface.hpp"

class SocketInterface : public ISocketInterface
{
public:
  inline int CreateSocket(int domain, int type, int protocol) const override;
  inline int Bind(int socketFD, const sockaddr *socketAddress, socklen_t addrlen) const override;
  inline int Listen(int socketFD, int maxPendingConnectionsCount) const override;
  inline int Accept(int socketFD, sockaddr *out_socketAddress, socklen_t *out_addrLen) const override;
  inline int Close(int socketFD) const override;
  inline ssize_t Read(int socketFD, void *buffer, size_t nBytes) const override;
  inline ssize_t Write(int socketFD, const void *buffer, size_t nBytes) const override;
  inline ssize_t SetOption(int socketFD, int protocolLevel,
                           int optionName, const void *optionValue, socklen_t optionLen) const override;
};

int SocketInterface::CreateSocket(int domain, int type, int protocol) const
{
  return socket(domain, type, protocol);
}

int SocketInterface::Bind(int socketFD, const sockaddr *socketAddress, socklen_t addrlen) const
{
  return bind(socketFD, socketAddress, addrlen);
}

int SocketInterface::Listen(int socketFD, int maxPendingConnectionsCount) const
{
  return listen(socketFD, maxPendingConnectionsCount);
}

int SocketInterface::Accept(int socketFD, sockaddr *out_socketAddress, socklen_t *out_addrLen) const
{
  return accept(socketFD, out_socketAddress, out_addrLen);
}

int SocketInterface::Close(int socketFD) const
{
  return close(socketFD);
}

ssize_t SocketInterface::Read(int socketFD, void *buffer, size_t nBytes) const
{
  return read(socketFD, buffer, nBytes);
}

ssize_t SocketInterface::Write(int socketFD, const void *buffer, size_t nBytes) const
{
  return write(socketFD, buffer, nBytes);
}

ssize_t SocketInterface::SetOption(int socketFD, int protocolLevel, int optionName, 
                                   const void *optionValue, socklen_t optionLen) const
{
  return setsockopt(socketFD, protocolLevel, optionName, optionValue, optionLen);
}