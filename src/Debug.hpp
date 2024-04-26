#pragma once

#include <cstdlib>
#include <cerrno>  // errno
#include <cstring> // std::strerror

#ifdef NDEBUG
#define DEBUG_LOG(...) (void)0
#else
#define DEBUG_LOG(...) fprintf(stdout, __VA_ARGS__)
#endif

#ifdef NDEBUG
#define DEBUG_LOG_ERROR(...) (void)0
#else
#define DEBUG_LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#endif

// TODO (avelkov) : make DEBUG_ASSERT more useful
#ifdef NDEBUG
#define DEBUG_ASSERT(condition, ...) ((void)0)
#else
#define DEBUG_ASSERT(condition, fmt, ...)                                    \
  do                                                                         \
  {                                                                          \
    if (!(condition))                                                        \
    {                                                                        \
      DEBUG_LOG_ERROR("Assertion failed: %s\n" fmt "\nFile: %s\nLine: %d\n", \
                      #condition, ##__VA_ARGS__, __FILE__, __LINE__);        \
      abort();                                                               \
    }                                                                        \
  } while (false)
#endif