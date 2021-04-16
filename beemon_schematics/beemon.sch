EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "BeeMon"
Date "2021-04-13"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP8266:NodeMCU_1.0_(ESP-12E) U4
U 1 1 60754DD9
P 5800 4250
F 0 "U4" H 5800 5337 60  0000 C CNN
F 1 "NodeMCU_1.0_(ESP-12E)" H 5800 5231 60  0000 C CNN
F 2 "" H 5200 3400 60  0000 C CNN
F 3 "" H 5200 3400 60  0000 C CNN
	1    5800 4250
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117 U2
U 1 1 60756942
P 4150 5300
F 0 "U2" H 4150 5542 50  0000 C CNN
F 1 "AMS1117" H 4150 5451 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4150 5500 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 4250 5050 50  0001 C CNN
	1    4150 5300
	0    1    1    0   
$EndComp
$Comp
L sensors:DHT22_Temperature_Humidity TH1
U 1 1 60761ED8
P 7300 5850
F 0 "TH1" V 7247 6728 60  0000 L CNN
F 1 "DHT22_Temperature_Humidity" V 7353 6728 60  0000 L CNN
F 2 "" H 7300 5850 60  0000 C CNN
F 3 "" H 7300 5850 60  0000 C CNN
	1    7300 5850
	0    1    1    0   
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 60766656
P 3850 3750
F 0 "BT1" V 3595 3800 50  0000 C CNN
F 1 "Battery_Cell" V 3686 3800 50  0000 C CNN
F 2 "" V 3850 3810 50  0001 C CNN
F 3 "~" V 3850 3810 50  0001 C CNN
	1    3850 3750
	1    0    0    -1  
$EndComp
$Comp
L Components:HX711 U5
U 1 1 60756E57
P 7800 3950
F 0 "U5" H 7800 4425 50  0000 C CNN
F 1 "HX711" H 7800 4334 50  0000 C CNN
F 2 "" H 7900 3950 50  0001 C CNN
F 3 "" H 7900 3950 50  0001 C CNN
	1    7800 3950
	-1   0    0    1   
$EndComp
$Comp
L Components:LoadCell VR1
U 1 1 6075C84F
P 9800 2500
F 0 "VR1" V 9846 2272 50  0000 R CNN
F 1 "LoadCell" V 9755 2272 50  0000 R CNN
F 2 "" H 9900 2650 50  0001 C CNN
F 3 "" H 9900 2650 50  0001 C CNN
	1    9800 2500
	0    -1   -1   0   
$EndComp
$Comp
L Components:LoadCell VR2
U 1 1 6075D333
P 9800 3100
F 0 "VR2" V 9846 2872 50  0000 R CNN
F 1 "LoadCell" V 9755 2872 50  0000 R CNN
F 2 "" H 9900 3250 50  0001 C CNN
F 3 "" H 9900 3250 50  0001 C CNN
	1    9800 3100
	0    -1   -1   0   
$EndComp
$Comp
L Components:LoadCell VR3
U 1 1 6075DCFC
P 9800 3700
F 0 "VR3" V 9846 3472 50  0000 R CNN
F 1 "LoadCell" V 9755 3472 50  0000 R CNN
F 2 "" H 9900 3850 50  0001 C CNN
F 3 "" H 9900 3850 50  0001 C CNN
	1    9800 3700
	0    -1   -1   0   
$EndComp
$Comp
L Components:LoadCell VR4
U 1 1 6075EB8E
P 9800 4300
F 0 "VR4" V 9846 4072 50  0000 R CNN
F 1 "LoadCell" V 9755 4072 50  0000 R CNN
F 2 "" H 9900 4450 50  0001 C CNN
F 3 "" H 9900 4450 50  0001 C CNN
	1    9800 4300
	0    -1   -1   0   
$EndComp
$Comp
L Device:Solar_Cell SC1
U 1 1 6075F99A
P 1700 3800
F 0 "SC1" H 1808 3896 50  0000 L CNN
F 1 "Solar_Cell" H 1808 3805 50  0000 L CNN
F 2 "" V 1700 3860 50  0001 C CNN
F 3 "~" V 1700 3860 50  0001 C CNN
	1    1700 3800
	1    0    0    -1  
