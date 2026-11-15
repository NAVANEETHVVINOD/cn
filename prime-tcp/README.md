# TCP Prime Number

Checks whether a signed 32-bit integer is prime. Negative numbers, 0, and 1 are reported as non-prime.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in one terminal and `./client` in another. Run both in this folder on the same machine. The server listens on port 9102 and stays running until you press Ctrl+C.

Example input is `29`.

The client displays `29 is prime.`.

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Enter one signed 32-bit integer.
3. Create an IPv4 TCP socket using `socket()`.
4. Set the server address to `127.0.0.1:9102` and call `connect()`.
5. Send the newline-terminated request using `send()`.
6. Receive the complete response line using `recv()`.
7. Close the socket using `close()`.
8. Display the result.
9. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9102 using `bind()`.
4. Call `listen()`. For each connection, call `accept()` and read a complete request line using `recv()`.
5. Parse the integer and reject input outside the allowed range.
6. Treat numbers smaller than 2 as non-prime.
7. Try divisors from 2 while the divisor is at most the number divided by the divisor.
8. Report non-prime if a divisor has zero remainder. Otherwise report prime.
9. Send a newline-terminated result using `send()` and close the client socket.
10. Repeat for the next request until stopped.
11. Stop the program.
