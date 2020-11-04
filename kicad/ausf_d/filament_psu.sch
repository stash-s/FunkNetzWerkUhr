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
Wire Wire Line
	6450 4850 6450 4950
Wire Wire Line
	6150 4050 6450 4050
Wire Wire Line
	6450 4050 6450 4150
Text Label 6150 4050 0    10   ~ 0
GND
Wire Wire Line
	4350 3250 4350 3150
Wire Wire Line
	4350 3150 4250 3150
Wire Wire Line
	4350 3150 4350 2550
Connection ~ 4350 3150
Wire Wire Line
	4550 3650 4350 3650
Wire Wire Line
	4550 4450 3750 4450
Wire Wire Line
	3750 4450 3150 4450
Wire Wire Line
	3750 4550 3750 4450
Connection ~ 3750 4450
Text Label 3150 4450 0    70   ~ 0
V_IN
Wire Wire Line
	3750 4050 4550 4050
Wire Wire Line
	3850 3150 3750 3150
Wire Wire Line
	3750 3150 3750 4050
Wire Wire Line
	4150 2350 3750 2350
Wire Wire Line
	3750 2350 3750 3150
Connection ~ 3750 4050
Connection ~ 3750 3150
Wire Wire Line
	6450 3650 6150 3650
Wire Wire Line
	6450 2350 6450 3650
Wire Wire Line
	5800 2350 6450 2350
Wire Wire Line
	6450 4550 6450 4450
Wire Wire Line
	6450 4450 6150 4450
Wire Wire Line
	4550 4850 4350 4850
Wire Wire Line
	4350 4850 4350 5550
Wire Wire Line
	4350 5550 4350 5650
Wire Wire Line
	4550 5550 4350 5550
Connection ~ 4350 5550
Wire Wire Line
	5250 5750 5450 5750
Wire Wire Line
	5450 5750 5450 5550
Wire Wire Line
	7250 2350 7250 2550
Wire Wire Line
	7250 2350 7650 2350
Wire Wire Line
	7650 5550 7650 2350
Wire Wire Line
	7650 2350 8250 2350
Wire Wire Line
	5450 5550 7650 5550
Connection ~ 7650 2350
Text Label 7950 2350 0    70   ~ 0
VSS
Wire Wire Line
	4950 5550 5100 5550
$Comp
L ausf_d-rescue:R-EU_0204_7-esp-vfd-clock-eagle-import-ausf_d-rescue R6
U 1 1 5CD6CAB6
P 4350 3450
F 0 "R6" H 4200 3509 59  0000 L BNN
F 1 "68R" H 4200 3320 59  0000 L BNN
F 2 "PartsStash:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder_Value" H 4350 3450 50  0001 C CNN
F 3 "" H 4350 3450 50  0001 C CNN
	1    4350 3450
	0    -1   -1   0   
$EndComp
$Comp
L ausf_d-rescue:R-EU_0204_7-esp-vfd-clock-eagle-import-ausf_d-rescue R5
U 1 1 5CD6CABC
P 4050 3150
F 0 "R5" H 3900 3209 59  0000 L BNN
F 1 "300" H 3900 3020 59  0000 L BNN
F 2 "PartsStash:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder_Value" H 4050 3150 50  0001 C CNN
F 3 "" H 4050 3150 50  0001 C CNN
	1    4050 3150
	-1   0    0    1   
$EndComp
$Comp
L ausf_d-rescue:R-EU_0411_15-esp-vfd-clock-eagle-import-ausf_d-rescue R4
U 1 1 5CD6CAC2
P 3750 4250
F 0 "R4" H 3600 4309 59  0000 L BNN
F 1 "R22" H 3600 4120 59  0000 L BNN
F 2 "PartsStash:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder_Value" H 3750 4250 50  0001 C CNN
F 3 "" H 3750 4250 50  0001 C CNN
	1    3750 4250
	0    1    1    0   
$EndComp
$Comp
L ausf_d-rescue:R-EU_0204_7-esp-vfd-clock-eagle-import-ausf_d-rescue R8
U 1 1 5CD6CAC8
P 4750 5550
F 0 "R8" H 4600 5609 59  0000 L BNN
F 1 "5k1" H 4600 5420 59  0000 L BNN
F 2 "PartsStash:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder_Value" H 4750 5550 50  0001 C CNN
F 3 "" H 4750 5550 50  0001 C CNN
	1    4750 5550
	1    0    0    -1  
