cmake_minimum_required(VERSION 3.19)

project(EchoServerPrj)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(lib/Core)
add_subdirectory(lib/EchoServer)
add_subdirectory(lib/NetworkService)
add_subdirectory(app)
add_subdirectory(tests)