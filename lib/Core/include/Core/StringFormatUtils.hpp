#pragma once

#include <string>

namespace StringFormatUtils
{
  std::string FormatInfoStr(const std::string &connectionsCountPrefix,
                            int connectionsCount,
                            const std::string &messagesCountPrefix,
                            unsigned long messagesCount);
}
