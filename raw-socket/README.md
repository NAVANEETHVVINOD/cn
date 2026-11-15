# Raw Socket Packet Capture

Captures packets visible to the local Linux machine and prints Ethernet, IP, and TCP/UDP/ICMP header fields. Use it only on networks and machines you are authorized to inspect.

This example uses Linux packet-socket headers, so it will not compile on macOS or Windows.

```sh
gcc -Wall -Wextra packet-capture.c -o packet-capture
sudo ./packet-capture
```

Press `Ctrl+C` to stop. Root privileges (or the `CAP_NET_RAW` capability) are required to open the raw socket.

## **Algorithm to write in your lab record**

1. Start the program.
2. Allocate a buffer and create an `AF_PACKET` raw socket.
3. Receive each Ethernet frame using `recvfrom()`.
4. Check the header length and print the frame length, MAC addresses, and Ethernet protocol.
5. For IPv4, validate the IP header and print the source and destination addresses, TTL, and protocol.
6. For TCP and UDP, display the ports. For ICMP, display the type and code.
7. Repeat until stopped. On a receive error, close the socket and free the buffer.
8. Stop the program.
