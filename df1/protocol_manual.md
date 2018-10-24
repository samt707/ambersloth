# DF1 Protocol 

[DF1 Manual](https://literature.rockwellautomation.com/idc/groups/literature/documents/rm/1770-rm516_-en-p.pdf)


## Half-Duplex

### Transmission Symbols (2-6 pp. 35)

| Abbreviation | Hexadecimal Value | Binary Value |
|:------------:|:-----------------:|:------------:|
|STX           |02                 |0000 0010     |
|SOH           |01                 |0000 0001     |
|ETX           |03                 |0000 0011     |
|EOT           |04                 |0000 0100     |
|ENQ           |05                 |0000 0101     |
|ACK           |06                 |0000 0110     |
|DLE           |10                 |0001 0000     |
|NAK           |0F                 |0000 1111     |

### Transmission Symbols Explanations (2-7 pp. 36)

|Symbol | Type           |                          Meaning|
|:-----:|:--------------:|:-------------------------------:|
|DLE SOH|control symbol  |Sender symbol that indicates the start of a master message.|
|DLE STX| control symbol |Sender symbol that separates the multi-drop header from the data.|
|DLE ETX BCC/CRC |control symbol| Sender symbol that terminates a message.|
|DLE ACK|control symbol  |Response symbol which signals that a message has been successfully received.|
|DLE NAK| control symbol |Global link reset command only issued by the master. Causes the slaves to cancel all messages that are ready to transmit to the master. Typically, the slave returns the message and an error code to the originator.|
|DLE ENQ| control symbol |Sender symbol, issued only by the master, that starts a poll command.|
|DLE EOT BCC| control symbol| Response symbol used by slaves as a response to a poll when they have no messages to send.|
|STN   |data symbol |Station number of the slave node on your half-duplex link.|
|APP DATA| data symbol| Single characters having values 00-0F and 11-FF. Includes data from application layer including user programs and common application routines. A data 1016 is sent as 10 10 (DLE DLE).|
|DLE DLE| data symbol |Represents the data value or STN value of 1016. See APP DATA.|

### Message Packet Format (6-3 pp. 82)


```
            --------------------------------------------------------------
            | DST | SRC | CMD | STS |  TNS  | FNC |  ADDR  | SIZE | DATA | 
            --------------------------------------------------------------
Size (Bytes): 1     1      1     1      2      1       2      1        1    
```

|Field      |Contents   |See   |
|:---------:|:---------:|:----:|
|DST|  destination node for the message|page 6-4|
|SRC |source node of the message| page 6-4|
|FNC      | function code| page 6-5 
|CMD| command code |page 6-5|
|ADDR    | address of memory location (2 bytes)| page 6-8|
|STS |status code| page 6-6 
|EXT STS |extended status code |page 6-6|
|SIZE| number of bytes to be transferred| page 6-8|
|TNS| transaction number (2 bytes)| page 6-7|
|DATA| data values being transferred by the message The number of data bytes in a message depends on the command or function being executed.| Ch. 7|

### Communication Commands (7-2,7-3 pp.89-90)

![comcmd1](/df1/img/comcmd1.png)
![comcmd2](/df1/img/comcmd2.png)

