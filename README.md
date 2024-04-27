------------------------------------------------------------------------
Build
------------------------------------------------------------------------
Make sure you have Make and GCC installed:

```
sudo apt update
sudo apt install build-essential
sudo apt install cmake
```

Building Debug:
```
cmake -S . -B build/debug/ -D CMAKE_BUILD_TYPE=Debug
cmake --build build/debug/
```

Building Release:
```
cmake -S . -B build/release/ -D CMAKE_BUILD_TYPE=Release
cmake --build build/release/
```

------------------------------------------------------------------------
Usage
------------------------------------------------------------------------

* See EchoServerConfig.hpp for the port (currently it's: 50022)
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
  
* Implement proepr server config (cmd args, cfg file, env vars..)? 
  - All the config settings are hard-coded currently (including port)

* Should we count the info command as a message
  - Info request (anything that starts with '>' is considered and info request and not counted as a message)

* Should we report message count for the current user only? And for the current session only?
  - We are reporting only the message count for each individual user session.

------------------------------------------------------------------------
TODO
------------------------------------------------------------------------

* Sending more than CFG_ECHO_SERVER_MAX_CLIENT_MSG_LEN bytes from client results
  in multiple reads, which in turn makes the message counter incorrect (this is
  connected to the way we handle timeouts)

* There is a hard-coded timeout period - clients are disconnected if idle for
  CFG_ECHO_SERVER_TIMEOUT_SECONDS seconds. 
  Active sessions counter for timed-out sessions is updated with a latency (less than the timeout period) 

* Write unit tests and refactor if needed. Integrate mock library. Create a makefile.

* Consider using a thread pool for scalability (or other approaches)
* There is no way to stop the server except killing it.
* Test with non-newline terminated client requests
* After a certain amount of messages (unsigned long max), msg sent counter overflows and goes back to 0 
* Use exceptions to make code more readable?
* Place comments where needed for clarity
* Inline small functions?
