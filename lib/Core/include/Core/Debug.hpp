#pragma once

#include <cstdio>
#include <cstdlib>
#include <csignal>

#ifdef NDEBUG
#define DEBUG_LOG(...) (void)0
#else
#define DEBUG_LOG(...) fprintf(stderr, __VA_ARGS__)
#endif

#ifdef NDEBUG
#define DEBUG_LOG_ERROR(...) (void)0
#else
#define DEBUG_LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#endif

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
      std::raise(SIGINT);                                                    \
    }                                                                        \
  } while (false)
#endif