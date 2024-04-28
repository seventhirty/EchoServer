#pragma once

#include <string>
#include <functional>

class ClientConnectionHandler
{
public:
  using ActiveConnectionsCountGetterCallback = std::function<int()>;
  using ReadCallback = std::function<ssize_t(int, std::string &)>;
  using WriteCallback = std::function<ssize_t(int, const std::string &)>;

  ClientConnectionHandler(int socketID,
                          ActiveConnectionsCountGetterCallback activeConnectionsCountGetterCallback,
                          ReadCallback readCallback,
                          WriteCallback writeCallback);

  void HandleClientEchoConnection();

private:
  ClientConnectionHandler(const ClientConnectionHandler &) = delete;
  ClientConnectionHandler &operator=(const ClientConnectionHandler &) = delete;

  bool IsClientMessageInfoRequest(const std::string &msg) const;
  bool ReadClientMessage(std::string &out_Msg) const; // TODO Rename
  bool WriteInfoMessageToClient() const;
  bool WriteEchoMessageToClient(const std::string &clientMsg) const;

  int m_socketID;

  ActiveConnectionsCountGetterCallback m_activeConnectionsCountGetterCallback;
  ReadCallback m_readCallback;
  WriteCallback m_writeCallback;

  unsigned long m_messagesReceivedCount;
};