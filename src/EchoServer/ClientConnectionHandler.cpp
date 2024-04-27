#include "ClientConnectionHandler.hpp"
#include "Core/StringFormatUtils.hpp"
#include "Core/Debug.hpp"
#include "SocketInterface/SocketInterface.hpp"
#include "EchoServerConfig.hpp"

ClientConnectionHandler::ClientConnectionHandler(int socketID, ActiveConnectionsCountGetterCallback callback)
    : m_activeConnectionsCountGetterCallback(callback), m_socketID(socketID), m_messagesReceivedCount(0UL)
{
}

void ClientConnectionHandler::HandleClientEchoConnection()
{
  SocketInterface::SetupConnectionTimeout(m_socketID, CFG_ECHO_SERVER_TIMEOUT_SECONDS);

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
      ++m_messagesReceivedCount;

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
  auto readResult = SocketInterface::Read(m_socketID, out_Msg);
  if (readResult == 0)
  {
    DEBUG_LOG("ClientConnectionHandler: Client disconnected.\n");
  }

  return readResult > 0;
}

bool ClientConnectionHandler::WriteInfoMessageToClient() const
{
  DEBUG_LOG("ClientConnectionHandler: client requested info\n");

  return SocketInterface::Write(
             m_socketID,
             StringFormatUtils::FormatInfoStr(CFG_ECHO_SERVER_INFO_CMD_STR_CONNECTIONS_COUNT,
                                              m_activeConnectionsCountGetterCallback(),
                                              CFG_ECHO_SERVER_INFO_CMD_STR_MSGS_COUNT,
                                              m_messagesReceivedCount)) >= 0;
}

bool ClientConnectionHandler::WriteEchoMessageToClient(const std::string &clientMsg) const
{
  DEBUG_LOG("ClientConnectionHandler: writing echo to client\n");
  return SocketInterface::Write(m_socketID, clientMsg) >= 0;
}