# TCP Multi-User Chat

The server uses `select()` to monitor clients and sends each message to the other connected users. Start one server and multiple clients.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client       # run in two or more separate terminals
```

This is a learning example: it has no authentication or encryption.

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Set the server address to `127.0.0.1:9000` and connect using `connect()`.
4. Read the user name and send it to the server.
5. Call `fork()` to create a sender process.
6. In the child, read and send messages using `send()`.
7. In the parent, use `recv()` to receive and display messages until the connection closes.
8. Close the socket using `close()`.
9. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Initialize the table of client sockets and names.
3. Create a TCP socket, bind it to `INADDR_ANY` on port 9000, and call `listen()`.
4. Use `select()` to wait for the listening socket or a client socket to become readable.
5. For a new connection, use `accept()`, receive the name, and store the client in the table.
6. For a readable client socket, receive the message and remove the client if it disconnected.
7. Otherwise, prefix the message with the sender's name and send it to the other clients.
8. Repeat the `select()` loop until stopped.
9. Stop the program.
