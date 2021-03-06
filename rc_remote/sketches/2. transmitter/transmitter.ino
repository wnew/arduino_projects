// transmitter.pde
//
// transmit on pin 12
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>
char *controller;

void setup() {
   Serial.begin(9600);	  // Debugging only
   Serial.println("setup transmit");
   pinMode(13, OUTPUT);
   vw_set_ptt_inverted(true); //
   vw_set_tx_pin(12);
   // Initialise the IO and ISR
   vw_set_ptt_inverted(true); // Required for DR3100
   vw_setup(2000);	 // Bits per sec
}

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

/*void loop() {
   const char *msg = "hello";
   digitalWrite(13, true); // Flash a light to show transmitting
   vw_send((uint8_t *)msg, strlen(msg));
   vw_wait_tx(); // Wait until the whole message is gone
   digitalWrite(13, false);
   delay(200);
}*/



