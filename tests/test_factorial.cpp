#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file

// https://github.com/catchorg/Catch2/blob/v2.x/docs/tutorial.md#scaling-up

// TODO : proper include path

// g++ ./../src/factorial.cpp test_factorial.cpp -I./..//extern/Catch2/include

#include "catch.hpp"
#include "./../src/factorial.hpp"

TEST_CASE("Factorials are computed", "[factorial]")
{
  REQUIRE(MyFactorial(0) == 1);
  REQUIRE(MyFactorial(1) == 1);
  REQUIRE(MyFactorial(2) == 2);
  REQUIRE(MyFactorial(3) == 6);
  REQUIRE(MyFactorial(10) == 3628800);
}