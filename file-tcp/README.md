# TCP File Server

The server shares one file selected when it starts. The client requests that file by basename and saves the received bytes to a new file. Text files, binary files, and empty files are supported.

## Build on Ubuntu

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

In the server terminal, create a small example file and start the server.

```sh
printf 'Hello from the TCP file server\n' > sample.txt
./server sample.txt
```

In the client terminal, request the file and compare it with the original.

```sh
./client sample.txt received.txt
cmp sample.txt received.txt
```

Use a destination that does not already exist. The server listens on `127.0.0.1:9109`.

## **Algorithm to write in your lab record**

### **TCP Client Algorithm**

1. Start the program.
2. Read the requested filename and the new local destination.
3. Create a TCP socket and connect to `127.0.0.1:9109`.
4. Send the filename followed by a newline using `send()`.
5. Read the status line and check for `OK` and a byte count.
6. Create the destination and receive bytes with `recv()` until the stated count is reached.
7. Remove the partial file if the transfer fails. Close the socket and report the result.
8. Stop the program.

### **TCP Server Algorithm**

1. Start the program.
2. Open the command-line file in binary mode and record its basename.
3. Create a TCP socket, bind it to `127.0.0.1:9109`, and call `listen()`.
4. Use `accept()` and read the requested basename up to the newline.
5. If it matches, determine the file size and send an `OK` line with the byte count. Otherwise send an error.
6. Read and send the fixed number of bytes in chunks.
7. Close the client socket and accept the next client until stopped.
8. Stop the program.
