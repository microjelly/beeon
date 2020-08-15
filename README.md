# beeon

## Overview
The classic device was created several years ago to fill a single need, preventing my work computer from auto locking due to inactivity. *Subverting security policy comes with a responsibility to ensure that you lock your computer (CTRL+ALT+DEL) everytime you walk away!*  

## classic notes
### flash bootloader to board
`avrdude -c USBasp -p attiny85 -U flash:w:micronucleus-2.04.hex:i -B 10`  
`avrdude -c USBasp -p attiny85 -U lfuse:w:0xe1:m -U hfuse:w:0xdd:m -U efuse:w:0xfe:m`  
### upload new firmware onto board
`micronucleus --run {firmware.hex}`
### clear out any existing firmware
`micronucleus --erase-only`
### upload firmware with random serial number
*first create random serial number file*  
`beeon-sn -mk -mk-p=Z-ZZ > beeon-sn.txt`  
`beeon-sn | micronucleus --run -`  

