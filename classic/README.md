[finished-product-image]: hw/v1/img/classic-v1.jpg "BEEON - Classic; v1"
[pcb-top-image]: hw/v1/img/classic-v1-top.png "BEEON - Classic; v1; pcb-top"
[pcb-bottom-image]: hw/v1/img/classic-v1-bottom.png "BEEON - Classic; v1; pcb-bottom"

# classic hardware

## Overview
The classic device was created several years ago to fill a single need, preventing my work computer from auto locking due to inactivity. *Subverting security policy comes with a responsibility to ensure that you lock your computer (CTRL+ALT+DEL) everytime you walk away!*  

Alternatively the device can also be used as a low-pin USB development platform, by soldering a pin header to the exposed pads on the bottom you can access 3 GPIOS, VCC (3v3+), GND and the RESET pin of the ATTINY85. Making it a very low-pin count development board with USB capabilities.

---
## Firmware
The firmware makes use of the outstanding V-USB software-only implementation of low-speed USB devices. If you plan on making changes or releasing your own devices please change the vendor/device names as well as the vendor/product ids within the [usbconfig.h](fw/v1/usbconfig.h) file.
    
`V-USB` is released under the [GPLv2](https://github.com/obdev/v-usb/blob/master/usbdrv/License.txt) license.

---
## Bootloader
Micronucleus is the bootloader that is currently in use by the beeon-classic devices. You will need a copy of the commandline tool for your operating system inorder to upload new firmware onto the device. v2.04 is the version that we are currently using.
  
`Micronucleus ` is released under the [GPLv2](https://github.com/micronucleus/micronucleus/blob/master/License.txt) license.

| OS | Link |
| -- | -- |
| Windows | [Download](https://github.com/micronucleus/micronucleus/raw/master/commandline/micronucleus.exe) |
| Linux/Darwin | [Build](https://github.com/micronucleus/micronucleus/tree/master/commandline) |

---
## BOM
| Reference(s) | Package  | Description                    | Manufacturer      | Part Number        | **Cost |
| ------------ | -------: | ------------------------------ | ----------------- | -----------------: | -----: |
| SW1          |          | Switch                         | E-Switch          | *TL1014BF180QG     | $#.##  |
| D1           | 1206     | LED                            | OSRAM Opto        | *LG N971-KN-1      | $#.##  |
| J1           |          | 6 PIN 2.54mm (Optional Header) | Harwin            | M20-7820646        | $0.95  |
| J2           |          | USB                            | CNC-Tech          | 1001-011-01101     | $0.77  |
| R1           | 0805     | 47 Ohm Resistor                | Vishay/Dale       | CRCW080547R0FKEA   | $0.10  |
| R2           | 0805     | 1K5 Ohm Resistor               | Vishay/Dale       | CRCW08051K50FKEB   | $0.17  |
| R3           | 0805     | 68 Ohm Resistor                | Vishay/Dale       | CRCW080568R0FKEA   | $0.10  |
| R4           | 0805     | 68 Ohm Resistor                | Vishay/Dale       | CRCW080568R0FKEA   | $0.10  |
| U1           | SOIC-8   | ATtiny85 MCU                   | Atmel             | ATtiny85-20SU      | $1.13  |
| U2           | SOT-23-5 | 1 00mA 3.3 LDO                 | Texas Instruments | TPS79133DBVR       | $1.32  |
| C1           | 1206     | 10uF 10v Tantalum Capacitor    | AVX               | F931A106KAA        | $0.49  |
| C2           | 1206     | 0.1uF 10v MLCC Capacitor       | Vishay/Vitramon   | VJ1206Y104KXQPW1BC | $0.29  |
| C3           | 1206     | 0.01uF 10v MLCC Capacitor      | Vishay/Vitramon   | VJ1206Y103KXJCW1BC | $0.25  |
| C4           | 1206     | 1uF 16v Tantalum Capacitor     | AVX               | F931C105KAA        | $0.51  |

**obsolete part (need to find replacement)*  
***cost last updated on 8/14/2020*

---
## PCB
[`Order from OSH Park`](https://oshpark.com/shared_projects/amtuUCdw)  
![alt text][pcb-top-image] ![alt text][pcb-bottom-image]              

---
## Finished Product
| ![alt text][finished-product-image] |
| :---------------------------------- |

