# TCP English Translation

Expands common English chat abbreviations using a small dictionary. Matching ignores ASCII letter case, and the server preserves whitespace, punctuation, and unknown words.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in one terminal and `./client` in another. Run both in this folder on the same machine. The server listens on port 9103 and stays running until you press Ctrl+C.

Example input is `TBH, idk.`.

The client displays `to be honest, I don't know.`.

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Enter a line of informal English.
3. Create an IPv4 TCP socket using `socket()`.
4. Set the server address to `127.0.0.1:9103` and call `connect()`.
5. Send the newline-terminated request using `send()`.
6. Receive the complete response line using `recv()`.
7. Close the socket using `close()`.
8. Check the reply status and display the translated text.
9. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Create an IPv4 TCP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9103 using `bind()`.
4. Call `listen()`. For each connection, call `accept()` and read a complete request line using `recv()`.
5. Scan the line for alphanumeric words and preserve separators.
6. Look up each word in the dictionary, ignoring case.
7. Copy the expansion for a match or the original word otherwise.
8. Prefix a successful reply with `OK `.
9. Send a newline-terminated result using `send()` and close the client socket.
10. Repeat for the next request until stopped.
11. Stop the program.
