#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "EchoServer/EchoServer.hpp"
#include "NetworkService/INetworkService.hpp"

class MockNetworkService : public INetworkService
{
public:
  MOCK_METHOD(int, CreateListeningSocket, (uint16_t portID, int maxPendingConnectionsInQueue), (const override));
  MOCK_METHOD(int, Accept, (int listenSocketFileDescriptor), (const override));
  MOCK_METHOD(int, Close, (int socketFileDescriptor), (const override));
  MOCK_METHOD(ssize_t, ReadNextBytes, (int socketFileDescriptor, std::string &out_strResult), (const override));
  MOCK_METHOD(ssize_t, Write, (int socketFileDescriptor, const std::string &str), (const override));
  MOCK_METHOD(int, SetupConnectionTimeout, (int socketFileDescriptor, time_t timeoutSeconds), (const override));
};

TEST(EchoServer_Test, EchoServer_ConstructorInit)
{
  MockNetworkService *mockNetworkServicePtr = new MockNetworkService();

  EchoServer s(std::move(std::unique_ptr<INetworkService>(mockNetworkServicePtr)));

  EXPECT_EQ(s.GetActiveConnectionsCount(), 0);
}

TEST(EchoServer_Test, EchoServer_Run_Error_InitListeningSocket)
{
  MockNetworkService *mockNetworkServicePtr = new MockNetworkService();

  EXPECT_CALL(*mockNetworkServicePtr, CreateListeningSocket).WillOnce(testing::Return(-1));

  EXPECT_CALL(*mockNetworkServicePtr, Accept).Times(0);
  EXPECT_CALL(*mockNetworkServicePtr, Close).Times(0);
  EXPECT_CALL(*mockNetworkServicePtr, ReadNextBytes).Times(0);
  EXPECT_CALL(*mockNetworkServicePtr, Write).Times(0);
  EXPECT_CALL(*mockNetworkServicePtr, SetupConnectionTimeout).Times(0);

  EchoServer s(std::move(std::unique_ptr<INetworkService>(mockNetworkServicePtr)));
  EXPECT_EQ(s.GetActiveConnectionsCount(), 0);
  EXPECT_EQ(s.Run(), EXIT_FAILURE);
}

// int EchoServer::Run()
// {
//   DEBUG_LOG("EchoServer starting..\n");

//   auto listenSocketFD = InitListeningSocket();

//   if (listenSocketFD < 0)
//     return EXIT_FAILURE;

//   // TODO (avelkov): end loop condition isRunning and a way to stop server (and free port on kill)
//   while (true)
//     AcceptNextClientConnection(listenSocketFD);

//   DEBUG_LOG("EchoServer closing listening socket..\n");

//   return (m_networkService->Close(listenSocketFD) >= 0 ? EXIT_SUCCESS : EXIT_FAILURE);
// }