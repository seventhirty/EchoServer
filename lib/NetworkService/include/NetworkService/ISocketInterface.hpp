#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

class ISocketInterface
{
public:
  virtual int CreateSocket(int domain, int type, int protocol) const = 0;
  virtual int Bind(int socketFD, const sockaddr *socketAddress, socklen_t addrLen) const = 0;
  virtual int Listen(int socketFD, int maxPendingConnectionsCount) const = 0;
  virtual int Accept(int socketFD, sockaddr *out_socketAddress, socklen_t *out_addrLen) const = 0;
  virtual int Close(int socketFD) const = 0;
  virtual ssize_t Read(int socketFD, void *buffer, size_t nBytes) const = 0;
  virtual ssize_t Write(int socketFD, const void *buffer, size_t nBytes) const = 0;
  virtual ssize_t SetOption(int socketFD, int protocolLevel,
                            int optionName, const void *optionValue, socklen_t optionLen) const = 0;

  virtual ~ISocketInterface() = default;
};