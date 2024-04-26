#include "EchoServerUtils.hpp"
#include "EchoServerConfig.hpp"

namespace EchoServerUtils
{
  std::string FormatInfoStr(int connectionsCount, unsigned long messagesCount)
  {
    // TODO (avelkov): check if RVO is working
    // TODO (avelkov): check if using reserve is faster:

    std::string result(CFG_ECHO_SERVER_INFO_CMD_STR_CONNECTIONS_COUNT);

    result += std::to_string(connectionsCount);
    result += '\n';
    result += CFG_ECHO_SERVER_INFO_CMD_STR_MSGS_COUNT;
    result += std::to_string(messagesCount);
    result += '\n';

    return result;
  }
}