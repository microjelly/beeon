# beeon

## classic
avrdude -c USBasp -p attiny85 -U flash:w:micronucleus-2.04.hex:i -B 10  
avrdude -c USBasp -p attiny85 -U lfuse:w:0xe1:m -U hfuse:w:0xdd:m -U efuse:w:0xfe:m  
  
  
micronucleus2 --erase-only  
beeon-sn -mk -mk-p=T-20 > beeon-sn.txt  
beeon-sn | micronucleus2 --run -  
 