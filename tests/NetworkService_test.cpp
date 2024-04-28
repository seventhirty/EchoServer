#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "NetworkService/NetworkService.hpp"
#include "NetworkService/ISocketInterface.hpp"

class MockLinuxSocketInterface : public ISocketInterface
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

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_CreateSocketFailure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(-1));
  EXPECT_CALL(*mockSocketPtr, Bind).Times(0);
  EXPECT_CALL(*mockSocketPtr, Listen).Times(0);
  EXPECT_CALL(*mockSocketPtr, Close).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), -1);
}

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_BindSocketFailure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Bind).WillOnce(testing::Return(-1));
  EXPECT_CALL(*mockSocketPtr, Listen).Times(0);
  EXPECT_CALL(*mockSocketPtr, Close).Times(1);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), -1);
}

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_ListenSocketFailure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Bind).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Listen).WillOnce(testing::Return(-1));
  EXPECT_CALL(*mockSocketPtr, Close).Times(1);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), -1);
}

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_ListenSocketSuccess)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Bind).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Listen).Times(1);
  EXPECT_CALL(*mockSocketPtr, Close).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), 1);
}

TEST(NetworkService_Test, NetworkService_Accept_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Accept).WillOnce(testing::Return(-1));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Accept(1), -1);
}

TEST(NetworkService_Test, NetworkService_Accept_Success)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Accept).WillOnce(testing::Return(1));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Accept(1), 1);
}

TEST(NetworkService_Test, NetworkService_Accept_InvalidArgs_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Accept).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Accept(-1), -1);
}

TEST(NetworkService_Test, NetworkService_ReadNextBytes_InvalidSocketArgs_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Read).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  std::string result;

  EXPECT_EQ(s.ReadNextBytes(-1, result), -1);
}

TEST(NetworkService_Test, NetworkService_ReadNextBytes_ClearInParamStringResult)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Read).WillOnce(testing::Return(0));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  std::string result("non-empty in_param is an error");

  EXPECT_EQ(s.ReadNextBytes(1, result), 0);
  EXPECT_EQ(result.size(), 0);
}

TEST(NetworkService_Test, NetworkService_Write_InvalidSocketArgs_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Write).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Write(-1, "val"), -1);
}

TEST(NetworkService_Test, NetworkService_Write_InvalidEmptyStrArgs_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Write).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Write(1, ""), 0);
}

TEST(NetworkService_Test, NetworkService_Write_Success)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  const std::string msg("msg");

  EXPECT_CALL(*mockSocketPtr, Write).WillOnce(testing::Return(msg.size()));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Write(1, msg), msg.size());
}

TEST(NetworkService_Test, NetworkService_SetupConnectionTimeout_InvalidSocketArgs_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, SetOption).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.SetupConnectionTimeout(-1, 1), -1);
}

TEST(NetworkService_Test, NetworkService_SetupConnectionTimeout_InvalidTimeoutArgs_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, SetOption).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.SetupConnectionTimeout(1, 0), 0);
  EXPECT_EQ(s.SetupConnectionTimeout(1, -1), 0);
}

TEST(NetworkService_Test, NetworkService_SetupConnectionTimeout_SetOption_Failure)
{
  MockLinuxSocketInterface *mockSocketPtr = new MockLinuxSocketInterface();

  EXPECT_CALL(*mockSocketPtr, SetOption).WillOnce(testing::Return(-1));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.SetupConnectionTimeout(1, 1), -1);
}