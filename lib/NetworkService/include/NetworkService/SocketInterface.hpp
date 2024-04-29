#pragma once

#include "NetworkService/ISocketInterface.hpp"

class SocketInterface : public ISocketInterface
{
public:
  int CreateSocket(int domain, int type, int protocol) const override;
  int Bind(int socketFD, const sockaddr *socketAddress, socklen_t addrlen) const override;
  int Listen(int socketFD, int maxPendingConnectionsCount) const override;
  int Accept(int socketFD, sockaddr *out_socketAddress, socklen_t *out_addrLen) const override;
  int Close(int socketFD) const override;
  ssize_t Read(int socketFD, void *buffer, size_t nBytes) const override;
  ssize_t Write(int socketFD, const void *buffer, size_t nBytes) const override;
  ssize_t SetOption(int socketFD, int protocolLevel,
                           int optionName, const void *optionValue, socklen_t optionLen) const override;
};

inline int SocketInterface::CreateSocket(int domain, int type, int protocol) const
{
  return socket(domain, type, protocol);
}

inline int SocketInterface::Bind(int socketFD, const sockaddr *socketAddress, socklen_t addrlen) const
{
  return bind(socketFD, socketAddress, addrlen);
}

inline int SocketInterface::Listen(int socketFD, int maxPendingConnectionsCount) const
{
  return listen(socketFD, maxPendingConnectionsCount);
}

inline int SocketInterface::Accept(int socketFD, sockaddr *out_socketAddress, socklen_t *out_addrLen) const
{
  return accept(socketFD, out_socketAddress, out_addrLen);
}

inline int SocketInterface::Close(int socketFD) const
{
  return close(socketFD);
}

inline ssize_t SocketInterface::Read(int socketFD, void *buffer, size_t nBytes) const
{
  return read(socketFD, buffer, nBytes);
}

inline ssize_t SocketInterface::Write(int socketFD, const void *buffer, size_t nBytes) const
{
  return write(socketFD, buffer, nBytes);
}

inline ssize_t SocketInterface::SetOption(int socketFD, int protocolLevel, int optionName, 
                                   const void *optionValue, socklen_t optionLen) const
{
  return setsockopt(socketFD, protocolLevel, optionName, optionValue, optionLen);
}