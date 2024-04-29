#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "EchoServer/EchoServer.hpp"
#include "NetworkService/NetworkService.hpp"
#include "NetworkService/ISocketInterface.hpp"
#include "MockSocketInterface.hpp"

TEST(EchoServer_Test, EchoServer_ConstructorInit)
{
  MockSocketInterface *socketInterfacePtr = new MockSocketInterface();
  EchoServer s{std::move(std::unique_ptr<ISocketInterface>(socketInterfacePtr))};

  EXPECT_EQ(s.GetActiveConnectionsCount(), 0);
}

TEST(EchoServer_Test, EchoServer_Run_Error_InitListeningSocket)
{
  MockSocketInterface *socketInterfacePtr = new MockSocketInterface();

  EXPECT_CALL(*socketInterfacePtr, CreateSocket).WillOnce(testing::Return(-1));
  EXPECT_CALL(*socketInterfacePtr, Accept).Times(0);
  EXPECT_CALL(*socketInterfacePtr, Close).Times(0);
  EXPECT_CALL(*socketInterfacePtr, Read).Times(0);
  EXPECT_CALL(*socketInterfacePtr, Write).Times(0);
  EXPECT_CALL(*socketInterfacePtr, SetOption).Times(0);

  EchoServer s{std::move(std::unique_ptr<ISocketInterface>(socketInterfacePtr))};

  EXPECT_EQ(s.GetActiveConnectionsCount(), 0);
  EXPECT_EQ(s.Run(1), EXIT_FAILURE);
}