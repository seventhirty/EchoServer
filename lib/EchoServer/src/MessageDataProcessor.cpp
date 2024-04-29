#include "EchoServer/MessageDataProcessor.hpp"

#include <algorithm>

MessageDataProcessor::MessageDataProcessor(FullMessageHandlerCallback callback)
    : m_fullMessageHandlerCallback(callback)
{
}

bool MessageDataProcessor::ProcessReceivedBytes(const std::string &bytes)
{
  auto end = bytes.cend();
  auto nextLineStart = bytes.cbegin();

  while (nextLineStart != end)
  {
    auto newLineIter = std::find(nextLineStart, end, '\n');

    if (newLineIter != end)
    {
      // newline found in current sequence,
      // append and clear any leftovers from previous calls, process the full message
      std::string fullMessage(std::move(m_unprocessedLeftoverBytes));
      m_unprocessedLeftoverBytes.clear();

      fullMessage.append(nextLineStart, ++newLineIter);

      if (!m_fullMessageHandlerCallback(fullMessage))
        return false;

      nextLineStart = newLineIter;
    }
    else
    {
      // no newline found in current sequence, 
      // save contents as unprocessed leftovers for next time around
      m_unprocessedLeftoverBytes.append(nextLineStart, end);
      break;
    }
  }

  return true; 
}