#include "Core/StringFormatUtils.hpp"

namespace StringFormatUtils
{
  std::string FormatInfoStr(const std::string &connectionsCountPrefix,
                            int connectionsCount,
                            const std::string &messagesCountPrefix,
                            unsigned long messagesCount)
  {
    std::string result(connectionsCountPrefix);

    result += std::to_string(connectionsCount);
    result += '\n';
    result += messagesCountPrefix;
    result += std::to_string(messagesCount);
    result += '\n';

    return result;
  }
}