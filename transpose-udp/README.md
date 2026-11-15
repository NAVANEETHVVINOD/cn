# UDP Matrix Transpose

Enter the row count and column count (1 to 10 each) followed by the entries in row-major order on one line. The vertical bars separate the rows of the transposed matrix.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in one terminal and `./client` in another. Run both in this folder on the same machine. The server listens on port 9107 and stays running until you press Ctrl+C.

Example input is `2 3 1 2 3 4 5 6`.

The client displays `Transpose (3 x 2): 1 4 | 2 5 | 3 6`.

## **Algorithm to write in your lab record**

### **UDP Client Algorithm**

1. Start the program.
2. Enter the row count, column count, and row-major entries on one line.
3. Create an IPv4 UDP socket using `socket()`.
4. Set the server address to `127.0.0.1:9107` and call `connect()`.
5. Send the request as a single datagram using `send()`.
6. Receive the response datagram using `recv()`.
7. Close the socket using `close()`.
8. Display the transposed dimensions and rows.
9. Stop the program.

### **UDP Server Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9107 using `bind()`.
4. Receive a datagram and the client's address using `recvfrom()`.
5. Validate the dimensions and read the exact number of integer values.
6. Set the output dimensions to columns × rows.
7. For each original column `j`, write a transposed row containing `matrix[i][j]` for each original row `i`.
8. Send the result to the sender using `sendto()`.
9. Repeat for the next request until stopped.
10. Stop the program.
