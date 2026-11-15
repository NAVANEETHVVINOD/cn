# TCP Multiplication Table

Enter an integer from -1,000,000 through 1,000,000. The server returns its multiplication table from 1 through 10.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in one terminal and `./client` in another. Run both in this folder on the same machine. The server listens on port 9110 and stays running until you press Ctrl+C.

Example input is `7`.

The client displays `7 x 10 = 70` as the last line.

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Enter an integer between -1,000,000 and 1,000,000.
3. Create an IPv4 TCP socket using `socket()`.
4. Set the server address to `127.0.0.1:9110` and call `connect()`.
5. Send the newline-terminated request using `send()`.
6. Receive the complete response line using `recv()`.
7. Close the socket using `close()`.
8. Split the reply at the separators and print one equation per line.
9. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9110 using `bind()`.
4. Call `listen()`. For each connection, call `accept()` and read a complete request line using `recv()`.
5. Parse and validate the integer.
6. Multiply it by each factor from 1 through 10 and format each equation.
7. Join the equations into one reply line using separators.
8. Send a newline-terminated result using `send()` and close the client socket.
9. Repeat for the next request until stopped.
10. Stop the program.
