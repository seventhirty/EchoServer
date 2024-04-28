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
    , m_activeConnectionsCountGetterCallback(activeConnectionsCountGetterCallback)
    , m_readCallback(readCallback)
    , m_writeCallback(writeCallback)
    , m_messagesReceivedCount(0UL)
{
}

void ClientConnectionHandler::HandleClientEchoConnection()
{
  while (true)
  {
    std::string clientMsg;

    if (!ReadClientMessage(clientMsg))
      break;

    if (IsClientMessageInfoRequest(clientMsg))
    {
      if (!WriteInfoMessageToClient())
        break;
    }
    else
    {
      m_messagesReceivedCount += std::count(clientMsg.begin(), clientMsg.end(), '\n');

      if (!WriteEchoMessageToClient(clientMsg))
        break;
    }
  }
}

bool ClientConnectionHandler::IsClientMessageInfoRequest(const std::string &msg) const
{
  return !msg.empty() && (msg[0] == CFG_ECHO_SERVER_INFO_CMD_STR_PREFIX);
}

bool ClientConnectionHandler::ReadClientMessage(std::string &out_Msg) const
{
  auto readResult = m_readCallback(m_socketID, out_Msg);
  if (readResult == 0)
  {
    DEBUG_LOG("ClientConnectionHandler: Client disconnected.\n");
  }

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