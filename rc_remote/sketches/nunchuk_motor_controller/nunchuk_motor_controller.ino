//===========================================================================//
//===========================================================================//
//                                                                           //
//    Sketch: DC motor control via Nunchuk                                   //
//    Created: June 2014                                                     //
//    Updated: June 2014                                                     //
//    Description: This sketchs allows control of 2 DC motors via a the      //
//                 joystick on a wii nunchuk                                 //
//                                                                           //
//===========================================================================//
//===========================================================================//

//===========
// #includes
//===========
#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <AFMotor.h>
#include <Servo.h>

//==========
// #defines
//==========
#define BAUDRATE 9600

//================
// Global ojbects
//================
// initiate DC motor controllers
AF_DCMotor motor2(2);
// DC hobby servo
Servo servo;
// initiate nunchuk object
ArduinoNunchuk nunchuk = ArduinoNunchuk();

//===============
// Initial setup
//===============
void setup() {
   Serial.begin(BAUDRATE);
   Serial.println("Starting...");
   nunchuk.init();
   motor3.setSpeed(200);   // turn on DC motor #3
   motor3.run(RELEASE);
   // turn on servo
   servo.attach(10);
}

//===========
// Main loop
//===========
void loop() {
   nunchuk.update();
   int analogX = nunchuk.analogX;
   int analogY = nunchuk.analogY;
   if (analogY < 128) {
      motor2.run(BACKWARD);
      motor2.setSpeed(map(analogY, 0, 127, 254, 0));
   } else {
      motor2.run(FORWARD);
      motor2.setSpeed(map(analogY, 128, 255, 0, 254));
   }
   servo.write(map(analogX, 0, 255, 45, 135));
   delay(15);
}
