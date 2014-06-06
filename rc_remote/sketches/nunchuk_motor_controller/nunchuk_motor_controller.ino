//===========================================================================//
//===========================================================================//
//                                                                           //
//    Sketch: DC motor control via Nunchuk                                   //
//    Created: June 2014                                                     //
//    Updated: June 2014                                                     //
//    Description: This sketchs allows control of DC motors via a wii        //
//                 nunchuk                                                   //
//                                                                           //
//===========================================================================//
//===========================================================================//

//===========
// #includes
//===========
#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <AFMotor.h>

//==========
// #defines
//==========
#define BAUDRATE 9600

//================
// Global ojbects
//================
// initiate DC motor controllers
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
// initiate nunchuk object
ArduinoNunchuk nunchuk = ArduinoNunchuk();

//===============
// Initial setup
//===============
void setup() {
   Serial.begin(BAUDRATE);
   Serial.println("Starting...");
   nunchuk.init();
   motor2.setSpeed(200);   // turn on DC motor #2
   motor2.run(RELEASE);
   motor3.setSpeed(200);   // turn on DC motor #3
   motor3.run(RELEASE);
}

//===========
// Main loop
//===========
void loop() {
   nunchuk.update();
   int analogY = nunchuk.analogY;
   int analogX = nunchuk.analogX;

   //Serial.println(analogY);
   if (analogY < 128) {
   	  motor2.run(BACKWARD);
      motor2.setSpeed(map(analogY,128,255,254,0));
   } else {
   	  motor2.run(FORWARD);
   	  motor2.setSpeed(map(analogY,0,127,0,254));
   }
   if (analogX < 128) {
   	  motor3.run(BACKWARD);
      motor3.setSpeed(map(analogX,128,255,254,0));
      Serial.println(map(analogX,128,255,254,0));
   } else {
   	  motor3.run(FORWARD);
   	  motor3.setSpeed(map(analogX,0,127,0,254));
   	  Serial.println(map(analogX,0,127,0,254));
   }
}