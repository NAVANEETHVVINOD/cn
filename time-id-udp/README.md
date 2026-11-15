# UDP Time Server with Server ID

Returns the server's local time and its server ID. The server uses the stable ID **CN-TIME-01** and replies to each client's source address and port.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in terminal 1 and run `./client` in terminals 2 and 3. Both clients receive a reply with the same ID. Run both in this folder on the same machine. The server listens on port 9105 and stays running until you press Ctrl+C.

Each reply shows the local time alongside `server_id=CN-TIME-01`.

## **Algorithm to write in your lab record**

### **UDP Client Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket using `socket()`.
3. Set the server address to `127.0.0.1:9105` and call `connect()`.
4. Send `TIME` as one datagram using `send()`.
5. Receive the response datagram using `recv()`.
6. Close the socket using `close()`.
7. Display the time and server ID. Run the same client in a second terminal to verify that both receive a reply.
8. Stop the program.

### **UDP Server Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9105 using `bind()`.
4. Receive a datagram and the client's address using `recvfrom()`.
5. Check that the request is exactly `TIME`.
6. Get and format the server's local time.
7. Build the reply with `server_id=CN-TIME-01` and the formatted time.
8. Send the result to the sender using `sendto()`.
9. Repeat for the next request until stopped.
10. Stop the program.
