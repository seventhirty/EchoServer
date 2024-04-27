project(EchoServer)

add_library(EchoServer SHARED
    src/ClientConnectionHandler.cpp
    src/EchoServer.cpp
)

target_include_directories(Core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(EchoServer PRIVATE Core)
target_link_libraries(EchoServer PRIVATE SocketInterface)