$EndComp
$Comp
L charger_stepup-cache:TP4056mini U1
U 1 1 607619F7
P 2800 3700
F 0 "U1" H 2800 4065 50  0000 C CNN
F 1 "TP4056mini" H 2800 3974 50  0000 C CNN
F 2 "" H 2800 3700 50  0001 C CNN
F 3 "" H 2800 3700 50  0001 C CNN
	1    2800 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 3550 3150 3550
Wire Wire Line
	3150 3550 3150 3600
Connection ~ 3850 3550
Wire Wire Line
	2450 3800 2450 3900
Wire Wire Line
	3150 3800 3350 3800
Wire Wire Line
	3350 3800 3350 3850
Wire Wire Line
	3350 3850 3850 3850
Wire Wire Line
	3850 3850 3850 4750
Wire Wire Line
	3850 4850 5000 4850
Connection ~ 3850 3850
Wire Wire Line
	1700 3600 2450 3600
Wire Wire Line
	1700 3900 2450 3900
Wire Wire Line
	6600 4850 6700 4850
Wire Wire Line
	6700 4850 6700 6000
Wire Wire Line
	6700 6000 7300 6000
$Comp
L SparkFun-Resistors:10KOHM-HORIZ-1_4W-5% R1
U 1 1 6076BB3E
P 6950 4650
F 0 "R1" V 6855 4718 45  0000 L CNN
F 1 "10KOHM" V 6939 4718 45  0000 L CNN
F 2 "AXIAL-0.3" H 6950 4800 20  0001 C CNN
F 3 "" H 6950 4650 60  0001 C CNN
F 4 "" V 7034 4718 60  0000 L CNN "Field4"
	1    6950 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	6800 4450 6800 5800
Wire Wire Line
	6800 5800 7300 5800
Wire Wire Line
	6600 4450 6800 4450
Connection ~ 6800 4450
Wire Wire Line
	6800 4450 6950 4450
Wire Wire Line
	6950 4850 6950 4950
Wire Wire Line
	6950 4950 6600 4950
Wire Wire Line
	9550 2600 9400 2600
Wire Wire Line
	9400 2600 9400 3200
Wire Wire Line
	9400 3200 9550 3200
Wire Wire Line
	9550 2400 9350 2400
Wire Wire Line
	9350 2400 9350 3600
Wire Wire Line
	9350 3600 9550 3600
Wire Wire Line
	9550 3000 9300 3000
Wire Wire Line
	9300 3000 9300 4200
Wire Wire Line
	9300 4200 9550 4200
Wire Wire Line
	9550 3800 9350 3800
Wire Wire Line
	9350 3800 9350 4400
Wire Wire Line
	9350 4400 9550 4400
Wire Wire Line
	9550 2500 8550 2500
Wire Wire Line
	8550 2500 8550 4100
Wire Wire Line
	8550 4100 8200 4100
Wire Wire Line
	9550 3100 8500 3100
Wire Wire Line
	8500 3100 8500 4000
Wire Wire Line
	8500 4000 8200 4000
Wire Wire Line
	9550 3700 8450 3700
Wire Wire Line
	8450 3700 8450 3900
Wire Wire Line
	8450 3900 8200 3900
Wire Wire Line
	9550 4300 8550 4300
Wire Wire Line
	8550 4300 8550 4200
Wire Wire Line
	8550 4200 8200 4200
Wire Wire Line
	7400 4100 7050 4100
Wire Wire Line
	7050 4100 7050 4150
Wire Wire Line
	7400 4000 7000 4000
Wire Wire Line
	7000 4000 7000 4250
Wire Wire Line
	7000 4250 6600 4250
Wire Wire Line
	6950 3900 6950 4350
Wire Wire Line
	6950 4350 6600 4350
