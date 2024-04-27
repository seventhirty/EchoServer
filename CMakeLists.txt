cmake_minimum_required(VERSION 3.10)
project(EchoServer VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

file(GLOB_RECURSE SRC_FILES "src/*.cpp")
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(EchoServer ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
