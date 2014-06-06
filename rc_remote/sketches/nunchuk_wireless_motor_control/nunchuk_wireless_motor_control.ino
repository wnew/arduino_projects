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
AF_DCMotor motor4(4);
// initiate nunchuk object
ArduinoNunchuk nunchuk = ArduinoNunchuk();

//===============
// Initial setup
//===============
void setup() {
   Serial.begin(BAUDRATE);
   nunchuk.init();
   motor2.setSpeed(0);   // turn on DC motor #2
   motor2.run(RELEASE);
   motor4.setSpeed(0);   // turn on DC motor #4
   motor4.run(RELEASE);
}

//===========
// Main loop
//===========
void loop() {
   nunchuk.update();
   motor2.setSpeed(nunchuk.analogY);
   motor4.setSpeed(nunchuk.analogX);
}