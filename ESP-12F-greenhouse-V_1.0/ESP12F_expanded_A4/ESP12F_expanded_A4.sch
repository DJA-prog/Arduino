EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L 4xxx:4051 U4
U 1 1 62113757
P 7400 4100
F 0 "U4" H 7944 4054 50  0000 L CNN
F 1 "4051" H 7944 4145 50  0000 L CNN
F 2 "" H 7400 4100 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4051bms-52bms-53bms.pdf" H 7400 4100 50  0001 C CNN
	1    7400 4100
	1    0    0    1   
$EndComp
$Comp
L 74xx:74HC595 U3
U 1 1 6211375D
P 7400 2100
F 0 "U3" H 7400 2881 50  0000 C CNN
F 1 "74HC595" H 7400 2790 50  0000 C CNN
F 2 "" H 7400 2100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 7400 2100 50  0001 C CNN
	1    7400 2100
	1    0    0    -1  
$EndComp
$Comp
L RF_Module:ESP-12F U2
U 1 1 62113763
P 4300 3500
F 0 "U2" H 4300 4481 50  0000 C CNN
F 1 "ESP-12F" H 4300 4390 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 4300 3500 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 3950 3600 50  0001 C CNN
	1    4300 3500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_MEC_5G SW1
U 1 1 62113769
P 3150 2900
F 0 "SW1" H 3150 3185 50  0000 C CNN
F 1 "SW_MEC_5G" H 3150 3094 50  0000 C CNN
F 2 "" H 3150 3100 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=488" H 3150 3100 50  0001 C CNN
	1    3150 2900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_DIP_x01 SW2
U 1 1 6211376F
P 5800 2900
F 0 "SW2" H 5800 3167 50  0000 C CNN
F 1 "SW_DIP_x01" H 5800 3076 50  0000 C CNN
F 2 "" H 5800 2900 50  0001 C CNN
F 3 "~" H 5800 2900 50  0001 C CNN
	1    5800 2900
	1    0    0    -1  
$EndComp
$Comp
L Sensor:DHT11 U1
U 1 1 62113775
P 2550 3550
F 0 "U1" H 2306 3596 50  0000 R CNN
F 1 "DHT11" H 2306 3505 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 2550 3150 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 2700 3800 50  0001 C CNN
	1    2550 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3200 7400 3200
Wire Wire Line
	7400 2800 7400 2900
Connection ~ 7400 3200
Wire Wire Line
	6900 3800 7400 3800
Wire Wire Line
	7000 2000 7400 2000
Wire Wire Line
	7400 2000 7400 1500
Wire Wire Line
	7400 3800 7400 3200
Wire Wire Line
	6900 3500 6250 3500
Wire Wire Line
	6900 3600 6350 3600
Wire Wire Line
	6350 3600 6350 3550
Connection ~ 7400 1500
Wire Wire Line
	6600 4200 6600 3800
Wire Wire Line
	6600 3800 6900 3800
Connection ~ 6900 3800
$Comp
L Regulator_Linear:AP1117-33 U5
U 1 1 6211378F
P 8850 2200
F 0 "U5" H 8850 2442 50  0000 C CNN
F 1 "AP1117-33" H 8850 2351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 8850 2400 50  0001 C CNN
F 3 "http://www.diodes.com/datasheets/AP1117.pdf" H 8950 1950 50  0001 C CNN
	1    8850 2200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2550 2500 2550 3100
Wire Wire Line
	2550 3850 2550 4200
Wire Wire Line
	2550 4200 2950 4200
Wire Wire Line
	2950 2900 2950 4200
Connection ~ 2950 4200
Wire Wire Line
	2850 3550 2850 3800
Wire Wire Line
	2850 3800 3350 3800
Wire Wire Line
	3350 3100 2550 3100
Connection ~ 2550 3100
Wire Wire Line
	2550 3100 2550 3250
Wire Wire Line
	7000 2300 7400 2300
Wire Wire Line
	7400 2300 7400 2800
Connection ~ 7400 2800
Wire Wire Line
	8850 2500 8850 3000
Wire Wire Line
	8850 3000 8550 3000
Connection ~ 7400 3000
Wire Wire Line
	7400 3000 7400 3200
Wire Wire Line
	8550 2200 8550 1500
Wire Wire Line
	8550 1500 8050 1500
Wire Wire Line
	8050 5000 7400 5000
Connection ~ 8050 1500
Wire Wire Line
	8050 1500 7400 1500
Wire Wire Line
	6250 3500 6250 3600
