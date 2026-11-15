# Static routing: 3router3pc

Connect `PC0—R0—R1—R2—PC2`; PC1 connects to R1 g0/0. R1 needs 3 Ethernet ports.

PC0 `192.168.1.10`, gateway `192.168.1.1`; PC1 `192.168.2.10`, gateway `192.168.2.1`; PC2 `192.168.3.10`, gateway `192.168.3.1`. All masks `/24`. Links: R0 g0/1 `10.0.0.1/30`—R1 g0/1 `10.0.0.2/30`; R1 g0/2 `10.0.0.5/30`—R2 g0/1 `10.0.0.6/30`.

**R0**
```
en
conf t
int g0/0
ip add 192.168.1.1 255.255.255.0
no shut
int g0/1
ip add 10.0.0.1 255.255.255.252
no shut
ip route 192.168.2.0 255.255.255.0 10.0.0.2
ip route 192.168.3.0 255.255.255.0 10.0.0.2
end
wr
```
**R1**
```
en
conf t
int g0/0
ip add 192.168.2.1 255.255.255.0
no shut
int g0/1
ip add 10.0.0.2 255.255.255.252
no shut
int g0/2
ip add 10.0.0.5 255.255.255.252
no shut
ip route 192.168.1.0 255.255.255.0 10.0.0.1
ip route 192.168.3.0 255.255.255.0 10.0.0.6
end
wr
```
**R2**
```
en
conf t
int g0/0
ip add 192.168.3.1 255.255.255.0
no shut
int g0/1
ip add 10.0.0.6 255.255.255.252
no shut
ip route 192.168.1.0 255.255.255.0 10.0.0.5
ip route 192.168.2.0 255.255.255.0 10.0.0.5
end
wr
```
On PC0: `ping 192.168.3.10`

## **Algorithm to write in your lab record**

1. Place 3 routers and 3 PCs and connect them as shown above.
2. Assign each PC its listed IP address, subnet mask, and default gateway.
3. Set the router interface addresses and enable the interfaces using `no shutdown`.
4. Add static routes for each remote LAN using its next-hop address.
5. Return to privileged EXEC mode with `end` and verify the routes with `show ip route`.
6. On PC0, run `ping 192.168.3.10` and record the result.
