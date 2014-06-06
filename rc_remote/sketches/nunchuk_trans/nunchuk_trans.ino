//===========================================================================//
//===========================================================================//
//                                                                           //
//    Sketch: Nunchuk data 433MHz transmitter                                //
//    Created: June 2014                                                     //
//    Updated: June 2014                                                     //
//    Description: This sketchs sends nunchuk data over a 433MHz transmitter //
//                                                                           //
//                                                                           //
//===========================================================================//
//===========================================================================//

//===========
// #includes
//===========
#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <VirtualWire.h>

//==========
// #defines
//==========
#define BAUDRATE 9600

//================
// Global ojbects
//================
char *controller;
// initiate nunchuk object
ArduinoNunchuk nunchuk = ArduinoNunchuk();

//===============
// Initial setup
//===============
void setup() {
   Serial.begin(BAUDRATE);	  // Debugging only
   Serial.println("setup transmit");
   nunchuk.init();
   pinMode(13, OUTPUT);
   vw_set_ptt_inverted(true); //
   vw_set_tx_pin(12);
   // Initialise the IO and ISR
   vw_set_ptt_inverted(true); // Required for DR3100
   vw_setup(2000);	 // Bits per sec
}

//===========
// Main loop
//===========
void loop() {
   controller = "1";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,1);
   delay(2000);
   controller = "0";
   vw_send((uint8_t *)controller, strlen(controller));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13,0);
   delay(2000);
}

// or


//===========
// Main loop
//===========
/*void loop() {
   const char *msg = "hello";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);
   delay(200);
}*/



