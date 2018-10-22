# Notes for df1_orig_half_duplex

## Packet 1

### Byte sequence

```
100200000f000139aa02078905004934
```

See 14-6/14-7 (pp 238-239) of [DF1 Protocol Manual](https://literature.rockwellautomation.com/idc/groups/literature/documents/rm/1770-rm516_-en-p.pdf)

- Offset 0 (10)- 0x10: DLE
- OffSet 1 (02)- 0x02: STX
	- DLE STX: Indicates start of message. 
- Offset 2 (00)- 0x00: DST (Destination)
	- Indicates the remote node address that the computer is communicating to.
- Offset 3 (00)- 0x00: SRC (Source)
	- Indicates the DH node address that is the source of the message. In this example, the computer uses an
SRC byte of 00 (hex). The asynchronous interface (177-KF2) automatically inserts the correct SRC value
before sending the message across the DH link to the 177-KA.
- Offset 4 (0F)- 0x0F: CMD (Command)
	- Indicates the type of command. In this example, the CMD byte has the value 0F (hex) which points to a
group of PL-3 commands. The FNC byte specifies which command in the group is sent.
- Offset 5 (00)- 0x00: STS 
	- STS: Indicates the status of the message. A command message should always set this field to 00 (hex).
- Offset 6 & 7 (0139)- 0x0139: TNS (Transaction)
	- TNS: Indicates a specific transaction value for each message. The TNS value increments for each message
packet. This value makes each message uniquely different, which helps you check for duplicate message
packets. In this example, there are three commands, and each must have a different TNS value.
- Offset 8 (aa)- 0xaa: FNC (Function Code)
	- FNC: Used with the CMD byte, this byte determines which command is sent. The CMD byte specifies a group of
commands, and the FNC byte specifies a command within that group of commands. In this example,
the FNC byte specifies command aa of command group 0F. (This is the word range read command.) Protected typed logical write with three address fields.
- Offset 9 & 10 (0207)- 0x0207: ADDR (address of memory location, 2 bytes).
	- ADDR: Specifies the PL-2 data table address where the unprotected read starts. The combination of these two
bytes points to a byte address. Since the PL-2 works in word (2 byte) increments, the address should
specify an even number of bytes. The address must be transferred low byte first. 
