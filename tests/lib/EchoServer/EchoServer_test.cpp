#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "EchoServer/EchoServer.hpp"

#include "mocks/MockSocketInterface.hpp"

#include <memory>

namespace
{
  class EchoServerTest : public testing::Test
  {
  protected:
    void SetUp() override
    {
      socketInterface = new MockSocketInterface();
      server = std::make_unique<EchoServer>(std::move(std::unique_ptr<ISocketInterface>(socketInterface)));
    }

    MockSocketInterface *socketInterface;
    std::unique_ptr<EchoServer> server;
  };

  TEST_F(EchoServerTest, ConstructorInit)
  {
    EXPECT_EQ(server->GetActiveConnectionsCount(), 0);
  }

  TEST_F(EchoServerTest, RunInitListeningSocketError)
  {
    EXPECT_CALL(*socketInterface, CreateSocket).WillOnce(testing::Return(-1));
    EXPECT_CALL(*socketInterface, Accept).Times(0);
    EXPECT_CALL(*socketInterface, Close).Times(0);
    EXPECT_CALL(*socketInterface, Read).Times(0);
    EXPECT_CALL(*socketInterface, Write).Times(0);
    EXPECT_CALL(*socketInterface, SetOption).Times(0);

    EXPECT_EQ(server->GetActiveConnectionsCount(), 0);
    EXPECT_EQ(server->Run(1), EXIT_FAILURE);
  }
}
