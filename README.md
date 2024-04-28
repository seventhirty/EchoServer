------------------------------------------------------------------------
Build
------------------------------------------------------------------------
Make sure you have Make and GCC installed:

```
sudo apt update
sudo apt install build-essential
sudo apt install cmake
```

Building Debug from the root dir:
```
cmake -S . -B build/debug/ -D CMAKE_BUILD_TYPE=Debug
cmake --build build/debug/
```

Running Debug tests from the root dir:
```
ctest --test-dir build/debug
```

Building Release from the root dir:
```
cmake -S . -B build/release/ -D CMAKE_BUILD_TYPE=Release
cmake --build build/release/
```

Running Release tests from the root dir:
```
ctest --test-dir build/release
```

------------------------------------------------------------------------
Usage
------------------------------------------------------------------------

* See EchoServerConfig.hpp for the port (currently it's: 50026)
* Connect to the server using a TCP client program, for example - telnet
* Anything sent from clients that starts with '>' is considered an info request

------------------------------------------------------------------------
Requirements Specification Questions:
------------------------------------------------------------------------

* What is the build target OS and tech to be used?
  - Currently we use C++17 and build for Ubunutu, using the sockets posix library and std threads

* Implement Client?
  - There is no client application. Tested with telnet (Ubuntu & Windows 11)

* Implement application-level protocol?
  - Currently we do raw echoes and anything that starts with '>' is considered an info request
  
* Implement proper server config (cmd args, cfg file, env vars..)? 
  - All the config settings are hard-coded currently (including port) in a single hearder file.

* Should we count the info command as a message
  - Info request (anything that starts with '>') is not counted as a message

* Should we report message count for the current user only? And for the current session only?
  - We are reporting only the message count for each individual user session.

* What encoding should be supported?
  - Currently it's ANSI only

* Should IPv6 be supported?
  - Currently it's not supported

------------------------------------------------------------------------
TODO
------------------------------------------------------------------------

* Implement proper shutdown - handle signals and release thread resources, close sockets

* There is a hard-coded timeout period - clients are disconnected if idle for
  CFG_ECHO_SERVER_TIMEOUT_SECONDS seconds. 
  Active sessions counter for timed-out sessions is updated with a latency equal
  to this timeout period in the worst case. 

* Don't use a separate thread per client connection (does not scale well)

* Refactor ClientConnectionHandler and EchoServer iceberg classes to be more easily testable and write unit tests

* After a certain amount of messages (unsigned long max), msg sent counter overflows and goes back to 0 
* Use exceptions to make code more readable?
