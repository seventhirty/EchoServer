#pragma once

#include <string>

class EchoServer;

class EchoServerClientConnection
{
public:
  EchoServerClientConnection(int socketID, EchoServer &server)
      : m_server(server), m_socketID(socketID), m_messagesReceivedCount(0UL) {}

  void HandleClientEchoConnection();

private:
  EchoServerClientConnection(const EchoServer &) = delete;

  bool IsClientMessageInfoRequest(const std::string &msg) const;
  bool ReadClientMessage(std::string &out_Msg);
  bool WriteInfoMessageToClient();
  bool WriteEchoMessageToClient(const std::string &clientMsg);

  EchoServer &m_server;
  int m_socketID;
  unsigned long m_messagesReceivedCount;
};