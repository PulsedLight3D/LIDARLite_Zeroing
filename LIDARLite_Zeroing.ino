/* 
http://pulsedlight3d.com
This sketch demonstrates getting distance with the LIDAR-Lite Sensor, turning
it off between readings, averaging distance and setting the calibration offset. 

It utilizes the 'Arduino I2C Master Library' from DSS Circuits:
http://www.dsscircuits.com/index.php/articles/66-arduino-i2c-master-library 

You can find more information about installing libraries here:
http://arduino.cc/en/Guide/Libraries

*/

#include <I2C.h>
#define    LIDARLite_ADDRESS       0x62          // Default I2C Address of LIDAR-Lite.
#define    RegisterMeasure         0x00          // Register to write to initiate ranging.
#define    MeasureValue            0x04          // Value to initiate ranging.
#define    RegisterHighLowB        0x8f          // Register to get both High and Low bytes in 1 call.
#define    CalibrationRegister     0x13          // The register to set for calibration
#define    CalibrationOffsetVlue   0x00          // The calibration offset... see note below. 

/*
Calibration offset is a Two's Compliment Value:

For postive offset... i.e. to add a constant to the distance output... simply convert the decimal number to hex
Example... if i want to add 5 to all distance readings... the CalibrationOffsetValue would be 0x05

For negative offset... i.e. to subtract a constant from the distance output, you need to subtract the value from 256 
and convert that to hex. 
Example 1... if i want to remove 5 from all distance readings: 256-5 = 251 so the CalibrationOffsetValue would be 0xFB
Example 2... if i want to remove 12 from all distance readings: 256-12 = 244 so the CalibrationOffsetValue would be 0xF4

Use this page to get the hex values: http://www.cs.princeton.edu/courses/archive/fall07/cos109/bc.html

*/


void setup(){
  Serial.begin(9600); //Opens serial connection at 9600bps.     
  I2c.begin(); // Opens & joins the irc bus as master
  delay(100); // Waits to make sure everything is powered up before sending or receiving data  
  I2c.timeOut(50); // Sets a timeout to ensure no locking up of sketch if I2C communication fails
  LidarLiteCalibrate();
}

void loop(){
   Serial.println(LidarLiteRawDistance()); 
}


/*=====================================================================================
FUNCTIONS 
=====================================================================================*/

void LidarLiteCalibrate(){
 // Write 0x04 to register 0x00
  uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses     
  while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
    nackack = I2c.write(LIDARLite_ADDRESS,CalibrationRegister, CalibrationOffsetVlue); // Write Calibration Offset Value to 0x13
    delay(1); // Wait 1 ms to prevent overpolling
  }
} 

int LidarLiteRawDistance(){
 // Write 0x04 to register 0x00
  uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses     
  while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
    nackack = I2c.write(LIDARLite_ADDRESS,RegisterMeasure, MeasureValue); // Write 0x04 to 0x00
    delay(1); // Wait 1 ms to prevent overpolling
  }

  byte distanceArray[2]; // array to store distance bytes from read function
  
  // Read 2byte distance from register 0x8f
  nackack = 100; // Setup variable to hold ACK/NACK resopnses     
  while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
    nackack = I2c.read(LIDARLite_ADDRESS,RegisterHighLowB, 2, distanceArray); // Read 2 Bytes from LIDAR-Lite Address and store in array
    delay(1); // Wait 1 ms to prevent overpolling
  }
  int distance = (distanceArray[0] << 8) + distanceArray[1];  // Shift high byte [0] 8 to the left and add low byte [1] to create 16-bit int
  
  return distance; // give us this value
} 



