# Notes for df1_orig_half_duplex

## Packet 1

### Byte sequence 

```
5bbe04680001637804000000100200000f000139aa02078905004934
```
#### Data 
- 17-8 (pp. 105) 
	- Protected Logical Write with Three Adress Fields)

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
the FNC byte specifies command aa of command group 0F. (This is the word range read command.) Protected typed logical write with three address fields. Writes data to a logical address in a SLC processor.
- Offset 9 (02)- 0x02: Byte Size
	- Byte Size: The size of data to be read (in bytes), not including the address fields
or other overhead bytes. In this case it is 2 bytes. 
- Offset 10 (07)- 0x07: File Number
	- Addresses files 0-254 only. For higher addresses, setting this byte to FF expands this field to three bytes total. Use the second and third bytes for the expanded file address (low address byte first). It is 7 in this case.
- Offset 11 (89)- 0x89: File Type
	- Use one of the these values for this field. Do not use any other values; doing so may result in unpredictable results.
	

|Hex Value|Definition|
|:-----:|:------:|
|80-83 hex| reserved|
|84 hex| status|
|85 hex| bit|
|86 hex| timer|
|87 hex| counter|
|88 hex| control|
|89 hex| integer|
|8A hex| floating point|
|8D hex| string|
|8E hex| ASCII|

- Offset 12 (05)- 0x05: Element Number
	- Addresses elements 0-254 only. For higher addresses, setting this
byte to FF expands this field to three bytes. Use the second and third
bytes for the expanded element address (low address byte first).

- Offset 13 (00)- 0x00: Sub-element Number
	- Addresses sub-elements 0-254 only. For higher addresses, setting
this byte to FF expands this field to three bytes. Use the second and
third bytes for the expanded sub-element address (low address byte
first).

- Offset 14 & 15(4934)- 0x4934: Data