Wire Wire Line
	6500 3900 6500 1900
Wire Wire Line
	6500 1900 7000 1900
Wire Wire Line
	6350 3400 6350 2200
Wire Wire Line
	6350 2200 7000 2200
Wire Wire Line
	7000 1700 6250 1700
Wire Wire Line
	6250 1700 6250 3300
Connection ~ 7400 2900
Wire Wire Line
	7400 2900 7400 3000
$Comp
L Device:R R13
U 1 1 621137C3
P 7900 4400
F 0 "R13" H 7970 4446 50  0000 L CNN
F 1 "47K" H 7970 4355 50  0000 L CNN
F 2 "" V 7830 4400 50  0001 C CNN
F 3 "~" H 7900 4400 50  0001 C CNN
	1    7900 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R12
U 1 1 621137C9
P 7900 3950
F 0 "R12" H 7970 3996 50  0000 L CNN
F 1 "22K" H 7970 3905 50  0000 L CNN
F 2 "" V 7830 3950 50  0001 C CNN
F 3 "~" H 7900 3950 50  0001 C CNN
	1    7900 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4100 7900 4200
Wire Wire Line
	7900 4550 7900 4700
Wire Wire Line
	3250 3300 3250 5150
Wire Wire Line
	8200 5150 8200 4200
Wire Wire Line
	8200 4200 7900 4200
Connection ~ 7900 4200
Wire Wire Line
	7900 4200 7900 4250
$Comp
L Device:CP C1
U 1 1 621137DB
P 8550 2650
F 0 "C1" H 8668 2696 50  0000 L CNN
F 1 "100uF" H 8668 2605 50  0000 L CNN
F 2 "" H 8588 2500 50  0001 C CNN
F 3 "~" H 8550 2650 50  0001 C CNN
	1    8550 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2800 8550 3000
Connection ~ 8550 3000
Wire Wire Line
	8550 3000 7900 3000
Wire Wire Line
	8550 2500 8550 2200
Connection ~ 8550 2200
Wire Wire Line
	4300 4200 5650 4200
Wire Wire Line
	4300 1500 7400 1500
Wire Wire Line
	6100 2900 7400 2900
Wire Wire Line
	4900 2900 5350 2900
$Comp
L Device:R R5
U 1 1 62187837
P 5200 3300
F 0 "R5" V 4993 3300 50  0000 C CNN
F 1 "1K" V 5084 3300 50  0000 C CNN
F 2 "" V 5130 3300 50  0001 C CNN
F 3 "~" H 5200 3300 50  0001 C CNN
	1    5200 3300
	0    1    1    0   
$EndComp
$Comp
L Device:R R6
U 1 1 6219C2D5
P 5200 3400
F 0 "R6" V 4993 3400 50  0000 C CNN
F 1 "1K" V 5084 3400 50  0000 C CNN
F 2 "" V 5130 3400 50  0001 C CNN
F 3 "~" H 5200 3400 50  0001 C CNN
	1    5200 3400
	0    1    1    0   
$EndComp
$Comp
L Device:R R7
U 1 1 6219C899
P 5200 3500
F 0 "R7" V 4993 3500 50  0000 C CNN
F 1 "1K" V 5084 3500 50  0000 C CNN
F 2 "" V 5130 3500 50  0001 C CNN
F 3 "~" H 5200 3500 50  0001 C CNN
	1    5200 3500
	0    1    1    0   
$EndComp
$Comp
L Device:R R8
U 1 1 6219D079
P 5200 3600
F 0 "R8" V 4993 3600 50  0000 C CNN
F 1 "1K" V 5084 3600 50  0000 C CNN
F 2 "" V 5130 3600 50  0001 C CNN
F 3 "~" H 5200 3600 50  0001 C CNN
	1    5200 3600
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 6219D6D0
P 5200 3700
F 0 "R9" V 4993 3700 50  0000 C CNN
F 1 "1K" V 5084 3700 50  0000 C CNN
F 2 "" V 5130 3700 50  0001 C CNN
F 3 "~" H 5200 3700 50  0001 C CNN
	1    5200 3700
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 6219DF7E
P 5200 3800
F 0 "R10" V 4993 3800 50  0000 C CNN
F 1 "1K" V 5084 3800 50  0000 C CNN
F 2 "" V 5130 3800 50  0001 C CNN
F 3 "~" H 5200 3800 50  0001 C CNN
	1    5200 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R R11
