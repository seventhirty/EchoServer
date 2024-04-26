#define CATCH_CONFIG_MAIN // TODO (avelkov): This tells Catch to provide a main() - only do this in one cpp file

// THIS IS A TEST FOR THE UNIT TESTS FRAMEWORK
// TODO (avelkov): more sensible unit tests

// https://github.com/catchorg/Catch2/blob/v2.x/docs/tutorial.md#scaling-up
// TODO (avelkov): proper include path
// g++ ./../src/factorial.cpp test_factorial.cpp -I./..//extern/Catch2/include

#include "catch.hpp"
#include "./../src/EchoServerUtils.hpp"
#include "./../src/EchoServerConfig.hpp"

TEST_CASE("String Format Utils(Test Unit Tests Actually)", "[EchoServerUtils]")
{
  std::string minLengthStr(CFG_ECHO_SERVER_INFO_CMD_STR_CONNECTIONS_COUNT);

  minLengthStr += std::to_string(0);
  minLengthStr += '\n';
  minLengthStr += CFG_ECHO_SERVER_INFO_CMD_STR_MSGS_COUNT;
  minLengthStr += std::to_string(0);
  minLengthStr += '\n';

  REQUIRE(EchoServerUtils::FormatInfoStr(1, 1).size() == minLengthStr.size());
  REQUIRE(EchoServerUtils::FormatInfoStr(10, 1).size() == minLengthStr.size() + 1);
  REQUIRE(EchoServerUtils::FormatInfoStr(1, 10).size() == minLengthStr.size() + 1);
}