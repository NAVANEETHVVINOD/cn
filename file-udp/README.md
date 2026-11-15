# Concurrent UDP File Server

The client requests a short text file by name. A child process sends its process ID and the file contents in one UDP response, and the client prints the response.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```

Run the client from a separate directory or request only a controlled test file. This small lab protocol does **not** implement sequencing, retransmission, or safe path validation, so it is suitable only for localhost demonstrations.

## **Algorithm to write in your lab record**

### **UDP Client Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket using `socket()`.
3. Set the server address to `127.0.0.1:9000`.
4. Read the filename and send it using `sendto()`.
5. Receive and print the response using `recvfrom()`.
6. Close the socket using `close()`.
7. Stop the program.

### **UDP Server Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket and bind it to `INADDR_ANY` on port 9000.
3. Receive a request and record the sender's address and port using `recvfrom()`.
4. Call `fork()` to handle the request in a child while the parent waits for more requests.
5. Open the requested file using `fopen()` and start the response with the child process ID.
6. Append the file contents if the file opens, or append a file-not-found message.
7. Send the response as one datagram using `sendto()` and exit the child.
8. Repeat in the parent until stopped.
9. Stop the program.
