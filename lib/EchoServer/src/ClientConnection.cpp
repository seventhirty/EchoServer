#include "EchoServer/ClientConnection.hpp"
#include "Core/Debug.hpp"
#include "NetworkService/NetworkService.hpp"

ClientConnection::ClientConnection(int socketID,
                                   ActiveConnectionsCountGetterCallback activeConnectionsCountGetterCallback,
                                   ReadCallback readCallback,
                                   WriteCallback writeCallback)
    : m_socketID(socketID)
    , m_messagesReceivedCount(0UL)
    , m_activeConnectionsCountGetterCallback(activeConnectionsCountGetterCallback)
    , m_readCallback(readCallback)
    , m_writeCallback(writeCallback)
    , m_messageDataProcessor([this](const std::string &msg) { return ProcessClientMessage(msg); })
{
}

void ClientConnection::HandleClientConnection()
{
  while (true)
  {
    std::string receivedBytes;

    if (!ReadNextBytesFromClient(receivedBytes))
      break;

    if (!m_messageDataProcessor.ProcessReceivedBytes(receivedBytes))
      break;
  }
}

bool ClientConnection::ReadNextBytesFromClient(std::string &out_Msg) const
{
  auto readResult = m_readCallback(m_socketID, out_Msg);
  
  if (readResult == 0)
    DEBUG_LOG("ClientConnection: Client disconnected.\n");

  return readResult > 0;
}

bool ClientConnection::ProcessClientMessage(const std::string &msg)
{
  if (StrUtils::IsClientMessageInfoRequest(msg))
    return WriteInfoMessageToClient();

  ++m_messagesReceivedCount;
  return WriteEchoMessageToClient(msg);
}