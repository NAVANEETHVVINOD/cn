# Cisco Packet Tracer routing labs

Choose a routing method and a topology. Each guide starts with a blank Packet Tracer workspace and walks through device placement, exact cable ports, PC IP settings, router commands, ping tests, and saving the completed project as a `.pkt` file.

| Routing method | Two routers and two PCs | Three routers and three PCs |
| --- | --- | --- |
| [Static routing](static-routing/README.md) | [Open lab](static-routing/2router2pc/README.md) | [Open lab](static-routing/3router3pc/README.md) |
| [OSPF](ospf/README.md) | [Open lab](ospf/2router2pc/README.md) | [Open lab](ospf/3router3pc/README.md) |
| [RIPv2](rip/README.md) | [Open lab](rip/2router2pc/README.md) | [Open lab](rip/3router3pc/README.md) |

The guides use **Cisco 2911** routers. The middle router in the three-router labs needs three Ethernet ports. [Cisco 2911 port specifications](https://www.cisco.com/c/en/us/products/collateral/routers/2900-series-integrated-services-routers-isr/data_sheet_c78_553896.html)

## **Algorithm to write in your lab record**

1. Choose a routing method and open its topology guide.
2. Place the devices and connect the specified Ethernet ports.
3. Configure each PC and router interface with the listed IPv4 settings.
4. Verify the direct links, then configure routing.
5. Check the routing table and ping between PCs on different LANs.
6. Save the configurations and the Packet Tracer project.
