/*
  Simple example for transmitting
  
  http://code.google.com/p/rc-switch/
  
  Need help? http://forum.ardumote.com
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  Serial.print("Starting up Transmitter");
  mySwitch.enableTransmit(10);  // Using Pin #10
}

void loop() {
  mySwitch.send("10000100011000000000010100");
  delay(1000);
}
