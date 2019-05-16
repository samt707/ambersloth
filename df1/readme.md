## DF-1 Wireshark Dissector
- [DF-1 Wireshark Dissector](/df1/dissectors/packet-df1.c)

## Notes

- [DF1 Protocol Manual](https://literature.rockwellautomation.com/idc/groups/literature/documents/rm/1770-rm516_-en-p.pdf)

## Methodology

1. Take raw, serial df1 traffic from a RS232 serial tap and run it through serial2pcap. 
    - In order to automate this process, we had serial2pcap split the data into 4000 byte pcaps. Serial2pcap was constantly running in the background to have a consistent stream of uninterrupted data. We wrote the pcaps to a network fileshare so that other hosts could easily access them. We were running serial2pcap on a windows machine and then running it through tshark on a second machine. In a practical scenario, serial2pcap and tshark should be running on the same machine to reduce latency and increase efficiency. 
    
2. Run the pcap that is output from serial2pcap through tshark using custom built dissectors.
    - First, be sure to follow [these](https://github.com/samt707/ambersloth/blob/master/df1/dissectors/readme.md) instructions on how to properly set up wireshark with the df1 dissector.
    - Second, in order to constantly be running data from serial2pcap to tshark, we used the following [script](https://github.com/samt707/ambersloth/blob/master/df1/scripts/amberscript.sh). This script would take each pcap output by serial2pcap, run it through tshark with the proper command line options and output it as a json file. From there, we would post the json file using the ```curl``` command to our Kibana instance. 
    
 3. In Kibana, we created tables and dashboards to represent the important fields from the DF1 traffic. These fields and tables can be changed depending upon what data you are most interested in. 
 

