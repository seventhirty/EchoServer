#include "EchoServer/StrUtils.hpp"
#include "EchoServer/EchoServerConfig.hpp"

namespace StrUtils
{
  std::string FormatInfoStr(int connectionsCount, unsigned long messagesCount)
  {
    std::string result(CFG_ECHO_SERVER_INFO_CMD_STR_CONNECTIONS_COUNT);
    result += std::to_string(connectionsCount);
    result += '\n';
    result += CFG_ECHO_SERVER_INFO_CMD_STR_MSGS_COUNT;
    result += std::to_string(messagesCount);
    result += '\n';

    return result;
  }

  bool IsClientMessageInfoRequest(const std::string &msg)
  {
    return !msg.empty() && (msg[0] == CFG_ECHO_SERVER_INFO_CMD_STR_PREFIX);
  }
}