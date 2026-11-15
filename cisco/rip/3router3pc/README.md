# RIPv2 in Packet Tracer with 3 routers and 3 PCs

Build this lab in a new Packet Tracer file. Each PC connects directly to its router.

## 1. Place and connect the devices

1. Open Packet Tracer. Choose **File → New** and work in the **Logical** workspace in **Realtime** mode.
2. Open **Network Devices → Routers** and drag 3 **2911** routers into the workspace. Refer to them as `R0`, `R1`, `R2` from left to right.
3. Open **End Devices** and place one **PC** below each router. In a new file the PCs are named `PC0`, `PC1`, `PC2` in placement order.
4. Open **Connections** (the lightning bolt), select **Copper Cross-Over**, and connect each pair below. Select the ports shown in the table on both devices.

| Device | Port | Device | Port |
| --- | --- | --- | --- |
| `PC0` | `FastEthernet0` | `R0` | `GigabitEthernet0/0` |
| `PC1` | `FastEthernet0` | `R1` | `GigabitEthernet0/0` |
| `PC2` | `FastEthernet0` | `R2` | `GigabitEthernet0/0` |
| `R0` | `GigabitEthernet0/1` | `R1` | `GigabitEthernet0/1` |
| `R1` | `GigabitEthernet0/2` | `R2` | `GigabitEthernet0/1` |

## 2. Set the PC IPv4 addresses

Click each PC, open **Desktop → IP Configuration**, and select **Static** for IPv4. Enter the values in its row.

| PC | IPv4 address | Subnet mask | Default gateway |
| --- | --- | --- | --- |
| PC0 | `192.168.1.10` | `255.255.255.0` | `192.168.1.1` |
| PC1 | `192.168.2.10` | `255.255.255.0` | `192.168.2.1` |
| PC2 | `192.168.3.10` | `255.255.255.0` | `192.168.3.1` |

## 3. Configure the router interfaces

Click the router on the left first and open **CLI**. If the initial configuration dialog appears, type `no` and press Enter. Press Enter again if prompted to reach `Router>`. Enter the block for that router. Repeat on each router in order. Each block changes the CLI hostname and leaves you at a privileged prompt such as `R0#`.

### R0

```text
enable
configure terminal
hostname R0
interface GigabitEthernet0/0
ip address 192.168.1.1 255.255.255.0
no shutdown
exit
interface GigabitEthernet0/1
ip address 10.0.0.1 255.255.255.252
no shutdown
exit
end
```

### R1

```text
enable
configure terminal
hostname R1
interface GigabitEthernet0/0
ip address 192.168.2.1 255.255.255.0
no shutdown
exit
interface GigabitEthernet0/1
ip address 10.0.0.2 255.255.255.252
no shutdown
exit
interface GigabitEthernet0/2
ip address 10.0.0.5 255.255.255.252
no shutdown
exit
end
```

### R2

```text
enable
configure terminal
hostname R2
interface GigabitEthernet0/0
ip address 192.168.3.1 255.255.255.0
no shutdown
exit
interface GigabitEthernet0/1
ip address 10.0.0.6 255.255.255.252
no shutdown
exit
end
```

## 4. Check the direct links

1. Run `show ip interface brief` on each router. Every interface listed in the cabling table should show `up` under both **Status** and **Protocol**.
2. In each PC's **Desktop → Command Prompt**, ping its own gateway using the address from step 2. For PC0, run `ping 192.168.1.1`.
3. On R0's CLI, run `ping 10.0.0.2` to check the R0–R1 link. On R1, run `ping 10.0.0.6` to check the R1–R2 link.

## 5. Configure RIPv2

Each router advertises its LAN and enables RIP on its `10.0.0.0` transit interfaces. IOS RIP uses the classful network in the `network` command. `no auto-summary` keeps the advertised subnet masks. Enter each block at the named router's privileged prompt.

### R0

```text
configure terminal
router rip
version 2
no auto-summary
network 192.168.1.0
network 10.0.0.0
exit
end
```

### R1

```text
configure terminal
router rip
version 2
no auto-summary
network 192.168.2.0
network 10.0.0.0
exit
end
```

### R2

```text
configure terminal
router rip
version 2
no auto-summary
network 192.168.3.0
network 10.0.0.0
exit
end
```

## 6. Verify the routes and test between PCs

1. On every router, run `show ip protocols` and check that RIP is using version 2. Allow time for the updates to arrive.
2. Run `show ip route` on every router. On R0, look for routes to `192.168.2.0/24` and `192.168.3.0/24` marked `R` via `10.0.0.2`. Each router's own LAN is marked `C` for connected.
3. Open **Desktop → Command Prompt** on the listed PCs and run the following commands.

**PC0**

```text
ping 192.168.2.10
ping 192.168.3.10
```

**PC2**

```text
ping 192.168.1.10
```

Expect replies from each target. If the first ping times out during address resolution, try it again. If your gateway ping fails, check the PC settings, port selections, and `no shutdown`. If gateway and transit pings work but a remote PC cannot be reached, check `show ip route` for the destination LAN and the return route.

## 7. Save your work

1. On each router, run `copy running-config startup-config`. Press Enter if asked to confirm the destination filename.
2. In Packet Tracer, choose **File → Save As** and save the project as `rip-3router3pc.pkt`.

## **Algorithm to write in your lab record**

1. Place 3 routers and 3 PCs and connect the specified Ethernet ports.
2. Set the IPv4 address, subnet mask, and gateway on each PC.
3. Assign the router interface addresses and enable each interface.
4. Test the PC-to-gateway and router-to-router links.
5. Enable RIPv2 with automatic summarization disabled and configure the LAN and transit networks.
6. Check the routing tables and ping between PCs on different LANs.
7. Save the router configurations and the Packet Tracer project.

Back to the [Packet Tracer lab index](../../README.md).
