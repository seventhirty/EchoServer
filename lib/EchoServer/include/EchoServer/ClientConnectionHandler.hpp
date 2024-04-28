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

  void HandleClientConnection();

private:
  ClientConnectionHandler(const ClientConnectionHandler &) = delete;
  ClientConnectionHandler &operator=(const ClientConnectionHandler &) = delete;

  bool ProcessReceivedBytes(const std::string &bytes, std::string &unprocessedLeftoverBytes);
  bool ProcessClientMessage(const std::string &msg);

  bool IsClientMessageInfoRequest(const std::string &msg) const;
  bool ReadNextBytesFromClient(std::string &out_Msg) const;
  bool WriteInfoMessageToClient() const;
  bool WriteEchoMessageToClient(const std::string &clientMsg) const;

  int m_socketID;
  unsigned long m_messagesReceivedCount;

  ActiveConnectionsCountGetterCallback m_activeConnectionsCountGetterCallback;
  ReadCallback m_readCallback;
  WriteCallback m_writeCallback;
};