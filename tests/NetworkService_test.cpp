#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "NetworkService/NetworkService.hpp"
#include "NetworkService/ISocketInterface.hpp"
#include "MockSocketInterface.hpp"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_CreateSocketFailure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(-1));
  EXPECT_CALL(*mockSocketPtr, Bind).Times(0);
  EXPECT_CALL(*mockSocketPtr, Listen).Times(0);
  EXPECT_CALL(*mockSocketPtr, Close).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), -1);
}

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_BindSocketFailure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Bind).WillOnce(testing::Return(-1));
  EXPECT_CALL(*mockSocketPtr, Listen).Times(0);
  EXPECT_CALL(*mockSocketPtr, Close).Times(1);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), -1);
}

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_ListenSocketFailure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Bind).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Listen).WillOnce(testing::Return(-1));
  EXPECT_CALL(*mockSocketPtr, Close).Times(1);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), -1);
}

TEST(NetworkService_Test, NetworkService_CreateListeningSocket_ListenSocketSuccess)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, CreateSocket).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Bind).WillOnce(testing::Return(1));
  EXPECT_CALL(*mockSocketPtr, Listen).Times(1);
  EXPECT_CALL(*mockSocketPtr, Close).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.CreateListeningSocket(0U, 1), 1);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST(NetworkService_Test, NetworkService_Accept_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Accept).WillOnce(testing::Return(-1));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Accept(1), -1);
}

TEST(NetworkService_Test, NetworkService_Accept_Success)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Accept).WillOnce(testing::Return(1));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Accept(1), 1);
}

TEST(NetworkService_Test, NetworkService_Accept_InvalidArgs_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Accept).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Accept(-1), -1);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST(NetworkService_Test, NetworkService_ReadNextBytes_InvalidSocketArgs_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Read).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  std::string result;

  EXPECT_EQ(s.ReadNextBytes(-1, result), -1);
}

TEST(NetworkService_Test, NetworkService_ReadNextBytes_ClearInParamStringResult)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Read).WillOnce(testing::Return(0));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  std::string result("non-empty in_param is an error");

  EXPECT_EQ(s.ReadNextBytes(1, result), 0);
  EXPECT_EQ(result.size(), 0);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST(NetworkService_Test, NetworkService_Write_InvalidSocketArgs_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Write).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Write(-1, "val"), -1);
}

TEST(NetworkService_Test, NetworkService_Write_InvalidEmptyStrArgs_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, Write).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Write(1, ""), 0);
}

TEST(NetworkService_Test, NetworkService_Write_Success)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  const std::string msg("msg");

  EXPECT_CALL(*mockSocketPtr, Write).WillOnce(testing::Return(msg.size()));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.Write(1, msg), msg.size());
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

TEST(NetworkService_Test, NetworkService_SetupConnectionTimeout_InvalidSocketArgs_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, SetOption).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.SetupConnectionTimeout(-1, 1), -1);
}

TEST(NetworkService_Test, NetworkService_SetupConnectionTimeout_InvalidTimeoutArgs_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, SetOption).Times(0);

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.SetupConnectionTimeout(1, 0), 0);
  EXPECT_EQ(s.SetupConnectionTimeout(1, -1), 0);
}

TEST(NetworkService_Test, NetworkService_SetupConnectionTimeout_SetOption_Failure)
{
  MockSocketInterface *mockSocketPtr = new MockSocketInterface();

  EXPECT_CALL(*mockSocketPtr, SetOption).WillOnce(testing::Return(-1));

  NetworkService s(std::move(std::unique_ptr<ISocketInterface>(mockSocketPtr)));

  EXPECT_EQ(s.SetupConnectionTimeout(1, 1), -1);
}