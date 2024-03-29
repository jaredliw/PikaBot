# PikaBot
An Arduino library for PikaBot. This library allows you to program your PikaBot in a fast and easy way without getting too deep into electronics and programming.

## Introduction

![PikaBot](https://www.cytron.io/image/catalog/products/KIT-PIKABOT/KIT-PIKABOT%20(36).jpg)

[PikaBot](https://my.cytron.io/p-pikabot-maker-uno-smart-car-kit) is a mobile robot kit based on [Maker UNO](https://my.cytron.io/p-maker-uno) (Arduino Uno compatible) by [Cytron Technologies](https://my.cytron.io/).

## Installation

### Download from  Arduino Library Manager (Recommended)

In Arduino IDE, go to **Tools > Manage Libraries...** and search for "**Pikabot**". Click "**Install**" and then "**Close**" after it is done.

### Manual download

Download the ZIP file [here](https://github.com/jaredliw/PikaBot/archive/refs/heads/master.zip). Unzip it and place it under **Documents\Arduino\libraries** (The folder should be named as "**Pikabot**").

You are ready to go!

## Troubleshooting Guide

- **I can't get my code compiled/uploaded.**

  Make sure that you have:

  - installed CH340 Driver in order to program [Maker UNO](https://my.cytron.io/p-maker-uno). ("**Cytron Motor Drivers Library**" is not necessarily to be installed.)
  - configured the correct COM port.

  Refer to the booklet for more information.

- **Some parts of the robot are not functioning as expected.**

  Check your circuit. Make sure that all parts are connected to 5V and GND. Pins should be connected as follows:

  | Pin No. | Should be connected to...                                    |
  | ------- | ------------------------------------------------------------ |
  | A0      | Left IR line sensor pin D0.                                  |
  | A1      | Right IR line sensor pin D0.                                 |
  | 2       | Push button.                                                 |
  | 3       | Motor driver pin M2B (Right DC motor should turn backwards when button M2B is pressed). |
  | 4       | Ultrasonic range sensor pin ECHO.                            |
  | 5       | Ultrasonic range sensor pin TRIG.                            |
  | 9       | Motor driver pin M2A (Right DC motor should turn forwards when button M2A is pressed). |
  | 10      | Motor driver pin M1B (Left DC motor should turn backwards when button M2B is pressed). |
  | 11      | Motor driver pin M1A (Left DC motor should turn forwards when button M2B is pressed). |

- **The robot does not move for the distance specified.** OR **The robot does not rotate by the angle specified.**

  Due to technical constraints, ± 3 cm or ± 10° of deviation is unavoidable. If it does differ a lot, please measure the distance/angle manually and parse the values to function `calibrateMotors` before using motors. See how to use this function in **File > Examples > Pikabot > Motor**.

- **Some notes are missed when playing music using buzzer.**

  Invalid notes/pitches/notations will be skipped. Check your code again.

- **The robot is not following the line.**

  Try to:
  
  - Calibrate your line sensors using a screwdriver. Refer to the booklet for more information.
  - Reduce the speed (around 90 is recommended).

## Report a Problem

Something isn't working as expected? You are welcome to [open an issue](https://github.com/jaredliw/PikaBot/issues) to make this library better! Before opening an issue, make sure that you have read the [troubleshooting guide](https://github.com/jaredliw/PikaBot#troubleshooting-guide).

## Sponsorship

If you would like to make a monetary contribution to this library, kindly contact me via jaredliw@gmail.com.

## License

Released under [GNU General Public License v3.0](https://github.com/jaredliw/PikaBot/blob/master/LICENSE). Any redistribution must:

- retain the same license as it is;
- state changes that you have made; and
- give attribution to this repository and the author(s).

All rights reserved.
