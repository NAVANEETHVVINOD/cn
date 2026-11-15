# TCP Basic Client–Server

Demonstrates reliable, connection-oriented communication. The client sends a greeting and the server replies.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server              # terminal 1
./client              # terminal 2
```

Expected result: the server prints `Hello from client`; the client prints `Hello from server`.

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Set the server address to `127.0.0.1:12345` and connect using `connect()`.
4. Send the client greeting using `send()`.
5. Read the server greeting using `read()` and display it.
6. Close the socket using `close()`.
7. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Bind the socket to `INADDR_ANY` on port 12345 using `bind()`.
4. Listen using `listen()` and accept a client using `accept()`.
5. Read and display the client greeting using `read()`.
6. Send the server greeting using `send()`.
7. Close the client and listening sockets.
8. Stop the program.
