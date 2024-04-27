#pragma once

#include <string>
#include <functional>

class ClientConnectionHandler
{
public:
  using ActiveConnectionsCountGetterCallback = std::function<int()>;

  ClientConnectionHandler(int socketID, ActiveConnectionsCountGetterCallback callback);
  void HandleClientEchoConnection();

private:
  ClientConnectionHandler(const ClientConnectionHandler &) = delete;
  ClientConnectionHandler &operator=(const ClientConnectionHandler &) = delete;

  bool IsClientMessageInfoRequest(const std::string &msg) const;
  bool ReadClientMessage(std::string &out_Msg) const;
  bool WriteInfoMessageToClient() const;
  bool WriteEchoMessageToClient(const std::string &clientMsg) const;

  ActiveConnectionsCountGetterCallback m_activeConnectionsCountGetterCallback;
  int m_socketID;
  unsigned long m_messagesReceivedCount;
};