$EndComp
$Comp
L ausf_d-rescue:R-EU_0204_7-esp-vfd-clock-eagle-import-ausf_d-rescue R7
U 1 1 5CD6CACE
P 4350 5850
F 0 "R7" H 4200 5909 59  0000 L BNN
F 1 "2k2" H 4200 5720 59  0000 L BNN
F 2 "PartsStash:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder_Value" H 4350 5850 50  0001 C CNN
F 3 "" H 4350 5850 50  0001 C CNN
	1    4350 5850
	0    -1   -1   0   
$EndComp
$Comp
L Diode:B150-E3 D2
U 1 1 5CD6CAD4
P 4950 2700
AR Path="/5CD6CAD4" Ref="D2"  Part="1" 
AR Path="/5CD5170D/5CD6CAD4" Ref="D2"  Part="1" 
F 0 "D2" H 4860 2775 59  0000 L BNN
F 1 "SS16T3G" H 4860 2565 59  0000 L BNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 4950 2700 50  0001 C CNN
F 3 "" H 4950 2700 50  0001 C CNN
	1    4950 2700
	0    1    1    0   
$EndComp
$Comp
L Diode:B150-E3 D3
U 1 1 5CD6CADA
P 6850 2350
AR Path="/5CD6CADA" Ref="D3"  Part="1" 
AR Path="/5CD5170D/5CD6CADA" Ref="D3"  Part="1" 
F 0 "D3" H 6760 2425 59  0000 L BNN
F 1 "SS16T3G" H 6760 2215 59  0000 L BNN
F 2 "Diode_SMD:D_SMB_Handsoldering" H 6850 2350 50  0001 C CNN
F 3 "" H 6850 2350 50  0001 C CNN
	1    6850 2350
	-1   0    0    1   
$EndComp
$Comp
L ausf_d-rescue:BD140G-esp-vfd-clock-eagle-import-ausf_d-rescue Q2
U 1 1 5CD6CAE0
P 4350 2450
AR Path="/5CD6CAE0" Ref="Q2"  Part="1" 
AR Path="/5CD5170D/5CD6CAE0" Ref="Q2"  Part="1" 
F 0 "Q2" H 3950 2750 59  0000 L BNN
F 1 "2SD669AD-C" H 3950 2650 59  0000 L BNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin2" H 4350 2450 50  0001 C CNN
F 3 "" H 4350 2450 50  0001 C CNN
	1    4350 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:L L2
U 1 1 5CD6CAEC
P 5650 2350
F 0 "L2" V 5800 2450 59  0000 L BNN
F 1 "300uH" V 5600 2300 59  0000 L BNN
F 2 "PartsStash:L_Toroid_Horizontal_D16.8mm_P6mm_AliExpress" H 5650 2350 50  0001 C CNN
F 3 "" H 5650 2350 50  0001 C CNN
	1    5650 2350
	0    -1   -1   0   
$EndComp
$Comp
L Device:CP C8
U 1 1 5CD6CAF2
P 7250 2700
F 0 "C8" H 7295 2719 59  0000 L BNN
F 1 "330" H 7295 2519 59  0000 L BNN
F 2 "Capacitor_SMD:CP_Elec_10x14.3" H 7250 2700 50  0001 C CNN
F 3 "" H 7250 2700 50  0001 C CNN
	1    7250 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C6
U 1 1 5CD6CAF8
P 3750 4700
F 0 "C6" H 3795 4719 59  0000 L BNN
F 1 "100" H 3795 4519 59  0000 L BNN
F 2 "Capacitor_SMD:CP_Elec_6.3x7.7" H 3750 4700 50  0001 C CNN
F 3 "" H 3750 4700 50  0001 C CNN
	1    3750 4700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5CD6CAFE
P 6450 4700
F 0 "C7" H 6510 4715 59  0000 L BNN
F 1 "470pF" H 6510 4515 59  0000 L BNN
F 2 "Capacitor_SMD:C_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6450 4700 50  0001 C CNN
F 3 "" H 6450 4700 50  0001 C CNN
	1    6450 4700
	1    0    0    -1  
$EndComp
$Comp
L ausf_d-rescue:GND-esp-vfd-clock-eagle-import-ausf_d-rescue #U016
U 1 1 5CD6CB0A
P 6450 4250
F 0 "#U016" H 6450 4250 50  0001 C CNN
F 1 "GND" H 6350 4150 59  0000 L BNN
F 2 "" H 6450 4250 50  0001 C CNN
F 3 "" H 6450 4250 50  0001 C CNN
	1    6450 4250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT T1
