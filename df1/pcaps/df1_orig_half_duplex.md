# Notes for df1_orig_half_duplex

## Packet 1

### Byte sequence

```
100200000f000139aa02078905004934
```

- Offset 0 (10)- 0x10: DLE
- OffSet 1 (02)- 0x02: STX
	- DLE STX: Sender symbol that separates the multidrop header from the data.
- Offset 2 (00)- 0x00: DST (Destination)
- Offset 3 (00)- 0x00: SRC (Source)
- Offset 4 (0F)- 0x0F: CMD (Command)


