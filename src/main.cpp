#include "EchoServer.hpp"
#include "Debug.hpp"

int main()
{
  int result = EXIT_SUCCESS;
  try
  {
    EchoServer server;
    result = server.Run();
  }
  catch (const std::exception &e)
  {
    DEBUG_LOG_ERROR("Exception thrown: %s", e.what());
    result = EXIT_FAILURE;
  }

  return result;
}