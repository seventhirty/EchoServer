#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "NetworkService/NetworkService.hpp"
#include "mocks/MockSocketInterface.hpp"

namespace
{
  class NetworkServiceTest : public ::testing::Test
  {
  protected:
    void SetUp() override
    {
      socketInterface = new MockSocketInterface();
      networkService = std::make_unique<NetworkService>(std::move(std::unique_ptr<ISocketInterface>(socketInterface)));
    }

    MockSocketInterface *socketInterface;
    std::unique_ptr<NetworkService> networkService;
  };

  TEST_F(NetworkServiceTest, CreateSocketFailure)
  {
    EXPECT_CALL(*socketInterface, CreateSocket).WillOnce(testing::Return(-1));
    EXPECT_CALL(*socketInterface, Bind).Times(0);
    EXPECT_CALL(*socketInterface, Listen).Times(0);
    EXPECT_CALL(*socketInterface, Close).Times(0);
    EXPECT_EQ(networkService->CreateListeningSocket(0U, 1), -1);
  }

  TEST_F(NetworkServiceTest, BindSocketFailure)
  {
    EXPECT_CALL(*socketInterface, CreateSocket).WillOnce(testing::Return(1));
    EXPECT_CALL(*socketInterface, Bind).WillOnce(testing::Return(-1));
    EXPECT_CALL(*socketInterface, Listen).Times(0);
    EXPECT_CALL(*socketInterface, Close).Times(1);
    EXPECT_EQ(networkService->CreateListeningSocket(0U, 1), -1);
  }

  TEST_F(NetworkServiceTest, ListenSocketFailure)
  {
    EXPECT_CALL(*socketInterface, CreateSocket).WillOnce(testing::Return(1));
    EXPECT_CALL(*socketInterface, Bind).WillOnce(testing::Return(1));
    EXPECT_CALL(*socketInterface, Listen).WillOnce(testing::Return(-1));
    EXPECT_CALL(*socketInterface, Close).Times(1);
    EXPECT_EQ(networkService->CreateListeningSocket(0U, 1), -1);
  }

  TEST_F(NetworkServiceTest, ListenSocketSuccess)
  {
    EXPECT_CALL(*socketInterface, CreateSocket).WillOnce(testing::Return(1));
    EXPECT_CALL(*socketInterface, Bind).WillOnce(testing::Return(1));
    EXPECT_CALL(*socketInterface, Listen).Times(1);
    EXPECT_CALL(*socketInterface, Close).Times(0);
    EXPECT_EQ(networkService->CreateListeningSocket(0U, 1), 1);
  }

  TEST_F(NetworkServiceTest, AcceptFailure)
  {
    EXPECT_CALL(*socketInterface, Accept).WillOnce(testing::Return(-1));
    EXPECT_EQ(networkService->Accept(1), -1);
  }

  TEST_F(NetworkServiceTest, AcceptSuccess)
  {
    EXPECT_CALL(*socketInterface, Accept).WillOnce(testing::Return(1));
    EXPECT_EQ(networkService->Accept(1), 1);
  }

  TEST_F(NetworkServiceTest, AcceptInvalidArgs)
  {
    EXPECT_CALL(*socketInterface, Accept).Times(0);
    EXPECT_EQ(networkService->Accept(-1), -1);
  }

  TEST_F(NetworkServiceTest, ReadNextBytesInvalidSocketArgs)
  {
    EXPECT_CALL(*socketInterface, Read).Times(0);
    std::string result;
    EXPECT_EQ(networkService->ReadNextBytes(-1, result), -1);
  }

  TEST_F(NetworkServiceTest, ReadNextBytesClearInParamStringResult)
  {
    EXPECT_CALL(*socketInterface, Read).WillOnce(testing::Return(0));

    std::string result("non-empty in_param is an error");
    
    EXPECT_EQ(networkService->ReadNextBytes(1, result), 0);
    EXPECT_EQ(result.size(), 0);
  }

  TEST_F(NetworkServiceTest, WriteInvalidSocketArgs)
  {
    EXPECT_CALL(*socketInterface, Write).Times(0);
    EXPECT_EQ(networkService->Write(-1, "val"), -1);
  }

  TEST_F(NetworkServiceTest, WriteInvalidEmptyStrArgs)
  {
    EXPECT_CALL(*socketInterface, Write).Times(0);
    EXPECT_EQ(networkService->Write(1, ""), 0);
  }

  TEST_F(NetworkServiceTest, WriteSuccess)
  {
    const std::string msg("msg");

    EXPECT_CALL(*socketInterface, Write).WillOnce(testing::Return(msg.size()));
    EXPECT_EQ(networkService->Write(1, msg), msg.size());
  }

  TEST_F(NetworkServiceTest, SetupConnectionTimeoutInvalidSocketArgs)
  {
    EXPECT_CALL(*socketInterface, SetOption).Times(0);
    EXPECT_EQ(networkService->SetupConnectionTimeout(-1, 1), -1);
  }

  TEST_F(NetworkServiceTest, SetupConnectionTimeoutInvalidTimeoutArgs)
  {
    EXPECT_CALL(*socketInterface, SetOption).Times(0);
    EXPECT_EQ(networkService->SetupConnectionTimeout(1, 0), 0);
    EXPECT_EQ(networkService->SetupConnectionTimeout(1, -1), 0);
  }

  TEST_F(NetworkServiceTest, SetupConnectionTimeoutSetOptionFailure)
  {
    EXPECT_CALL(*socketInterface, SetOption).WillOnce(testing::Return(-1));
    EXPECT_EQ(networkService->SetupConnectionTimeout(1, 1), -1);
  }
}
