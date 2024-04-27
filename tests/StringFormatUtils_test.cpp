#include <gtest/gtest.h>
#include "Core/StringFormatUtils.hpp"

class FormatInfoStrTest : public ::testing::Test
{
};

TEST_F(FormatInfoStrTest, FormatsTypicalInputCorrectly)
{
  EXPECT_EQ(StringFormatUtils::FormatInfoStr("c: ", 1, "m: ", 2), "c: 1\nm: 2\n");
  EXPECT_EQ(StringFormatUtils::FormatInfoStr("", 1, "", 2), "1\n2\n");
}