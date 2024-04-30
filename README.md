------------------------------------------------------------------------
Build
------------------------------------------------------------------------
Make sure you have Make and GCC installed:

```
sudo apt update
sudo apt install build-essential
sudo apt install cmake
```

Building Debug from the root project dir:
```
cmake -S . -B build/debug/ -D CMAKE_BUILD_TYPE=Debug
cmake --build build/debug/
```

Running Debug tests from the root project dir:
```
ctest --test-dir build/debug
```

Building Release from the root project dir:
```
cmake -S . -B build/release/ -D CMAKE_BUILD_TYPE=Release
cmake --build build/release/
```

Running Release tests from the root project dir:
```
ctest --test-dir build/release
```

------------------------------------------------------------------------
Usage
------------------------------------------------------------------------

* Start by providing port or not.
* If no port is provided, default port (51337) is used

* Examples for running from the root project dir:
```
./build/debug/app/EchoServerApp
./build/release/app/EchoServerApp 50000
```

* Connect to the server using a TCP client program, for example - telnet
```
telnet localhost 50001
telnet 192.168.0.189 50000
telnet ::1 51337
```

* Any lines sent from clients that start with '>' are considered as "info requests"

------------------------------------------------------------------------
Requirements Specification Questions:
------------------------------------------------------------------------

* What is the build target OS and tech to be used?
  - Currently we use C++17 and build for Ubunutu, using posix sockets

* Implement Client?
  - There is no client application. Tested with telnet (Ubuntu & Windows 11)

* Implement application-level protocol?
  - Currently we do raw echoes and anything that starts with '>' is considered an info request
  
* Should we count the info command as a message
  - Info request (anything that starts with '>') is not counted as a message

* Should we report message count for the current user only? And for the current session only?
  - We are reporting only the message count for each individual user session.

* What encoding should be supported?
  - Currently it's ANSI only

------------------------------------------------------------------------
TODO
------------------------------------------------------------------------

* There is a hard-coded timeout period - clients are disconnected if idle for
  CFG_ECHO_SERVER_TIMEOUT_SECONDS seconds. 
  Active sessions counter is updated with a latency equal
  to this timeout period in the worst case, if clients don't properly close the connection. 

* Using a separate thread per client connection with a single server process does not scale well.
  - Look into using a thread pool with std::thread::hardware_concurrency threads
  - Look into: http://www.kegel.com/c10k.html
  - Look into: https://highscalability.com/the-secret-to-10-million-concurrent-connections-the-kernel-i/


* Implement proper shutdown - handle signals and release thread resources, close sockets

* After a certain amount of messages (unsigned long max), msg sent counter overflows and goes back to 0 
