#include "SocketInterface.hpp"
#include "EchoServerConfig.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace SocketInterface
{
  int CreateSocket()
  {
    return socket(AF_INET, SOCK_STREAM, 0);
  }

  int BindSocket(int socketFileDescriptor, int portID)
  {
    sockaddr_in servAddr;

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(portID);

    return bind(socketFileDescriptor,
                reinterpret_cast<sockaddr *>(&servAddr),
                sizeof(servAddr));
  }

  int ListenSocket(int socketFileDescriptor, int maxPendingConnectionsInQueue)
  {
    return listen(socketFileDescriptor, maxPendingConnectionsInQueue);
  }

  int Accept(int listenSocketFileDescriptor)
  {
    sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    return accept(listenSocketFileDescriptor, (struct sockaddr *)&cli_addr, &clilen);
  }

  int Close(int socketFileDescriptor)
  {
    return close(socketFileDescriptor);
  }

  ssize_t Read(int socketFileDescriptor, std::string &out_strResult)
  {
    // TODO (avelkov): handle messages with unlimited length
    char buffer[CFG_ECHO_SERVER_MAX_CLIENT_MSG_LEN]{};

    ssize_t charsReadCount = read(socketFileDescriptor, buffer, sizeof(buffer));

    if (charsReadCount > 0)
      out_strResult.assign(buffer, static_cast<size_t>(charsReadCount));

    return charsReadCount;
  }

  int Write(int socketFileDescriptor, const std::string &str)
  {
    return write(socketFileDescriptor, str.data(), str.size());
  }

  int SetupConnectionTimeout(int socketFileDescriptor, time_t timeoutSeconds)
  {
    timeval timeout{};
    timeout.tv_sec = timeoutSeconds;

    return setsockopt(socketFileDescriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
  }
}
