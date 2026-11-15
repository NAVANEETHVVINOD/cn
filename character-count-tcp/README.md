# TCP Character Count

Counts ASCII letters and digits. Every other byte, including spaces, counts as a special character. Use ASCII input for human-readable character totals.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in one terminal and `./client` in another. Run both in this folder on the same machine. The server listens on port 9104 and stays running until you press Ctrl+C.

Example input is `Ab 12!`.

The client displays `Alphabets: 2, digits: 2, special characters: 2`.

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Enter a line of ASCII text.
3. Create an IPv4 TCP socket using `socket()`.
4. Set the server address to `127.0.0.1:9104` and call `connect()`.
5. Send the newline-terminated request using `send()`.
6. Receive the complete response line using `recv()`.
7. Close the socket using `close()`.
8. Display the result.
9. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9104 using `bind()`.
4. Call `listen()`. For each connection, call `accept()` and read a complete request line using `recv()`.
5. Initialize the letter, digit, and special-character counters to zero.
6. For each byte, increment the letter counter for an ASCII letter or the digit counter for an ASCII digit.
7. Increment the special-character counter for all other bytes, including spaces.
8. Format the three totals.
9. Send a newline-terminated result using `send()` and close the client socket.
10. Repeat for the next request until stopped.
11. Stop the program.
