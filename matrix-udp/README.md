# UDP Matrix Classification

Classifies a square matrix as diagonal, upper triangular, lower triangular, or ordinary. Enter its order (1 to 10) followed by its entries in row-major order on one line.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in one terminal and `./client` in another. Run both in this folder on the same machine. The server listens on port 9101 and stays running until you press Ctrl+C.

Example input is `2 1 0 0 4`.

The client displays `Matrix type: Diagonal`.

## **Algorithm to write in your lab record**

### **UDP Client Algorithm**

1. Start the program.
2. Enter the order and row-major matrix entries on one line.
3. Create an IPv4 UDP socket using `socket()`.
4. Set the server address to `127.0.0.1:9101` and call `connect()`.
5. Send the request as a single datagram using `send()`.
6. Receive the response datagram using `recv()`.
7. Close the socket using `close()`.
8. Display the result.
9. Stop the program.

### **UDP Server Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9101 using `bind()`.
4. Receive a datagram and the client's address using `recvfrom()`.
5. Read and validate the matrix order.
6. Initialize the `upper` and `lower` flags to true.
7. Read exactly `N × N` entries. Clear `upper` for a nonzero entry below the diagonal and `lower` for a nonzero entry above it.
8. If both flags are set, report diagonal. If only one is set, report the matching triangular type. Otherwise report ordinary.
9. Send the result to the sender using `sendto()`.
10. Repeat for the next request until stopped.
11. Stop the program.
