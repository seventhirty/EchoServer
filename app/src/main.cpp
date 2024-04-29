#include "EchoServer/EchoServer.hpp"
#include "NetworkService/NetworkService.hpp"
#include "NetworkService/SocketInterface.hpp"
#include "Core/Debug.hpp"

int main()
{
  int result = EXIT_SUCCESS;
  try
  {
    EchoServer server{std::move(std::make_unique<SocketInterface>())};
    result = server.Run();
  }
  catch (const std::exception &e)
  {
    DEBUG_LOG_ERROR("Exception thrown: %s", e.what());
    result = EXIT_FAILURE;
  }

  return result;
}
