#pragma once

#include <string>
#include <functional>

class MessageDataProcessor
{
public:
  using FullMessageHandlerCallback = std::function<bool(const std::string &)>;

  explicit MessageDataProcessor(FullMessageHandlerCallback callback);
  bool ProcessReceivedBytes(const std::string &bytes);

private:
  FullMessageHandlerCallback m_fullMessageHandlerCallback;
  std::string m_unprocessedLeftoverBytes;
};
