#pragma once

#include <string>

namespace EchoServerStrUtils
{
  std::string FormatInfoStr(int connectionsCount,unsigned long messagesCount);
  bool IsClientMessageInfoRequest(const std::string &msg);
}
