# UDP Vowel and Consonant Count

Counts vowels (`A`, `E`, `I`, `O`, `U`) and consonants in English ASCII text, ignoring letter case. Digits, spaces, and punctuation are ignored.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Start `./server` in one terminal and `./client` in another. Run both in this folder on the same machine. The server listens on port 9108 and stays running until you press Ctrl+C.

Example input is `Hello World! 123`.

The client displays `Vowels: 3, consonants: 7`.

## **Algorithm to write in your lab record**

### **UDP Client Algorithm**

1. Start the program.
2. Enter a line of ASCII text.
3. Create an IPv4 UDP socket using `socket()`.
4. Set the server address to `127.0.0.1:9108` and call `connect()`.
5. Send the request as a single datagram using `send()`.
6. Receive the response datagram using `recv()`.
7. Close the socket using `close()`.
8. Display the result.
9. Stop the program.

### **UDP Server Algorithm**

1. Start the program.
2. Create an IPv4 UDP socket using `socket()`.
3. Bind it to `127.0.0.1` on port 9108 using `bind()`.
4. Receive a datagram and the client's address using `recvfrom()`.
5. Initialize the vowel and consonant counters to zero.
6. Skip input bytes that are outside the ASCII alphabet.
7. Treat `a`, `e`, `i`, `o`, and `u` as vowels regardless of case, and count the remaining letters as consonants.
8. Format both totals.
9. Send the result to the sender using `sendto()`.
10. Repeat for the next request until stopped.
11. Stop the program.
