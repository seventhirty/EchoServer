#include <gtest/gtest.h>
#include "Core/StringFormatUtils.hpp"

TEST(FormatInfoStr_Test, FormatCorrect)
{
  EXPECT_EQ(StringFormatUtils::FormatInfoStr("c: ", 1, "m: ", 2), "c: 1\nm: 2\n");
  EXPECT_EQ(StringFormatUtils::FormatInfoStr("", 1, "", 2), "1\n2\n");
}