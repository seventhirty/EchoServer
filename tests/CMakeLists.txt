cmake_minimum_required(VERSION 3.19)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

################################################################################

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

################################################################################

add_executable(NetworkService_test lib/NetworkService/NetworkService_test.cpp)

target_link_libraries(NetworkService_test
 PRIVATE
  gtest_main 
  gmock_main
  NetworkService)

add_test(NetworkService_gtest NetworkService_test)

################################################################################

add_executable(EchoServer_test lib/EchoServer/EchoServer_test.cpp)

target_link_libraries(EchoServer_test
 PRIVATE
  gtest_main 
  gmock_main
  NetworkService
  EchoServer)

add_test(EchoServer_gtest EchoServer_test)

################################################################################