U 1 1 5CD6CB22
P 5250 5550
F 0 "T1" V 5015 5400 59  0000 L BNN
F 1 "TRIM_EU-S64W" V 5100 5400 59  0000 L BNN
F 2 "Potentiometer_SMD:Potentiometer_Bourns_3314G_Vertical" H 5250 5550 50  0001 C CNN
F 3 "" H 5250 5550 50  0001 C CNN
	1    5250 5550
	0    1    1    0   
$EndComp
Text HLabel 3150 4450 0    50   Input ~ 0
+9V
Text HLabel 8250 2350 2    50   Input ~ 0
+FILAMENT_DC
Wire Wire Line
	7250 2350 7000 2350
Connection ~ 7250 2350
Wire Wire Line
	6700 2350 6450 2350
Connection ~ 6450 2350
Wire Wire Line
	4550 2350 4950 2350
Wire Wire Line
	4950 2550 4950 2350
Connection ~ 4950 2350
Wire Wire Line
	4950 2350 5500 2350
$Comp
L ausf_d-rescue:MC34063AP-esp-vfd-clock-eagle-import-ausf_d-rescue U2
U 1 1 5CD6CAB0
P 5350 4250
F 0 "U2" H 4750 5050 59  0000 L BNN
F 1 "MC34063AP" H 4750 3350 59  0000 L BNN
F 2 "Package_SO:PowerIntegrations_SO-8" H 5350 4250 50  0001 C CNN
F 3 "" H 5350 4250 50  0001 C CNN
	1    5350 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 5550 5450 5550
Connection ~ 5450 5550
Wire Wire Line
	5250 5750 5250 5700
$Comp
L power:GND #PWR0107
U 1 1 5CDBAFB8
P 4350 6050
F 0 "#PWR0107" H 4350 5800 50  0001 C CNN
F 1 "GND" H 4355 5877 50  0000 C CNN
F 2 "" H 4350 6050 50  0001 C CNN
F 3 "" H 4350 6050 50  0001 C CNN
	1    4350 6050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5CDBB564
P 3750 4850
F 0 "#PWR0108" H 3750 4600 50  0001 C CNN
F 1 "GND" H 3755 4677 50  0000 C CNN
F 2 "" H 3750 4850 50  0001 C CNN
F 3 "" H 3750 4850 50  0001 C CNN
	1    3750 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5CDBC039
P 6450 4950
F 0 "#PWR0109" H 6450 4700 50  0001 C CNN
F 1 "GND" H 6455 4777 50  0000 C CNN
F 2 "" H 6450 4950 50  0001 C CNN
F 3 "" H 6450 4950 50  0001 C CNN
	1    6450 4950
	1    0    0    -1  
$EndComp
Connection ~ 6450 4850
Wire Wire Line
	6150 4850 6450 4850
$Comp
L power:GND #PWR0110
U 1 1 5CDC224F
P 7250 2850
F 0 "#PWR0110" H 7250 2600 50  0001 C CNN
F 1 "GND" H 7255 2677 50  0000 C CNN
F 2 "" H 7250 2850 50  0001 C CNN
F 3 "" H 7250 2850 50  0001 C CNN
	1    7250 2850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5CDC27FE
P 4950 2850
F 0 "#PWR0111" H 4950 2600 50  0001 C CNN
F 1 "GND" H 4955 2677 50  0000 C CNN
F 2 "" H 4950 2850 50  0001 C CNN
F 3 "" H 4950 2850 50  0001 C CNN
	1    4950 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5CDC513C
P 8850 2950
F 0 "J4" H 8930 2942 50  0000 L CNN
F 1 "Conn_01x02" H 8930 2851 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8850 2950 50  0001 C CNN
F 3 "~" H 8850 2950 50  0001 C CNN
	1    8850 2950
	1    0    0    -1  
$EndComp
Text HLabel 8650 2950 0    50   Input ~ 0
+FILAMENT_DC
$Comp
L power:GND #PWR05
U 1 1 5CDC58E3
P 8650 3050
F 0 "#PWR05" H 8650 2800 50  0001 C CNN
F 1 "GND" V 8655 2922 50  0000 R CNN
F 2 "" H 8650 3050 50  0001 C CNN
F 3 "" H 8650 3050 50  0001 C CNN
	1    8650 3050
	0    1    1    0   
$EndComp
$EndSCHEMATC
