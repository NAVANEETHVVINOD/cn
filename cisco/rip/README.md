# RIP

- [2router2pc](2router2pc/README.md)
- [3router3pc](3router3pc/README.md)

## **Algorithm to write in your lab record**

1. Choose one of the topology guides above.
2. Assign each PC its listed IP address, subnet mask, and default gateway.
3. Set the router interface addresses and enable the interfaces using `no shutdown`.
4. Start `router rip`, select `version 2`, disable automatic summarization, and advertise the connected networks shown in the guide.
5. Return to privileged EXEC mode with `end` and verify the routes with `show ip route`.
6. Ping the PC on the far LAN.
