# TCP Matrix Classification

Enter an `n × n` integer matrix in the client (`1 ≤ n ≤ 10`). The server identifies whether it is a diagonal, upper-triangular, lower-triangular, or ordinary matrix.

```sh
gcc -Wall -Wextra server.c -o server
gcc -Wall -Wextra client.c -o client
./server
./client
```

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Set the server address to `127.0.0.1:12345` and connect using `connect()`.
4. Read the matrix order `N` and verify it is between 1 and 10.
5. Read and display the entries in the `N × N` integer matrix.
6. Send `N` using `send()`.
7. Send the matrix array using `send()`.
8. Receive the matrix type using `recv()` and display it.
9. Close the socket using `close()`.
10. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Bind the socket to `INADDR_ANY` on port 12345 using `bind()`.
4. Listen using `listen()` and accept a client using `accept()`.
5. Receive `N` and the matrix array using `recv()`.
6. Initialize the `upper`, `lower`, and `diagonal` flags to 1.
7. Inspect each entry with nested loops over rows and columns.
8. If `i > j` and the entry is nonzero, set `upper` to 0.
9. If `i < j` and the entry is nonzero, set `lower` to 0.
10. If `i != j` and the entry is nonzero, set `diagonal` to 0.
11. Choose diagonal, upper triangular, lower triangular, or ordinary in that order using the flags.
12. Send the matrix type using `send()`.
13. Close the client and listening sockets.
14. Stop the program.
