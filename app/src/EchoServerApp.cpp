#include "EchoServerApp.hpp"

#include <cstdlib>

#include "EchoServer/EchoServer.hpp"
#include "NetworkService/SocketInterface.hpp"
#include "Core/Debug.hpp"

#include "EchoServer/EchoServerConfig.hpp"

int EchoServerApp::Run(int argc, char *argv[]) const
{
  int port = ResolvePort(argc, argv);

  int result = EXIT_SUCCESS;

  try
  {
    EchoServer server{std::move(std::make_unique<SocketInterface>())};
    result = server.Run(port);
  }
  catch (const std::exception &e)
  {
    DEBUG_LOG_ERROR("Exception thrown: %s", e.what());
    result = EXIT_FAILURE;
  }

  return result;
}

int EchoServerApp::ResolvePort(int argc, char *argv[]) const
{
  int port = CFG_ECHO_SERVER_DEFAULT_PORT;

  if (argc >= 2)
  {
    int portArg{};
    try
    {
      portArg = std::stoi(argv[1]);
      port = portArg;
    }
    catch(const std::exception& e)
    {
      DEBUG_LOG_ERROR("Error parsing provided port argument");
    }
  }

  return port;
}