LIDARLite_Zeroing
========================================

This repository contains sample code demonstrating how to zero the LIDAR-Lite unit. LIDAR-Lite is not "zeroed" at the factory but we have a register (0x13) for zeroing the unit. If you want to offset the readings simply write a calibration offset value to 0x13. 

### Notes

The calibration offset is a two's compliment. 

For postive offset... i.e. to add a constant to the distance output... simply convert the decimal number to hex. 

- Example... if i want to add 5 to all distance readings... the CalibrationOffsetValue would be 0x05

For negative offset... i.e. to subtract a constant from the distance output, you need to subtract the value from 256 and convert that to hex. 

- Example 1... if i want to remove 5 from all distance readings: 256-5 = 251 so the CalibrationOffsetValue would be 0xFB. 
- Example 2... if i want to remove 12 from all distance readings: 256-12 = 244 so the CalibrationOffsetValue would be 0xF4

Use this page to get the hex values: 
[http://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html](http://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html)