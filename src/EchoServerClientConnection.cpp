#include "EchoServerClientConnection.hpp"
#include "SocketInterface.hpp"
#include "EchoServerConfig.hpp"
#include "EchoServer.hpp"
#include "EchoServerUtils.hpp"
#include "Debug.hpp"

void EchoServerClientConnection::HandleClientEchoConnection()
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

bool EchoServerClientConnection::IsClientMessageInfoRequest(const std::string &msg) const
{
  return !msg.empty() && (msg[0] == CFG_ECHO_SERVER_INFO_CMD_STR_PREFIX);
}

bool EchoServerClientConnection::ReadClientMessage(std::string &out_Msg)
{
  auto readResult = SocketInterface::Read(m_socketID, out_Msg);

  if (readResult < 0)
  {
    DEBUG_LOG_ERROR("EchoServerClientConnection: ERROR reading client msg: %s\n", std::strerror(errno));
    return false;
  }
  else if (readResult == 0)
  {
    DEBUG_LOG("EchoServerClientConnection: client disconnected\n");
    return false;
  }

  return true;
}

bool EchoServerClientConnection::WriteInfoMessageToClient()
{
  DEBUG_LOG("EchoServerClientConnection: client requested info\n");

  auto writeResult = SocketInterface::Write(
      m_socketID,
      EchoServerUtils::FormatInfoStr(m_server.GetActiveConnectionsCount(),
                                     m_messagesReceivedCount));
  if (writeResult < 0)
  {
    DEBUG_LOG_ERROR("EchoServerClientConnection: ERROR writing info msg to client: %s\n",
                    std::strerror(errno));
    return false;
  }

  return true;
}

bool EchoServerClientConnection::WriteEchoMessageToClient(const std::string &clientMsg)
{
  DEBUG_LOG("EchoServerClientConnection: writing echo to client\n");

  if (SocketInterface::Write(m_socketID, clientMsg) < 0)
  {
    DEBUG_LOG_ERROR("EchoServerClientConnection: ERROR writing echo msg to client: %s\n",
                    std::strerror(errno));
    return false;
  }

  return true;
}