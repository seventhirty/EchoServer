





Requirements Specification Questions:

* Special formatting for differentiating between info and chat commands
* Should we count the info command as a message (there is no echo for it, but info printing)
* Should we report message count for the current user only? And for the current session only?


TODO

* All the settings are hard-coded (including port)

* Sending more than CFG_ECHO_SERVER_MAX_CLIENT_MSG_LEN bytes from client results
  in multiple reads, which in turn makes the message counter incorrect (this is
  connected to the way we handle timeouts)

* There is a hard-coded timeout period - clients are disconnected if idle for
  CFG_ECHO_SERVER_TIMEOUT_SECONDS seconds.

* Consider using a thread pool for scalability (or other approaches)

* There is no way to stop the server except killing it.

* There is no client application. Tested with telnet (Ubuntu & Windows 11)



* After a certain amount of messages 


- Use exceptions to make code more readable