#pragma once

#include <string>

namespace StrUtils
{
  std::string FormatInfoStr(int connectionsCount,unsigned long messagesCount);
  bool IsClientMessageInfoRequest(const std::string &msg);
}
