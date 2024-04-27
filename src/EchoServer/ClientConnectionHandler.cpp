#include "ClientConnectionHandler.hpp"
#include "SocketInterface/SocketInterface.hpp"
#include "EchoServerConfig.hpp"
#include "Core/StringFormatUtils.hpp"
#include "Core/Debug.hpp"

ClientConnectionHandler::ClientConnectionHandler(int socketID, ActiveConnectionsCountGetterCallback callback)
    : m_activeConnectionsCountGetterCallback(callback), m_socketID(socketID), m_messagesReceivedCount(0UL)
{
}

void ClientConnectionHandler::HandleClientEchoConnection()
{
  SocketInterface::SetupConnectionTimeout(m_socketID, CFG_ECHO_SERVER_TIMEOUT_SECONDS);

  while (true)
  {
    std::string readStr;

    if (!ReadClientMessage(readStr))
      break;

    if (IsClientMessageInfoRequest(readStr))
    {
      if (!WriteInfoMessageToClient())
        break;
    }
    else
    {
      ++m_messagesReceivedCount;

      if (!WriteEchoMessageToClient(readStr))
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

  if (readResult < 0)
  {
    DEBUG_LOG_ERROR("ClientConnectionHandler: ERROR reading client msg: %s\n", std::strerror(errno));
    return false;
  }
  else if (readResult == 0)
  {
    DEBUG_LOG("ClientConnectionHandler: client disconnected\n");
    return false;
  }

  return true;
}

bool ClientConnectionHandler::WriteInfoMessageToClient() const
{
  DEBUG_LOG("ClientConnectionHandler: client requested info\n");

  auto writeResult = SocketInterface::Write(
      m_socketID,
      StringFormatUtils::FormatInfoStr(CFG_ECHO_SERVER_INFO_CMD_STR_CONNECTIONS_COUNT,
                                       m_activeConnectionsCountGetterCallback(),
                                       CFG_ECHO_SERVER_INFO_CMD_STR_MSGS_COUNT,
                                       m_messagesReceivedCount));
  if (writeResult < 0)
  {
    DEBUG_LOG_ERROR("ClientConnectionHandler: ERROR writing info msg to client: %s\n",
                    std::strerror(errno));
    return false;
  }

  return true;
}

bool ClientConnectionHandler::WriteEchoMessageToClient(const std::string &clientMsg) const
{
  DEBUG_LOG("ClientConnectionHandler: writing echo to client\n");

  if (SocketInterface::Write(m_socketID, clientMsg) < 0)
  {
    DEBUG_LOG_ERROR("ClientConnectionHandler: ERROR writing echo msg to client: %s\n",
                    std::strerror(errno));
    return false;
  }

  return true;
}