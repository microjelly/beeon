EESchema Schematic File Version 2
LIBS:microjelly
LIBS:device
LIBS:beeon-classic-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "22 aug 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATTINY85 U1
U 1 1 53F78C6C
P 4000 3550
F 0 "U1" H 3950 3550 60  0000 C CNN
F 1 "ATTINY85" H 4000 4300 60  0000 C CNN
F 2 "~" H 4000 3550 60  0000 C CNN
F 3 "~" H 4000 3550 60  0000 C CNN
	1    4000 3550
	1    0    0    -1  
$EndComp
$Comp
L LDO U2
U 1 1 53F78C7B
P 8500 2000
F 0 "U2" H 8300 2350 60  0000 C CNN
F 1 "LDO" H 8500 1650 60  0000 C CNN
F 2 "~" H 7700 2650 60  0000 C CNN
F 3 "~" H 7700 2650 60  0000 C CNN
	1    8500 2000
	1    0    0    -1  
$EndComp
$Comp
L USB J2
U 1 1 53F78CBD
P 9200 4000
F 0 "J2" H 9200 3650 60  0000 C CNN
F 1 "USB" H 9200 3750 60  0000 C CNN
F 2 "~" H 9200 4000 60  0000 C CNN
F 3 "~" H 9200 4000 60  0000 C CNN
	1    9200 4000
	0    -1   -1   0   
$EndComp
$Comp
L ISP J1
U 1 1 53F78CDD
P 8500 5750
F 0 "J1" H 8250 6350 60  0000 C CNN
F 1 "ISP" H 8300 5200 60  0000 C CNN
F 2 "~" H 8500 5750 60  0000 C CNN
F 3 "~" H 8500 5750 60  0000 C CNN
	1    8500 5750
	1    0    0    -1  
$EndComp
$Comp
L ESWITCH SW1
U 1 1 53F78CF3
P 4150 6750
F 0 "SW1" H 4050 7000 60  0000 C CNN
F 1 "ESWITCH" H 4150 6500 60  0000 C CNN
F 2 "~" H 3400 7450 60  0000 C CNN
F 3 "~" H 3400 7450 60  0000 C CNN
	1    4150 6750
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 53F78D86
P 3000 3800
F 0 "C1" H 3050 3900 50  0000 L CNN
F 1 "10uF" H 3050 3700 50  0000 L CNN
F 2 "~" H 3000 3800 60  0000 C CNN
F 3 "~" H 3000 3800 60  0000 C CNN
	1    3000 3800
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 53F78DA1
P 1850 6800
F 0 "R1" V 1930 6800 40  0000 C CNN
F 1 "47" V 1857 6801 40  0000 C CNN
F 2 "~" V 1780 6800 30  0000 C CNN
F 3 "~" H 1850 6800 30  0000 C CNN
	1    1850 6800
	0    -1   -1   0   
$EndComp
$Comp
L LED D1
U 1 1 53F78DB1
P 2400 6800
F 0 "D1" H 2400 6900 50  0000 C CNN
F 1 "LED" H 2400 6700 50  0000 C CNN
F 2 "~" H 2400 6800 60  0000 C CNN
F 3 "~" H 2400 6800 60  0000 C CNN
	1    2400 6800
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 53F78DE2
P 8500 2500
F 0 "C3" H 8500 2600 40  0000 L CNN
F 1 ".01uF" H 8506 2415 40  0000 L CNN
F 2 "~" H 8538 2350 30  0000 C CNN
F 3 "~" H 8500 2500 60  0000 C CNN
	1    8500 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	8700 2500 9050 2500
Wire Wire Line
	9050 2500 9050 2150
Wire Wire Line
	7700 2500 8300 2500
Wire Wire Line
	7950 2000 7950 2500
Connection ~ 7950 2150
$Comp
L C C2
U 1 1 53F78E1D
P 7700 2300
F 0 "C2" H 7700 2400 40  0000 L CNN
F 1 ".1uF" H 7706 2215 40  0000 L CNN
F 2 "~" H 7738 2150 30  0000 C CNN
F 3 "~" H 7700 2300 60  0000 C CNN
	1    7700 2300
	1    0    0    -1  
$EndComp
Connection ~ 7950 2500
Wire Wire Line
	7700 1500 7700 2100
Wire Wire Line
	7700 1850 7950 1850
Text GLabel 9500 2700 2    60   Input ~ 0
GND
Wire Wire Line
	7700 2700 7700 2500
$Comp
L CP1 C4
U 1 1 53F78E77
P 9200 2050
F 0 "C4" H 9250 2150 50  0000 L CNN
F 1 "1uF" H 9250 1950 50  0000 L CNN
F 2 "~" H 9200 2050 60  0000 C CNN
F 3 "~" H 9200 2050 60  0000 C CNN
	1    9200 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 1850 9450 1850
Wire Wire Line
	9200 2250 9200 2700
Text GLabel 9450 1850 2    60   Input ~ 0
VCC
Connection ~ 9200 1850
Wire Wire Line
	7700 2700 9500 2700
