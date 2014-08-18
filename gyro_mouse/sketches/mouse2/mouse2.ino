//Wiichuck Mouse
//Brian Krukoski
//April 2012
//red-+5, white-gnd, green-sda, yllw-clck

#include <Wire.h>
#include "nunchuck_funcs.h"
int loop_cnt=0;

// parameters for reading the joystick:
int range = 40;               // output range of X or Y movement
int threshold = range/10;      // resting threshold
int center = range/2;         // resting position value

boolean mouseIsActive = false;    // whether or not to control the mouse
int lastSwitchState = LOW;        // previous switch state

void setup() {
  // initilization for the Wiichuck
  nunchuck_init();
  // take control of the mouse:
  Mouse.begin();
  Serial.begin(9600);
}

void loop() {
  if( loop_cnt > 10 ) { // every 10 msecs get new data
    loop_cnt = 0;
    nunchuck_get_data();

    //right and left click control
    int leftState = nunchuck_cbutton(); 
    if (leftState) Mouse.press(MOUSE_LEFT); else Mouse.release(MOUSE_LEFT);
    int rightState = nunchuck_zbutton();
    if (rightState) Mouse.press(MOUSE_RIGHT); else Mouse.release(MOUSE_RIGHT);

    // read the x axis
    int xReading = nunchuck_joyx(); //calls on nunchuck_funcs library for x axis reading
    xReading = map(xReading, 38, 232, 0, range); // 38 and 232 arbitrarily determined through experimentation, maps to 0 and preset range
    int xDistance = xReading - center;
    if (abs(xDistance) < threshold) //if absolute value of xDistance is less than predefined threshold....
      {
        xDistance = 0;
      }

    // read the y axis
    int yReading = nunchuck_joyy(); //calls on nunchuck_funcs library for y axis reading
    yReading = map(yReading, 38, 232, 0, range); // 38 and 232 arbitrarily determined through experimentation, maps to 0 and preset range
    int yDistance = yReading - center;
    if (abs(yDistance) < threshold) //if absolute value of yDistance is less than predefined threshold....
      {
        yDistance = 0;
      }

    // move the mouse if the readings were above 0
    if ((xDistance != 0) || (yDistance != 0)) {
      Mouse.move(xDistance, -yDistance, 0); // -yDistance ensures inverted style joystick
    }
  }
  nunchuck_print_data(); //prints nunchuck data to serial monitor for debugging purposes
  loop_cnt++;
  delay(1);
 
}