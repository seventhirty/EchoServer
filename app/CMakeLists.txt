cmake_minimum_required(VERSION 3.19)

project(EchoServerApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(EchoServerApp src/main.cpp)

set(CC_COMMON_COMPILE_OPTIONS "-Wall" "-Wextra" "-Wpedantic")
set(CC_COMPILE_DEBUG_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-g" "-DDEBUG")
set(CC_COMPILE_RELEASE_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-O3" "-DNDEBUG")

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${CC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${CC_COMPILE_RELEASE_OPTIONS}>")

target_link_libraries(${PROJECT_NAME} PRIVATE Core EchoServer NetworkService)





# include(CTest)
# enable_testing()

# file(GLOB_RECURSE SRC_FILES "src/*.cpp")
# include_directories(${PROJECT_SOURCE_DIR}/src)

# add_executable(EchoServer ${SRC_FILES})

# set(CC_COMMON_COMPILE_OPTIONS "-Wall" "-Wextra" "-Wpedantic")
# set(CC_COMPILE_DEBUG_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-g" "-DDEBUG")
# set(CC_COMPILE_RELEASE_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-O3" "-DNDEBUG")

# target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${CC_COMPILE_DEBUG_OPTIONS}>")
# target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${CC_COMPILE_RELEASE_OPTIONS}>")

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
