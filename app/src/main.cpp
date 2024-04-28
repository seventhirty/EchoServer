#include "EchoServer/EchoServer.hpp"
#include "NetworkService/NetworkService.hpp"
#include "NetworkService/SocketInterface.hpp"
#include "Core/Debug.hpp"

int main()
{
  int result = EXIT_SUCCESS;
  try
  {
    auto socketInterfacePtr{std::make_unique<SocketInterface>()};
    auto networkServicePtr{std::make_unique<NetworkService>(std::move(socketInterfacePtr))};
    EchoServer server{std::move(networkServicePtr)};

    result = server.Run();
  }
  catch (const std::exception &e)
  {
    DEBUG_LOG_ERROR("Exception thrown: %s", e.what());
    result = EXIT_FAILURE;
  }

  return result;
}
