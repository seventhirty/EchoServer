project(SocketInterface)

add_library(SocketInterface SHARED
    src/SocketInterface.cpp
)

target_include_directories(SocketInterface PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(SocketInterface PRIVATE Core)