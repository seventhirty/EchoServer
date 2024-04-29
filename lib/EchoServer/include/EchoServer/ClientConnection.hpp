#pragma once

#include <string>
#include <functional>

#include "EchoServer/StrUtils.hpp"
#include "EchoServer/EchoServerConfig.hpp"
#include "EchoServer/MessageDataProcessor.hpp"

class ClientConnection
{
public:
  using ActiveConnectionsCountGetterCallback = std::function<int()>;
  using ReadCallback = std::function<ssize_t(int, std::string &)>;
  using WriteCallback = std::function<ssize_t(int, const std::string &)>;

  ClientConnection(int socketID,
                   ActiveConnectionsCountGetterCallback activeConnectionsCountGetterCallback,
                   ReadCallback readCallback,
                   WriteCallback writeCallback);

  void HandleClientConnection();

private:
  ClientConnection(const ClientConnection &) = delete;
  ClientConnection &operator=(const ClientConnection &) = delete;

  bool ProcessClientMessage(const std::string &msg);
  bool ReadNextBytesFromClient(std::string &out_Msg) const;
  bool WriteInfoMessageToClient() const;
  bool WriteEchoMessageToClient(const std::string &clientMsg) const;

  int m_socketID;
  unsigned long m_messagesReceivedCount;
  ActiveConnectionsCountGetterCallback m_activeConnectionsCountGetterCallback;
  ReadCallback m_readCallback;
  WriteCallback m_writeCallback;
  MessageDataProcessor m_messageDataProcessor;
};

inline bool ClientConnection::WriteInfoMessageToClient() const
{
  return m_writeCallback(m_socketID, StrUtils::FormatInfoStr( 
    m_activeConnectionsCountGetterCallback(), 
    m_messagesReceivedCount)) >= 0;
}

inline bool ClientConnection::WriteEchoMessageToClient(const std::string &clientMsg) const
{
  return m_writeCallback(m_socketID, clientMsg) >= 0;
}