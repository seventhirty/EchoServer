#include "SocketInterface/SocketInterface.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

#include "Core/Debug.hpp"

namespace SocketInterface
{
  int CreateListeningSocket(int portID, int maxPendingConnectionsInQueue)
  {
    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR opening listening socket: %s\n", std::strerror(errno));
    }

    sockaddr_in servAddr{};

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(portID);

    if (bind(socketFD, reinterpret_cast<sockaddr *>(&servAddr), sizeof(servAddr)) < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR binding listening socket: %s\n", std::strerror(errno));
      return -1;
    }

    if (listen(socketFD, maxPendingConnectionsInQueue) < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR preparing listening socket to listen: %s\n", std::strerror(errno));
      return -1;
    }

    return socketFD;
  }

  int Accept(int listenSocketFileDescriptor)
  {
    sockaddr_in cli_addr{};
    socklen_t clilen = sizeof(cli_addr);

    int clientSocketFD = accept(listenSocketFileDescriptor,
                                reinterpret_cast<sockaddr *>(&cli_addr),
                                &clilen);

    if (clientSocketFD < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR on accept: %s", std::strerror(errno));
    }

    return clientSocketFD;
  }

  int Close(int socketFileDescriptor)
  {
    int res = close(socketFileDescriptor);
    if (res < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR reading: %s\n", std::strerror(errno));
    }
    return res;
  }

  ssize_t Read(int socketFileDescriptor, std::string &out_strResult)
  {
    // TODO (avelkov): handle messages with unlimited length
    char buffer[256]{};

    ssize_t charsReadCount = read(socketFileDescriptor, buffer, sizeof(buffer));

    if (charsReadCount > 0)
    {
      out_strResult.assign(buffer, static_cast<size_t>(charsReadCount));
    }

    if (charsReadCount < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR reading: %s\n", std::strerror(errno));
    }

    return charsReadCount;
  }

  ssize_t Write(int socketFileDescriptor, const std::string &str)
  {
    ssize_t writeResult = write(socketFileDescriptor, str.data(), str.size());

    if (writeResult < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR writing: %s\n", std::strerror(errno));
    }

    return writeResult;
  }

  int SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds)
  {
    timeval timeout{};
    timeout.tv_sec = timeoutSeconds;

    int result = setsockopt(socketFileDescriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    if (result < 0)
    {
      DEBUG_LOG_ERROR("SocketInterface: ERROR setting timeout: %s\n", std::strerror(errno));
    }

    return result;
  }
}