Connection ~ 9200 2700
Text GLabel 9450 1500 2    60   Input ~ 0
VBUS
Wire Wire Line
	9450 1500 7700 1500
Connection ~ 7700 1850
Text GLabel 8700 4250 3    60   Input ~ 0
GND
Text GLabel 8550 4250 3    60   Input ~ 0
VBUS
Wire Wire Line
	8700 4250 8700 4150
Wire Wire Line
	8700 4150 8850 4150
Wire Wire Line
	8550 4250 8550 4050
Wire Wire Line
	8550 4050 8850 4050
$Comp
L R R4
U 1 1 53F78F69
P 8500 3950
F 0 "R4" V 8580 3950 40  0000 C CNN
F 1 "68" V 8507 3951 40  0000 C CNN
F 2 "~" V 8430 3950 30  0000 C CNN
F 3 "~" H 8500 3950 30  0000 C CNN
	1    8500 3950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8850 3950 8750 3950
Text GLabel 8250 4250 3    60   Input ~ 0
PB4
Wire Wire Line
	8250 4250 8250 3950
$Comp
L R R3
U 1 1 53F78FA1
P 8500 3800
F 0 "R3" V 8580 3800 40  0000 C CNN
F 1 "68" V 8507 3801 40  0000 C CNN
F 2 "~" V 8430 3800 30  0000 C CNN
F 3 "~" H 8500 3800 30  0000 C CNN
	1    8500 3800
	0    -1   -1   0   
$EndComp
$Comp
L R R2
U 1 1 53F78FA7
P 8500 3650
F 0 "R2" V 8580 3650 40  0000 C CNN
F 1 "1K5" V 8507 3651 40  0000 C CNN
F 2 "~" V 8430 3650 30  0000 C CNN
F 3 "~" H 8500 3650 30  0000 C CNN
	1    8500 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8750 3650 8750 3800
Wire Wire Line
	8750 3800 8850 3800
Wire Wire Line
	8850 3800 8850 3850
Text GLabel 8100 4250 3    60   Input ~ 0
PB3
Wire Wire Line
	8250 3800 8100 3800
Wire Wire Line
	8100 3800 8100 4250
Text GLabel 7950 4250 3    60   Input ~ 0
VCC
Wire Wire Line
	7950 4250 7950 3650
Wire Wire Line
	7950 3650 8250 3650
Wire Wire Line
	2800 4000 3250 4000
Text GLabel 2800 4000 0    60   Input ~ 0
GND
Connection ~ 3000 4000
Wire Wire Line
	3250 3600 3250 3700
Wire Wire Line
	2800 3600 3250 3600
Text GLabel 2800 3600 0    60   Input ~ 0
VCC
Connection ~ 3000 3600
Text GLabel 4800 3700 2    60   Input ~ 0
PB3
Text GLabel 4800 3850 2    60   Input ~ 0
PB4
Text GLabel 4800 4000 2    60   Input ~ 0
PB5
Text GLabel 4800 3350 2    60   Input ~ 0
PB2
Text GLabel 4800 3200 2    60   Input ~ 0
PB1
Text GLabel 4800 3050 2    60   Input ~ 0
PB0
Wire Wire Line
	4800 3050 4700 3050
Wire Wire Line
	4800 3200 4700 3200
Wire Wire Line
	4800 3350 4700 3350
Wire Wire Line
	4800 3700 4700 3700
Wire Wire Line
	4800 3850 4700 3850
Wire Wire Line
	4800 4000 4700 4000
Text GLabel 8900 5350 2    60   Input ~ 0
PB1
Text GLabel 8900 5500 2    60   Input ~ 0
VCC
Text GLabel 8900 5650 2    60   Input ~ 0
PB2
Text GLabel 8900 5800 2    60   Input ~ 0
PB0
Text GLabel 8900 5950 2    60   Input ~ 0
PB5
Text GLabel 8900 6100 2    60   Input ~ 0
GND
Wire Wire Line
	8900 5350 8800 5350
Wire Wire Line
	8800 5500 8900 5500
Wire Wire Line
	8800 5650 8900 5650
Wire Wire Line
	8800 5800 8900 5800
Wire Wire Line
	8800 5950 8900 5950
Wire Wire Line
	8800 6100 8900 6100
Text GLabel 2700 6800 2    60   Input ~ 0
GND
Text GLabel 1500 6800 0    60   Input ~ 0
PB1
Wire Wire Line
	1500 6800 1600 6800
Wire Wire Line
	2100 6800 2200 6800
Wire Wire Line
	2600 6800 2700 6800
Text GLabel 4750 6850 2    60   Input ~ 0
GND
Text GLabel 3550 6650 0    60   Input ~ 0
PB2
Wire Wire Line
	3550 6650 4650 6650
Wire Wire Line
	3650 6850 4750 6850
Connection ~ 3650 6650
Connection ~ 4650 6850
$EndSCHEMATC
