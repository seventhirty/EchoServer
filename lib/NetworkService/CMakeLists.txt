project(NetworkService)

add_library(NetworkService SHARED
    src/NetworkService.cpp
)

set(CC_COMMON_COMPILE_OPTIONS "-Wall" "-Wextra" "-Wpedantic")
set(CC_COMPILE_DEBUG_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-g" "-DDEBUG")
set(CC_COMPILE_RELEASE_OPTIONS "${CC_COMMON_COMPILE_OPTIONS}" "-O3" "-DNDEBUG")

target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${CC_COMPILE_DEBUG_OPTIONS}>")
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<CONFIG:Release>:${CC_COMPILE_RELEASE_OPTIONS}>")

target_include_directories(NetworkService PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(NetworkService PRIVATE Core)