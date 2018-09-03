EESchema Schematic File Version 4
LIBS:funknetzwerkuhr-cache
LIBS:nixie-breakout-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Transistor_BJT:MPSA92 Q?
U 1 1 5B3B9BBB
P 1800 1600
F 0 "Q?" H 1991 1646 50  0000 L CNN
F 1 "MPSA92" H 1991 1555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 2000 1525 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/MPSA92-D.PDF" H 1800 1600 50  0001 L CNN
	1    1800 1600
	1    0    0    -1  
$EndComp
Text HLabel 1900 1000 0    50   Input ~ 0
Vdd
Wire Wire Line
	1900 1000 1900 1400
Text HLabel 1900 2900 3    50   Output ~ 0
Anode1
Wire Wire Line
	1900 2900 1900 1800
$Comp
L Transistor_BJT:MPSA42 Q?
U 1 1 5B3B9FBE
P 1500 2300
F 0 "Q?" H 1691 2346 50  0000 L CNN
F 1 "MPSA42" H 1691 2255 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 1700 2225 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/MPSA42-D.PDF" H 1500 2300 50  0001 L CNN
	1    1500 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5B3BA1EE
P 1600 1850
F 0 "R?" H 1670 1896 50  0000 L CNN
F 1 "R" H 1670 1805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 1530 1850 50  0001 C CNN
F 3 "~" H 1600 1850 50  0001 C CNN
	1    1600 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1700 1600 1600
Wire Wire Line
	1600 2100 1600 2000
$Comp
L power:GND #PWR?
U 1 1 5B3BA44D
P 1600 2900
F 0 "#PWR?" H 1600 2650 50  0001 C CNN
F 1 "GND" H 1605 2727 50  0000 C CNN
F 2 "" H 1600 2900 50  0001 C CNN
F 3 "" H 1600 2900 50  0001 C CNN
	1    1600 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 2900 1600 2500
$EndSCHEMATC
