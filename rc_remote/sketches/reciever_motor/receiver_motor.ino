//===========================================================================//
//===========================================================================//
//                                                                           //
//    Sketch: 433MHz reciever motor controller                               //
//    Created: June 2014                                                     //
//    Updated: June 2014                                                     //
//    Description: This sketchs recieves nunchuk data over a 433MHz link and //
//                 uses this to contol a pair of DC motors                   //
//                                                                           //
//===========================================================================//
//===========================================================================//

//===========
// #includes
//===========
#include <VirtualWire.h>
#include <AFMotor.h>

//==========
// #defines
//==========
#define BAUDRATE 9600

//================
// Global ojbects
//================
const int LED_PIN = 13;
// initiate DC motor controllers
AF_DCMotor motor2(2);
AF_DCMotor motor4(4);

//===============
// Initial setup
//===============
void setup() {
   Serial.begin(9600);	// Debugging only
   Serial.println("setup recv");

   vw_set_rx_pin(12);

   // Initialise the IO and ISR
   vw_set_ptt_inverted(true); // Required for DR3100
   vw_setup(2000);	          // Bits per sec
   vw_rx_start();             // Start the receiver PLL running
   pinMode(13, OUTPUT);

   // initialise motors
   motor2.setSpeed(0);   // turn on DC motor #2
   motor2.run(RELEASE);
   motor4.setSpeed(0);   // turn on DC motor #4
   motor4.run(RELEASE);
}


//===========
// Main loop
//===========
void loop() {
   uint8_t buf[VW_MAX_MESSAGE_LEN];
   uint8_t buflen = VW_MAX_MESSAGE_LEN;

   if (vw_get_message(buf, &buflen)) { // Non-blocking
      int i;
      digitalWrite(LED_PIN, true); // Flash a light to show received good message
	  
      // Message with a good checksum received, dump it.
	  Serial.print("Got: ");
	  for (i = 0; i < buflen; i++) {
         Serial.print(buf[i], HEX);
         Serial.print(" ");
      }
	  Serial.println("");
      digitalWrite(LED_PIN, false);
   }
}
