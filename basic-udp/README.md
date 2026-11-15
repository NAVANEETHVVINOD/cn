# UDP Basic Client–Server

Connectionless greeting exchange using datagrams.

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
3. Set the server address to `127.0.0.1:12345`.
4. Send the greeting using `sendto()`.
5. Receive and display the reply using `recvfrom()`.
6. Close the socket using `close()`.
7. Stop the program.

### **UDP Server Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket and bind it to `INADDR_ANY` on port 12345.
3. Receive a request and record the sender's address and port using `recvfrom()`.
4. Display the client greeting.
5. Send the server greeting using `sendto()`.
6. Close the socket using `close()`.
7. Stop the program.
