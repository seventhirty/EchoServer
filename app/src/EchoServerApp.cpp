#include "EchoServerApp.hpp"

#include <cstdlib>
#include <cstdint>

#include "EchoServer/EchoServer.hpp"
#include "NetworkService/SocketInterface.hpp"
#include "Core/Debug.hpp"
#include "Core/StrUtils.hpp"

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
    DEBUG_LOG_ERROR("Exception thrown: %s\n", e.what());
    result = EXIT_FAILURE;
  }

  return result;
}

int EchoServerApp::ResolvePort(int argc, char *argv[]) const
{
  constexpr unsigned long validPortMinValue = 1024;
  constexpr unsigned long validPortMaxValue = UINT16_MAX;

  int port = CFG_ECHO_SERVER_DEFAULT_PORT;

  if (argc >= 2)
  {
    try
    {
      unsigned long portArg = StrUtils::ParseUL(argv[1]);

      if (portArg < validPortMinValue || portArg > validPortMaxValue)
        throw std::runtime_error("invalid port argument");

      port = static_cast<int>(portArg);
    }
    catch(const std::exception& e)
    {
      DEBUG_LOG_ERROR("Error parsing provided port argument. Will use default one.\n");
    }
  }

  return port;
}