NoConn ~ 5000 3650
NoConn ~ 5000 3750
NoConn ~ 5000 3850
NoConn ~ 5000 3950
NoConn ~ 5000 4050
NoConn ~ 5000 4150
NoConn ~ 5000 4250
NoConn ~ 5000 4350
NoConn ~ 5000 4450
NoConn ~ 5000 4550
NoConn ~ 5000 4650
NoConn ~ 6600 3850
NoConn ~ 6600 3950
NoConn ~ 6600 4550
NoConn ~ 6600 4650
NoConn ~ 6600 4750
NoConn ~ 8200 3700
NoConn ~ 8200 3800
Wire Wire Line
	6600 3550 6700 3550
Wire Wire Line
	6700 3550 6700 3200
Wire Wire Line
	6700 3200 4850 3200
Wire Wire Line
	4850 4750 5000 4750
$Comp
L Switch:SW_SPST SW1
U 1 1 607C3174
P 4450 4750
F 0 "SW1" V 4496 4662 50  0000 R CNN
F 1 "SW_SPST" V 4405 4662 50  0000 R CNN
F 2 "" H 4450 4750 50  0001 C CNN
F 3 "~" H 4450 4750 50  0001 C CNN
	1    4450 4750
	1    0    0    -1  
$EndComp
NoConn ~ 5800 2000
NoConn ~ 5700 2000
NoConn ~ 5600 2000
NoConn ~ 5900 2000
$Comp
L Components:HD44780_I2C U3
U 1 1 60782267
P 5800 2450
F 0 "U3" H 4912 2579 50  0000 R CNN
F 1 "HD44780_I2C" H 4912 2488 50  0000 R CNN
F 2 "" H 5500 2850 50  0001 C CNN
F 3 "" H 5500 2850 50  0001 C CNN
	1    5800 2450
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Displays:LCD-16X2-MINMIN4-RGB LCD1
U 1 1 60779C8D
P 5800 1600
F 0 "LCD1" V 6260 1550 45  0000 C CNN
F 1 "LCD-16X2-MINMIN4-RGB" V 6176 1550 45  0000 C CNN
F 2 "LCD-16X2_NOSILK-KIT-4BIT" H 5800 2700 20  0001 C CNN
F 3 "" H 5800 1600 50  0001 C CNN
F 4 "LCD-10862" V 6081 1550 60  0000 C CNN "Field4"
	1    5800 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6750 3650 6600 3650
Wire Wire Line
	6800 3750 6600 3750
Wire Wire Line
	6600 4150 7050 4150
Wire Wire Line
	7400 3900 6950 3900
Wire Wire Line
	7050 4100 7050 2350
Wire Wire Line
	7050 2350 6700 2350
Connection ~ 7050 4100
Wire Wire Line
	6800 3750 6800 2550
Wire Wire Line
	6800 2550 6700 2550
Wire Wire Line
	6750 3650 6750 2650
Wire Wire Line
	6750 2650 6700 2650
Wire Wire Line
	6700 2450 6950 2450
Wire Wire Line
	6950 2450 6950 2850
Wire Wire Line
	6950 2850 3850 2850
Wire Wire Line
	3850 3550 4150 3550
Wire Wire Line
	4150 5000 4150 3550
Connection ~ 4150 3550
Wire Wire Line
	3850 5300 3850 4850
Connection ~ 3850 4850
Wire Wire Line
	3850 2850 3850 3550
Wire Wire Line
	4150 5700 4150 5600
Wire Wire Line
	4150 5700 7300 5700
Wire Wire Line
	7400 3800 7250 3800
Wire Wire Line
	7250 3800 7250 5600
Wire Wire Line
	7250 5600 4150 5600
Connection ~ 4150 5600
Wire Wire Line
	4850 3200 4850 4750
Wire Wire Line
	4150 3550 4750 3550
Wire Wire Line
	5000 4950 4750 4950
Wire Wire Line
	4750 4950 4750 3550
Connection ~ 4750 3550
Wire Wire Line
	4750 3550 5000 3550
Wire Wire Line
	4850 4750 4650 4750
Connection ~ 4850 4750
Wire Wire Line
	4250 4750 3850 4750
Connection ~ 3850 4750
Wire Wire Line
	3850 4750 3850 4850
$EndSCHEMATC
