#include "EchoServer/ClientConnectionHandler.hpp"
#include "EchoServer/EchoServerConfig.hpp"
#include "Core/StringFormatUtils.hpp"
#include "Core/Debug.hpp"
#include "NetworkService/NetworkService.hpp"

#include <algorithm>

ClientConnectionHandler::ClientConnectionHandler(int socketID,
                                                 ActiveConnectionsCountGetterCallback activeConnectionsCountGetterCallback,
                                                 ReadCallback readCallback,
                                                 WriteCallback writeCallback)
    : m_socketID(socketID)
    , m_messagesReceivedCount(0UL)
    , m_activeConnectionsCountGetterCallback(activeConnectionsCountGetterCallback)
    , m_readCallback(readCallback)
    , m_writeCallback(writeCallback)
{
}

void ClientConnectionHandler::HandleClientConnection()
{
  std::string unprocessedLeftoverBytes;

  while (true)
  {
    std::string receivedBytes;

    if (!ReadNextBytesFromClient(receivedBytes))
      break;

    if (!ProcessReceivedBytes(receivedBytes, unprocessedLeftoverBytes))
      break;
  }
}

bool ClientConnectionHandler::ProcessReceivedBytes(const std::string &bytes, std::string &unprocessedLeftoverBytes)
{
  auto end = bytes.cend();
  auto nextLineStart = bytes.cbegin();

  while (nextLineStart != end)
  {
    auto newLineIter = std::find(nextLineStart, end, '\n');

    if (newLineIter != end)
    {
      // newline found in current sequence,
      // append and clear any leftovers from previous calls, and process the full message
      std::string fullMessage(std::move(unprocessedLeftoverBytes));
      unprocessedLeftoverBytes.clear();

      fullMessage.append(nextLineStart, ++newLineIter);

      if (!ProcessClientMessage(fullMessage))
        return false;

      nextLineStart = newLineIter;
    }
    else
    {
      // no newline found in current sequence, 
      // save contents as unprocessed leftovers for next time around
      unprocessedLeftoverBytes.append(nextLineStart, end);
      break;
    }
  }

  return true;
}

bool ClientConnectionHandler::ProcessClientMessage(const std::string &msg)
{
  if (IsClientMessageInfoRequest(msg))
    return WriteInfoMessageToClient();

  ++m_messagesReceivedCount;

  return WriteEchoMessageToClient(msg);
}

bool ClientConnectionHandler::IsClientMessageInfoRequest(const std::string &msg) const
{
  return !msg.empty() && (msg[0] == CFG_ECHO_SERVER_INFO_CMD_STR_PREFIX);
}

bool ClientConnectionHandler::ReadNextBytesFromClient(std::string &out_Msg) const
{
  auto readResult = m_readCallback(m_socketID, out_Msg);
  
  if (readResult == 0)
    DEBUG_LOG("ClientConnectionHandler: Client disconnected.\n");

  return readResult > 0;
}

bool ClientConnectionHandler::WriteInfoMessageToClient() const
{
  DEBUG_LOG("ClientConnectionHandler: client requested info\n");

  return m_writeCallback(m_socketID,
    StringFormatUtils::FormatInfoStr(CFG_ECHO_SERVER_INFO_CMD_STR_CONNECTIONS_COUNT,
                                    m_activeConnectionsCountGetterCallback(),
                                    CFG_ECHO_SERVER_INFO_CMD_STR_MSGS_COUNT,
                                    m_messagesReceivedCount)) >= 0;
}

bool ClientConnectionHandler::WriteEchoMessageToClient(const std::string &clientMsg) const
{
  DEBUG_LOG("ClientConnectionHandler: writing echo to client\n");
  return m_writeCallback(m_socketID, clientMsg) >= 0;
}