U 1 1 6219E495
P 5200 3900
F 0 "R11" V 4993 3900 50  0000 C CNN
F 1 "1K" V 5084 3900 50  0000 C CNN
F 2 "" V 5130 3900 50  0001 C CNN
F 3 "~" H 5200 3900 50  0001 C CNN
	1    5200 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	4300 1500 4300 2500
$Comp
L Device:R R3
U 1 1 621AA4B4
P 3500 3800
F 0 "R3" V 3293 3800 50  0000 C CNN
F 1 "1K" V 3384 3800 50  0000 C CNN
F 2 "" V 3430 3800 50  0001 C CNN
F 3 "~" H 3500 3800 50  0001 C CNN
	1    3500 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 621AB5BA
P 3500 3100
F 0 "R2" V 3293 3100 50  0000 C CNN
F 1 "1K" V 3384 3100 50  0000 C CNN
F 2 "" V 3430 3100 50  0001 C CNN
F 3 "~" H 3500 3100 50  0001 C CNN
	1    3500 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	2550 2500 3500 2500
Connection ~ 4300 2500
Wire Wire Line
	4300 2500 4300 2700
Wire Wire Line
	2950 4200 4300 4200
Connection ~ 4300 4200
$Comp
L Device:R R4
U 1 1 621B6D66
P 5200 2500
F 0 "R4" V 4993 2500 50  0000 C CNN
F 1 "1K" V 5084 2500 50  0000 C CNN
F 2 "" V 5130 2500 50  0001 C CNN
F 3 "~" H 5200 2500 50  0001 C CNN
	1    5200 2500
	0    1    1    0   
$EndComp
Connection ~ 5350 2900
Wire Wire Line
	5350 2900 5500 2900
Wire Wire Line
	5350 2500 5350 2900
Wire Wire Line
	5050 2500 4300 2500
Wire Wire Line
	3350 2900 3500 2900
Wire Wire Line
	3650 3100 3700 3100
Wire Wire Line
	3650 3800 3700 3800
Wire Wire Line
	4900 3300 5050 3300
Wire Wire Line
	5050 3400 4900 3400
Wire Wire Line
	4900 3500 5050 3500
Wire Wire Line
	4900 3700 5050 3700
Wire Wire Line
	4900 3600 5050 3600
Wire Wire Line
	4900 3800 5050 3800
Wire Wire Line
	5350 3800 5650 3800
Wire Wire Line
	5650 3800 5650 4200
Connection ~ 5650 4200
Wire Wire Line
	5650 4200 6600 4200
Wire Wire Line
	5350 3900 6500 3900
Wire Wire Line
	5050 3900 4900 3900
Wire Wire Line
	5350 3700 6900 3700
Wire Wire Line
	5350 3600 6250 3600
Wire Wire Line
	5350 3500 6100 3500
Wire Wire Line
	6100 3500 6100 3550
Wire Wire Line
	6100 3550 6350 3550
Wire Wire Line
	5350 3400 6350 3400
Wire Wire Line
	5350 3300 6250 3300
$Comp
L Device:R R1
U 1 1 62246C9C
P 3500 2650
F 0 "R1" H 3430 2604 50  0000 R CNN
F 1 "1K" H 3430 2695 50  0000 R CNN
F 2 "" V 3430 2650 50  0001 C CNN
F 3 "~" H 3500 2650 50  0001 C CNN
	1    3500 2650
	-1   0    0    1   
$EndComp
Connection ~ 3500 2500
Wire Wire Line
	3500 2500 4300 2500
Wire Wire Line
	3500 2800 3500 2900
Connection ~ 3500 2900
Wire Wire Line
	3500 2900 3700 2900
Text GLabel 9450 2200 2    50   Input ~ 10
VCC
$Comp
L power:GND #PWR0101
U 1 1 6225D26F
P 8550 3050
F 0 "#PWR0101" H 8550 2800 50  0001 C CNN
F 1 "GND" H 8555 2877 50  0000 C CNN
F 2 "" H 8550 3050 50  0001 C CNN
F 3 "" H 8550 3050 50  0001 C CNN
	1    8550 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3050 8550 3000
Wire Wire Line
	9150 2200 9450 2200
Text GLabel 4900 3000 2    50   Input Italic 10
TX
Text GLabel 4900 3200 2    50   Input Italic 10
RX
Wire Wire Line
	8050 1500 8050 5000
Wire Wire Line
	7900 3000 7900 3800
Connection ~ 7900 3000
Wire Wire Line
	7900 3000 7400 3000
Wire Wire Line
	3250 3300 3700 3300
Wire Wire Line
	3250 5150 8200 5150
$EndSCHEMATC
