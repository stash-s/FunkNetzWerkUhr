EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L Connector:Barrel_Jack_Switch J1
U 1 1 5B703308
P 3700 2150
F 0 "J1" H 3778 2475 50  0000 C CNN
F 1 "Jack-DC" H 3778 2384 50  0000 C CNN
F 2 "Parts:AliExpress55mmBarelJack" H 3750 2110 50  0001 C CNN
F 3 "" H 3750 2110 50  0001 C CNN
	1    3700 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2150 4100 2150
Wire Wire Line
	4100 2150 4100 2250
Wire Wire Line
	4100 2250 4000 2250
$Comp
L power:GND #PWR09
U 1 1 5B708045
P 4100 2350
F 0 "#PWR09" H 4100 2100 50  0001 C CNN
F 1 "GND" H 4105 2177 50  0000 C CNN
F 2 "" H 4100 2350 50  0001 C CNN
F 3 "" H 4100 2350 50  0001 C CNN
	1    4100 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 2350 4100 2250
Connection ~ 4100 2250
$Comp
L power:+9V #PWR08
U 1 1 5B70CCFB
P 4100 1950
F 0 "#PWR08" H 4100 1800 50  0001 C CNN
F 1 "+9V" H 4115 2123 50  0000 C CNN
F 2 "" H 4100 1950 50  0001 C CNN
F 3 "" H 4100 1950 50  0001 C CNN
	1    4100 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2050 4100 2050
Wire Wire Line
	4100 2050 4100 1950
$Comp
L funknetzwerkuhr-rescue:MAX1771-Parts_Stash-funknetzwerkuhr-rescue U4
U 1 1 5B71C581
P 5550 3800
AR Path="/5B71C581" Ref="U4"  Part="1" 
AR Path="/5B5B1780/5B71C581" Ref="U4"  Part="1" 
F 0 "U4" H 5250 4250 50  0000 C CNN
F 1 "max1771" H 5300 3400 50  0000 C CNN
F 2 "Package_SO:PowerIntegrations_SO-8" H 5550 3800 50  0001 C CNN
F 3 "" H 5550 3800 50  0001 C CNN
	1    5550 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5B7219A7
P 4400 4650
F 0 "#PWR010" H 4400 4400 50  0001 C CNN
F 1 "GND" H 4405 4477 50  0000 C CNN
F 2 "" H 4400 4650 50  0001 C CNN
F 3 "" H 4400 4650 50  0001 C CNN
	1    4400 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5B73AC8D
P 4700 4000
F 0 "C3" V 4800 3850 50  0000 L CNN
F 1 "100n" V 4550 3900 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4738 3850 50  0001 C CNN
F 3 "" H 4700 4000 50  0001 C CNN
	1    4700 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 4050 5000 4050
Wire Wire Line
	5000 4050 5000 4550
Wire Wire Line
	5000 4550 5550 4550
Wire Wire Line
	5550 4550 5550 4250
Wire Wire Line
	5100 3750 4700 3750
Wire Wire Line
	4700 3750 4700 3850
Wire Wire Line
	4700 4150 4700 4550
Wire Wire Line
	4700 4550 5000 4550
Connection ~ 5000 4550
Wire Wire Line
	4700 4550 4400 4550
Connection ~ 4700 4550
Connection ~ 4400 4550
Wire Wire Line
	4400 4550 4400 4650
$Comp
L power:+9V #PWR011
U 1 1 5B77A333
P 5550 2550
F 0 "#PWR011" H 5550 2400 50  0001 C CNN
F 1 "+9V" H 5565 2723 50  0000 C CNN
F 2 "" H 5550 2550 50  0001 C CNN
F 3 "" H 5550 2550 50  0001 C CNN
	1    5550 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 3350 5550 2700
Connection ~ 5550 2700
Wire Wire Line
	4400 4550 3900 4550
$Comp
L Device:C C2
U 1 1 5B78B212
P 3500 3500
F 0 "C2" V 3600 3350 50  0000 L CNN
F 1 "100n" V 3350 3400 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 3538 3350 50  0001 C CNN
F 3 "" H 3500 3500 50  0001 C CNN
	1    3500 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3350 3500 2700
Wire Wire Line
	3500 2700 3900 2700
Wire Wire Line
	3500 3650 3500 4550
