# Cisco Packet Tracer routing labs

Short, copy-paste labs for two common sizes:

| Folder | 2 routers / 2 PCs | 3 routers / 3 PCs |
| --- | --- | --- |
| [RIP](rip/README.md) | ✓ | ✓ |
| [OSPF](ospf/README.md) | ✓ | ✓ |
| [Static routing](static-routing/README.md) | ✓ | ✓ |

Use routers with the listed `GigabitEthernet` ports (2911 works). If yours has `FastEthernet`, replace `gigabitEthernet` with `fastEthernet` in the commands.

## **Algorithm to write in your lab record**

1. Choose a routing method and open the guide for your topology.
2. Place and connect the routers and PCs shown in the topology.
3. Assign each PC its listed IP address, subnet mask, and default gateway.
4. Set the router interface addresses and enable the interfaces using `no shutdown`.
5. Configure routing using the selected guide.
6. Ping between PCs on different LANs to verify connectivity.
