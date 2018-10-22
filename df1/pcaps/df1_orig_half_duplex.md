# Notes for df1_orig_half_duplex

## Packet 1

### Byte sequence

```
100200000f000139aa02078905004934
```

See 14-6/14-7 (pp 238-239) of (DF1 Protocol Manual)[https://literature.rockwellautomation.com/idc/groups/literature/documents/rm/1770-rm516_-en-p.pdf]

- Offset 0 (10)- 0x10: DLE
- OffSet 1 (02)- 0x02: STX
	- DLE STX: Sender symbol that separates the multidrop header from the data.
- Offset 2 (00)- 0x00: DST (Destination)
- Offset 3 (00)- 0x00: SRC (Source)
- Offset 4 (0F)- 0x0F: CMD (Command)
- Offset 5 (00)- 0x00: STS 
	- STS: Indicates the status of the message. A command message should always set this field to 00 (hex).