$Comp
L Device:L L1
U 1 1 5B7B044B
P 6250 2700
F 0 "L1" V 6440 2700 50  0000 C CNN
F 1 "L" V 6349 2700 50  0000 C CNN
F 2 "Inductor_THT:L_Toroid_Vertical_L14.0mm_W6.3mm_P4.57mm_Pulse_A" H 6250 2700 50  0001 C CNN
F 3 "" H 6250 2700 50  0001 C CNN
	1    6250 2700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5550 2550 5550 2700
$Comp
L Transistor_FET:IRF740 Q1
U 1 1 5B7D60FD
P 6500 3600
F 0 "Q1" H 6450 3750 50  0000 L CNN
F 1 "IRF640" V 6750 3450 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-263-2" H 6750 3525 50  0001 L CIN
F 3 "" H 6500 3600 50  0001 L CNN
	1    6500 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 2700 6600 2700
Wire Wire Line
	6600 2700 6600 3400
Wire Wire Line
	6000 3600 6300 3600
Wire Wire Line
	6600 3800 6000 3800
$Comp
L Device:R RSENSE1
U 1 1 5B817112
P 6600 4300
F 0 "RSENSE1" V 6500 4200 50  0000 L CNN
F 1 "0R1" V 6700 4200 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.40x3.35mm_HandSolder" V 6530 4300 50  0001 C CNN
F 3 "" H 6600 4300 50  0001 C CNN
	1    6600 4300
	1    0    0    -1  
$EndComp
Connection ~ 6600 3800
Wire Wire Line
	6600 4550 5550 4550
Connection ~ 5550 4550
Wire Wire Line
	6600 4550 6600 4450
$Comp
L Device:D D1
U 1 1 5B82AEE8
P 6950 2700
F 0 "D1" H 6950 2484 50  0000 C CNN
F 1 "ES2J" H 6950 2575 50  0000 C CNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 6950 2700 50  0001 C CNN
F 3 "" H 6950 2700 50  0001 C CNN
	1    6950 2700
	-1   0    0    1   
$EndComp
$Comp
L Device:CP C5
U 1 1 5B82B010
P 7300 3250
F 0 "C5" V 7400 3050 50  0000 L CNN
F 1 "4.7uF,250V" V 7150 3050 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D8.0mm_P3.50mm" H 7338 3100 50  0001 C CNN
F 3 "" H 7300 3250 50  0001 C CNN
	1    7300 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2700 6800 2700
Connection ~ 6600 2700
Wire Wire Line
	7100 2700 7300 2700
Wire Wire Line
	7300 2700 7300 3100
Wire Wire Line
	7300 3400 7300 4550
Wire Wire Line
	7300 4550 7100 4550
Connection ~ 6600 4550
$Comp
L Device:R R1
U 1 1 5B85662F
P 7700 3100
F 0 "R1" H 7770 3146 50  0000 L CNN
F 1 "1.5M" H 7770 3055 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 7630 3100 50  0001 C CNN
F 3 "" H 7700 3100 50  0001 C CNN
	1    7700 3100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5B856729
P 7700 4300
F 0 "R2" H 7770 4346 50  0000 L CNN
F 1 "10k" H 7770 4255 50  0000 L CNN
F 2 "PartsStash:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder_Value" V 7630 4300 50  0001 C CNN
F 3 "" H 7700 4300 50  0001 C CNN
	1    7700 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 4450 7700 4550
Wire Wire Line
	7700 4550 7300 4550
Connection ~ 7300 4550
Wire Wire Line
	7700 2700 7300 2700
Connection ~ 7300 2700
Wire Wire Line
	6000 4050 6950 4050
Wire Wire Line
	6950 4050 6950 3600
Wire Wire Line
	6950 3600 7700 3600
$Comp
L Device:C C7
U 1 1 5B9159FA
P 8550 3600
F 0 "C7" V 8650 3450 50  0000 L CNN
F 1 "100n,250V" V 8400 3400 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L16.5mm_W4.7mm_P15.00mm_MKT" H 8588 3450 50  0001 C CNN
F 3 "" H 8550 3600 50  0001 C CNN
	1    8550 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2700 8550 3000
Wire Wire Line
	7700 2700 8550 2700
Connection ~ 7700 2700
Wire Wire Line
	8550 3750 8550 4550
Wire Wire Line
	8550 4550 7700 4550
Connection ~ 7700 4550
$Comp
L power:+VDC #PWR013
U 1 1 5B926D85
P 8550 2600
F 0 "#PWR013" H 8550 2500 50  0001 C CNN
F 1 "+VDC" H 8550 2875 50  0000 C CNN
F 2 "" H 8550 2600 50  0001 C CNN
F 3 "" H 8550 2600 50  0001 C CNN
	1    8550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2600 8550 2700
