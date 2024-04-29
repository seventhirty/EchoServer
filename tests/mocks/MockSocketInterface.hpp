#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "NetworkService/ISocketInterface.hpp"

class MockSocketInterface : public ISocketInterface
{
public:
  MOCK_METHOD(int, CreateSocket, (int domain, int type, int protocol), (const override));
  MOCK_METHOD(int, Bind, (int socketFD, const sockaddr *socketAddress, socklen_t addrlen), (const override));
  MOCK_METHOD(int, Listen, (int socketFD, int maxPendingConnectionsCount), (const override));
  MOCK_METHOD(int, Accept, (int socketFD, sockaddr *out_socketAddress, socklen_t *out_addrLen), (const override));
  MOCK_METHOD(int, Close, (int socketFD), (const override));
  MOCK_METHOD(ssize_t, Read, (int socketFD, void *buffer, size_t nBytes), (const override));
  MOCK_METHOD(ssize_t, Write, (int socketFD, const void *buffer, size_t nBytes), (const override));
  MOCK_METHOD(ssize_t, SetOption, (int socketFD, int protocolLevel, int optionName, const void *optionValue, socklen_t optionLen), (const override));
};