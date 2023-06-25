# 3DP_EnclosureController

The 3D Printer Enclosure Controller is a board designed with the main purpose of maintaining a constant temperature and humidity level inside a 3D printer enclosure. 
Furthermore, it can also control LED strips to make some building processes look more appealing! Change it in color, intensity and pattern to suit your taste!

The main board design revolves around an Arduino Nano and a TFT screen controlled with a rotary encoder with a push button. The UI is really intuitive, consisting of several widgets 
that show the most important aspects: temperature, humidity, fan speed and LED control. The temperature and humidity measurement is done by a TMP36 sensor with its OP-Amp circuitry and a DHT11.

At the moment, the temperature and humidity is controlled with an "All-or-nothing" control type, just turning the fan on and off at the speed conveniently specified by the user depending
on the current temperature and humidity. The speed is achieved with a PWM and a MOSFET circuit (quite simple).

## Circuit diagram

PCB and circuit diagrams were made in EasyEDA. Using a coupon, I made five boards for less than 5 euro, incluiding shipping!
![Schematic_3D_Printer_Enclosure_2023-06-25](https://github.com/DanielUnleashed/3DP_EnclosureController/assets/24963887/407e8a81-f29d-4d6c-9965-07966e9bf881)

## PCBs

There are two versions to this PCB: one designed to be done in one layer and then add on top some straight stripped cables, and then there's the two layer one.

### One layer PCB
Top.

![PCB_PCB_3D_Printer_Enclosure 2side_2023-06-25](https://github.com/DanielUnleashed/3DP_EnclosureController/assets/24963887/23ca1f79-4285-47f4-8d80-96fe41ae2162)

Bot.

![PCB_PCB_3D_Printer_Enclosure 2side_2023-06-25 (1)](https://github.com/DanielUnleashed/3DP_EnclosureController/assets/24963887/6e885d3d-989a-42bb-bf01-77c5c1099698)

### Two layer PCB
Top.

![PCB_PCB_3D_Printer_Enclosure_2023-06-25](https://github.com/DanielUnleashed/3DP_EnclosureController/assets/24963887/7b35df39-2f1e-4649-b8c6-b4356e3c274f)

Bot.

![PCB_PCB_3D_Printer_Enclosure_2023-06-25 (1)](https://github.com/DanielUnleashed/3DP_EnclosureController/assets/24963887/c46bb78c-0e93-4c39-b534-fabffad551f2)
