# Concurrent UDP Time Server

The server receives UDP time requests in a loop and replies to each client with the current time.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```

## **Algorithm to write in your lab record**

### **UDP Client Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket using `socket()`.
3. Set the server address to `127.0.0.1:9000`.
4. Send `TIME` using `sendto()`.
5. Receive and display the time using `recvfrom()`.
6. Close the socket using `close()`.
7. Stop the program.

### **UDP Server Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket and bind it to `INADDR_ANY` on port 9000.
3. Receive a request and record the sender's address and port using `recvfrom()`.
4. Get the current time using `time()` and format it using `ctime()`.
5. Send the formatted time using `sendto()`.
6. Repeat for each request until stopped.
7. Stop the program.