Connection ~ 8550 2700
$Comp
L power:GND #PWR07
U 1 1 5BA5D6FA
P -331550 -111500
F 0 "#PWR07" H -331550 -111750 50  0001 C CNN
F 1 "GND" H -331545 -111673 50  0000 C CNN
F 2 "" H -331550 -111500 50  0001 C CNN
F 3 "" H -331550 -111500 50  0001 C CNN
	1    -331550 -111500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1a1
U 1 1 5B5BC670
P 7700 3900
F 0 "R1a1" H 7770 3946 50  0000 L CNN
F 1 "2.7k" H 7770 3855 50  0000 L CNN
F 2 "PartsStash:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder_Value" V 7630 3900 50  0001 C CNN
F 3 "" H 7700 3900 50  0001 C CNN
	1    7700 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	7700 3750 7700 3600
Connection ~ 7700 3600
Wire Wire Line
	7700 4150 7700 4050
Text HLabel 8800 2700 2    50   Output ~ 0
+180V
Wire Wire Line
	8800 2700 8550 2700
Text HLabel 4200 2050 2    50   Output ~ 0
+9V
Wire Wire Line
	4200 2050 4100 2050
Connection ~ 4100 2050
Wire Wire Line
	3900 3650 3900 4550
Connection ~ 3900 4550
Wire Wire Line
	3900 4550 3500 4550
Wire Wire Line
	3900 3350 3900 2700
Connection ~ 3900 2700
Wire Wire Line
	3900 2700 5550 2700
Text GLabel 5100 3600 0    50   Input ~ 0
BLANK
Wire Wire Line
	7700 2700 7700 2950
Wire Wire Line
	7700 3250 7700 3600
Wire Wire Line
	5550 2700 6100 2700
Text Label 6600 3900 3    50   ~ 0
SENSE
$Comp
L Device:CP C4
U 1 1 5B7B059A
P 3900 3500
F 0 "C4" V 4000 3350 50  0000 L CNN
F 1 "220uF,25V" V 3750 3350 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P2.50mm_P5.00mm" H 3938 3350 50  0001 C CNN
F 3 "" H 3900 3500 50  0001 C CNN
	1    3900 3500
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J3
U 1 1 5CCD2A7A
P 9150 3100
F 0 "J3" H 9122 2982 50  0000 R CNN
F 1 "Conn_01x02_Male" H 9122 3073 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 9150 3100 50  0001 C CNN
F 3 "~" H 9150 3100 50  0001 C CNN
	1    9150 3100
	-1   0    0    1   
$EndComp
Wire Wire Line
	8550 3000 8950 3000
Connection ~ 8550 3000
Wire Wire Line
	8550 3000 8550 3450
Wire Wire Line
	8950 3100 8950 4550
Wire Wire Line
	8950 4550 8550 4550
Connection ~ 8550 4550
$Comp
L Device:R RSENSE2
U 1 1 5FB6ADB5
P 6850 4300
F 0 "RSENSE2" V 6750 4200 50  0000 L CNN
F 1 "0R1" V 6950 4200 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.40x3.35mm_HandSolder" V 6780 4300 50  0001 C CNN
F 3 "" H 6850 4300 50  0001 C CNN
	1    6850 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 3800 6600 4100
Wire Wire Line
	6850 4150 6850 4100
Wire Wire Line
	6850 4100 6600 4100
Connection ~ 6600 4100
Wire Wire Line
	6600 4100 6600 4150
Wire Wire Line
	6850 4450 6850 4550
Connection ~ 6850 4550
Wire Wire Line
	6850 4550 6600 4550
$Comp
L Device:R RSENSE3
U 1 1 5FB6E24A
P 7100 4300
F 0 "RSENSE3" V 7000 4200 50  0000 L CNN
F 1 "0R1" V 7200 4200 50  0000 L CNN
F 2 "Resistor_SMD:R_2512_6332Metric_Pad1.40x3.35mm_HandSolder" V 7030 4300 50  0001 C CNN
F 3 "" H 7100 4300 50  0001 C CNN
	1    7100 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6850 4100 7100 4100
Wire Wire Line
	7100 4100 7100 4150
Connection ~ 6850 4100
Wire Wire Line
	7100 4450 7100 4550
Connection ~ 7100 4550
Wire Wire Line
	7100 4550 6850 4550
$EndSCHEMATC
