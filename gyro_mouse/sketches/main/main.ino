//===========================================================================//
//                                                                           //
//  Desc:    Arduino Code to implement a fencing scoring apparatus           //
//  Dev:     Wnew                                                            //
//  Date:    Nov 2012                                                        //
//  Updated: Aug 2014                                                        //
//  Notes:   1. Basis of algorithm from digitalwestie on github. Thanks Mate //
//           2. Used uint8_t instead of int where possible to optimise       //
//           3. Set ADC prescaler to 16 faster ADC reads                     //
//                                                                           //
//  To do:   1. Could use shift reg on lights and mode LEDs to save pins     //
//           2. Use interrupts for buttons                                   //
//           3. Implement short circuit LEDs (already provision for it)      //
//           4. Set up debug levels correctly                                //
//                                                                           //
//===========================================================================//

//============
// #includes
//============
#include <Wire.h>
#include <ArduinoNunchuk.h>

//============
// #defines
//============
#define DEBUG 0
#define BAUDRATE 57600
#define SENSITIVITY 10

ArduinoNunchuk nunchuk = ArduinoNunchuk();

//================
// Configuration
//================
void setup() {
  Mouse.begin();
  Serial.begin(BAUDRATE);
  nunchuk.init();
}

//============
// Main Loop
//============
void loop() {
  nunchuk.update();

  if (nunchuk.cButton) {
    Mouse.press(MOUSE_LEFT);
  } else {
    Mouse.release(MOUSE_LEFT);
  }

  if (nunchuk.zButton) {
    Mouse.press(MOUSE_RIGHT);
  } else {
    Mouse.release(MOUSE_RIGHT);
  }

  // sort out sensitivity
  // need to map the nunchuk values to a log scale
  //Mouse.move((nunchuk.analogX-128)/SENSITIVITY, (-1)*(nunchuk.analogY-128)/SENSITIVITY);
  long moveX = nunchuk.analogX-128;
  long moveY = nunchuk.analogY-128;
  Mouse.move(((moveX^3)-3)/10, ((-1)*(moveY^3)+3)/10);

  Serial.print(moveX^3, DEC);
  Serial.print(' ');
  Serial.print((-1)*(moveY^3), DEC);
  Serial.print(' ');
  Serial.print(nunchuk.analogX, DEC);
  Serial.print(' ');
  Serial.print(nunchuk.analogY, DEC);
  Serial.print(' ');
  // accel doesnt seem to be working on the new white nunchuks :(
  Serial.print(nunchuk.accelX, DEC);
  Serial.print(' ');
  Serial.print(nunchuk.accelY, DEC);
  Serial.print(' ');
  Serial.print(nunchuk.accelZ, DEC);
  Serial.print(' ');
  Serial.print(nunchuk.zButton, DEC);
  Serial.print(' ');
  Serial.println(nunchuk.cButton, DEC);
}
