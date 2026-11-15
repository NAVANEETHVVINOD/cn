# KTU Computer Networks Lab

C socket programs and Cisco Packet Tracer guides for the KTU Computer Networks laboratory. Each exercise has its own folder, run instructions, and numbered steps for your lab record.

## TCP exercises

| Folder | Program |
| --- | --- |
| [basic-tcp](basic-tcp/) | TCP greeting exchange |
| [chat-tcp](chat-tcp/) | Multi-user chat |
| [matrix-tcp](matrix-tcp/) | Square matrix classification |
| [prime-tcp](prime-tcp/) | Prime number check |
| [translation-tcp](translation-tcp/) | English chat abbreviation expansion |
| [character-count-tcp](character-count-tcp/) | Count letters, digits, and special characters |
| [transpose-tcp](transpose-tcp/) | Transpose a rectangular matrix |
| [file-tcp](file-tcp/) | Download a text or binary file |
| [multiplication-table-tcp](multiplication-table-tcp/) | Multiplication table from 1 to 10 |

## UDP exercises

| Folder | Program |
| --- | --- |
| [basic-udp](basic-udp/) | UDP greeting exchange |
| [english-udp](english-udp/) | English chat abbreviation expansion |
| [file-udp](file-udp/) | UDP file server |
| [matrix-udp](matrix-udp/) | Square matrix classification |
| [time-udp](time-udp/) | UDP time server |
| [time-id-udp](time-id-udp/) | Time server with a server ID and a two-client demonstration |
| [transpose-udp](transpose-udp/) | Transpose a rectangular matrix |
| [vowel-count-udp](vowel-count-udp/) | Count vowels and consonants |

## Other labs

- [Raw socket packet capture](raw-socket/) covers Linux packet headers.
- [Cisco Packet Tracer routing labs](cisco/) cover static routing, OSPF, and RIPv2 with topology and configuration guides.

## Run on Ubuntu

Use GCC and open two terminal windows in the exercise folder. For a typical client/server exercise, build the two programs once.

```sh
gcc -std=c11 -Wall -Wextra server.c -o server
gcc -std=c11 -Wall -Wextra client.c -o client
```

Run `./server` in one terminal and `./client` in the other. Use the arguments shown in the exercise README where applicable. The new exercises use `127.0.0.1`, so run the clients and server on the same machine. For the time server with an ID, open a third terminal to run a second client.
