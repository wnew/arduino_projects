/*
 * ArduinoNunchukDemo.ino
 *
 * Copyright 2011-2013 Gabriel Bianconi, http://www.gabrielbianconi.com/
 *
 * Project URL: http://www.gabrielbianconi.com/projects/arduinonunchuk/
 *
 */
#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 9600

#define SERIAL 1

ArduinoNunchuk nunchuk = ArduinoNunchuk();

void setup() {
#ifndef SERIAL
   Serial.begin(BAUDRATE);
#endif SERIAL
   nunchuk.init();
}

void loop() {
  nunchuk.update();
#ifndef SERIAL
   Serial.print  (nunchuk.analogX, DEC);
   Serial.print  (' ');
   Serial.print  (nunchuk.analogY, DEC);
   Serial.print  (' ');
   Serial.print  (nunchuk.accelX,  DEC);
   Serial.print  (' ');
   Serial.print  (nunchuk.accelY,  DEC);
   Serial.print  (' ');
   Serial.print  (nunchuk.accelZ,  DEC);
   Serial.print  (' ');
   Serial.print  (nunchuk.zButton, DEC);
   Serial.print  (' ');
   Serial.println(nunchuk.cButton, DEC);
#endif
}