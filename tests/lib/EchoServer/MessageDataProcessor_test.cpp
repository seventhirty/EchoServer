#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "EchoServer/MessageDataProcessor.hpp"

namespace
{
  class MessageDataProcessorTest : public testing::Test
  {
  protected:
    void SetUp() override
    {
      msgDataProcessor = std::make_unique<MessageDataProcessor>(fullMessageHandlerCallback.AsStdFunction());
    }

    testing::MockFunction<bool(const std::string &)> fullMessageHandlerCallback;
    std::unique_ptr<MessageDataProcessor> msgDataProcessor;
  };

  TEST_F(MessageDataProcessorTest, Full)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("full\n")).WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("full\n"), true);
  }

  TEST_F(MessageDataProcessorTest, Partial)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call).Times(0);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("partial"), true);
  }

  TEST_F(MessageDataProcessorTest, Empty)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call).Times(0);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes(""), true);
  }

  TEST_F(MessageDataProcessorTest, NewlineOnly)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("\n")).WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("\n"), true);
  }

  TEST_F(MessageDataProcessorTest, FullPartial)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("full\n")).WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("full\npartial"), true);
  }

  TEST_F(MessageDataProcessorTest, FullFull)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("full\n")).WillOnce(testing::Return(true));
    EXPECT_CALL(fullMessageHandlerCallback, Call("full2\n")).WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("full\nfull2\n"), true);
  }

  TEST_F(MessageDataProcessorTest, PartialThenFull)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("partialfull\n")).WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("partial"), true);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("full\n"), true);
  }

  TEST_F(MessageDataProcessorTest, PartialThenPartial)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call).Times(0);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("partial"), true);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("partial2"), true);
  }

  TEST_F(MessageDataProcessorTest, PartialThenNewline)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("partial\n")).WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("partial"), true);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("\n"), true);
  }

  TEST_F(MessageDataProcessorTest, PartialThenFullPartial)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("partialfull\n")).WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("partial"), true);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("full\npartial2"), true);
  }

  TEST_F(MessageDataProcessorTest, NewlineTwice)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("\n"))
      .WillOnce(testing::Return(true))
      .WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("\n\n"), true);
  }

  TEST_F(MessageDataProcessorTest, NewlineThenNewline)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("\n"))
      .WillOnce(testing::Return(true))
      .WillOnce(testing::Return(true));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("\n"), true);
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("\n"), true);
  }

  TEST_F(MessageDataProcessorTest, CallbackFailFull)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("full\n")).WillOnce(testing::Return(false));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("full\n"), false);
  }

  TEST_F(MessageDataProcessorTest, CallbackFailNewlineOnly)
  {
    EXPECT_CALL(fullMessageHandlerCallback, Call("\n")).WillOnce(testing::Return(false));
    EXPECT_EQ(msgDataProcessor->ProcessReceivedBytes("\n"), false);
  }
}
