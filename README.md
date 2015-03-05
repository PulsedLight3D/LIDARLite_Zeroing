LIDARLite_Zeroing
========================================

This repository contains sample code demonstrating how to zero the LIDAR-Lite unit. LIDAR-Lite is not "zeroed" at the factory but we have a register (0x13) for zeroing the unit. If you want to offset the readings simply write a calibration offset value to 0x13. 

## How it works

The calibration offset is a two's compliment. 

For postive offset... i.e. to add a constant to the distance output... simply convert the decimal number to hex. 

- Example... if i want to add 5 to all distance readings... the CalibrationOffsetValue would be 0x05

For negative offset... i.e. to subtract a constant from the distance output, you need to subtract the value from 256 and convert that to hex. 

- Example 1... if i want to remove 5 from all distance readings: 256-5 = 251 so the CalibrationOffsetValue would be 0xFB. 
- Example 2... if i want to remove 12 from all distance readings: 256-12 = 244 so the CalibrationOffsetValue would be 0xF4

Use this page to get the hex values: 
[http://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html](http://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html)

## Dependencies
1. Arduino Uno compatible Board
2. Arduino IDE (1.0.6 or newer)
3. USB Cable
4. LIDAR-Lite Sensor
5. The 'Arduino I2C Master Library' from DSS Circuits: http://www.dsscircuits.com/index.php/articles/66-arduino-i2c-master-library

## Installation
1. Download Repository and open with Arduino IDE
2. Install DSS "Arduino I2C Master Library" - Information about installing libraries can be found:  
http://arduino.cc/en/Guide/Libraries

## Arduino Setup

![arduino-screenshot](http://pulsedlight3d.net/assets.pl3d/arduino-setup.png)

### LIDARLite I2C Connection Setup
LIDARLite Cable | Arduino Pins
:---|:---
5V | 5V
PWR EN | _(Unused)_
MODE | _(Unused)_
SCL | SCL (topmost pin on the right hand side of Arduino)
SDA | SDA (second pin from the top on the right hand side of Arduino)
GND | GND
