# DF1 Dissector

## Notes

1. Be sure to backup any files that you edit in order to be able to easily revert back to a original, working copy of Wireshark. 
2. This dissector has only been tested on Wireshark 2.6.1
3. This dissector is not finished by any means. There are still many function codes that need to be added. Also, there were some inconsistencies seen between the DF1 protocol manual, what the traffic that was actually observed.

## Installation

1. First, you must compile Wireshark from source. This will enable you to add/change dissectors and recompile Wireshark. Follow this [link](https://www.wireshark.org/docs/wsug_html_chunked/ChBuildInstallUnixBuild.html) to learn how to compile Wireshark from source.

2. Next, you will have to place the df1 dissector into the dissector directory. You will also have to replace the old dissector RTAC Serial Line Dissector so that it properly calls the new DF1 dissector. **NOTE: Be sure to make a backup of the original packet-rtacser.c dissector before proceeding.**
    - [packet-df1.c](https://github.com/samt707/ambersloth/blob/master/df1/dissectors/packet-df1.c)
    - [packet-rtacser.c](https://github.com/samt707/ambersloth/blob/master/df1/dissectors/packet-rtacser.c)
  ```
  cp packet-df1.c /wireshark-2.6.1/epan/dissectors
  cp packet-rtacser.c /wireshark-2.6.1/epan/dissectors
  
  ```
  
3. Now, we have to edit the Makefile in order for wireshark to compile with our newly added dissector. The easiest way to do this is to start at ```/wirehshark-2.6.1/epan/dissectors/Makefile```. The construct of the Makefile is straightforward. Where ever you see a grouping of dissectors, just add the same syntax, but replace the name of the dissector with packet-df1.c. Add the following lines of code in the proper locations to your Makefile. **NOTE: Be sure to make a backup of the original Makefile before proceeding.**
      - The first string you are going to add is ```packet-df1.lo``` in the ```am__objects_4 = ``` section
      - ```./$(DEPDIR)/packet-df1.Plo``` in the ```am__depfiles_remade = ``` section
      - ```packet-df1.c``` in the ```DISSECTOR_SRC = ``` section
      - ```include ./$(DEPDIR)/packet-df1.Plo # am--include-marker``` under ```distclean-compile:
        -rm -f *.tab.c```
      -  ```-rm -f ./$(DEPDIR)/packet-df1.Plo``` under ```distclean: distclean-recursive```
  
4. Once you have editied the Makefile, you are ready to recompile Wireshark:
  
```    
    cd /wireshark-2.6.1
    sudo make && sudo make install
```    
5. If there are no errors, you can go ahead and open wireshark by running ```./wireshark```
