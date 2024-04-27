project(Core)

add_library(Core SHARED
    src/StringFormatUtils.cpp
)

target_include_directories(Core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
