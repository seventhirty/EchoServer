cmake_minimum_required(VERSION 3.19)

project(EchoServerApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(EchoServerApp src/main.cpp src/EchoServerApp.cpp)

set(CC_COMMON_COMPILE_OPTIONS "-Wall" "-Wextra" "-Wpedantic")
set(CC_COMPILE_DEBUG_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-g" "-DDEBUG")
set(CC_COMPILE_RELEASE_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-O3" "-DNDEBUG")

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${CC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${CC_COMPILE_RELEASE_OPTIONS}>")

target_link_libraries(${PROJECT_NAME} PRIVATE Core EchoServer NetworkService)
