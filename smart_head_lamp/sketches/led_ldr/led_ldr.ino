//===========================================================================//
//===========================================================================//
//                                                                           //
//    Sketch: Ambient Light Tracker                                          //
//    Created: June 2014                                                     //
//    Updated: June 2014                                                     //
//    Description: This sketch senses the ambient light using an LDR and     //
//                 adjusts an LED to keep the ambient light constant         //
//                                                                           //
//===========================================================================//
//===========================================================================//

//===========
// #includes
//===========


//==========
// #defines
//==========
#define DEBUG              // Send out serial debug data
#define BAUDRATE      9600 // Serial baudrate

#define LEDPIN        5    // PWM Pin for the LED
#define LDRPIN        A3   // Pin for the LDR
#define BUTTONPIN     0    // Pin 2 is an interrupt capable pin

#define OFF           0    // Defining the modes for the state machine
#define WHITEON       1
#define WHITEHALF     2
#define WHITETRACK    3
#define WHITESTROBE   4
#define REDON         5
#define REDSTROBE     6

#define DEPRESSTHRESH 200  // The theshold between a long and a short press
#define TIMEOUT       1000 // The max time between presses when changing modes

//================
// Global ojbects
//================
int mode                 = OFF; // Keeps track of the current mode
int last_press_time      = 0;   // Stores the last time the button was pressed
int user_set_pulse_width = 255; // Stores the user configured pulse width

//===============
// Initial setup
//===============
void setup() {
  // Initalize LED Pin
  pinMode (LEDPIN, OUTPUT);
  // attach the interrupt on the button pin to the buttonPressed method
  attachInterrupt(BUTTONPIN, buttonPressed, RISING);

#ifdef DEBUG // Enable Serial Communication - useful for debugging
  Serial.begin   (BAUDRATE);
  Serial.println ("Starting...");
#endif
}

//=========================
// Button interrupt method
//=========================
void buttonPressed () {
  //TODO: figure out if long press or short press
  
  boolean longPress = 0;
  int timeOut = (millis() - last_pressed) > TIMEOUT;

  // long press
  if (longPress) {
    user_set_pulse_width = user_set_pulse_width++;
    // change the brightness 
  // short press
  } else { 
    if (!timeout) {
      if (mode < 7)
        mode++;
      else
        mode = OFF;
    } else {
      mode = OFF;
    }
  }

#ifdef DEBUG
  Serial.println("Mode change");
  Serial.println(mode);
#endif
  last_pressed = millis();
}

//===========
// Main loop
//===========
void loop() {
  // Read the LDR
  //analogWrite (LEDPIN, (map(analogRead (LDRPIN),0,950,255,0)));

  int ldr_val = analogRead (LDRPIN);

  switch (mode) {
    case OFF:
      pulse_width = 0;
    break;
    case WHITEON:
      pulse_width = user_set_pulse_width;
    break;
    case WHITEHALF:
      pulse_width = user_set_pulse_width;
    break;
    case WHITETRACK:
      //TODO: impl tracking algorithm
    break;
    case WHITESTROBE:
      //TODO: strobe the red led
      pulse_width = 255;
    break;
    case REDON:
      pulse_width = 255;
    break;
    case REDSTROBE:
      //TODO: strobe the red led
      pulse_width = 255;
    break;
    default:
      // Ensure the led is off
      pulse_width = 0; 
  }

  analogWrite(LEDPIN, pulseWidth);

  // Sometimes the number is over 255 or under 0 - rounding errors !!!!!
  //if (LDRValue < 0)   LDRValue = 0;
  //if (LDRValue > 255) LDRValue = 255;

  // Set the value for the LED
  //analogWrite (LEDPIN, LDRValue);

#ifdef DEBUG
  //Serial.println(mode);
  //Serial.print   ("LED PWN Value: ");
  //Serial.println (analogRead (LDRPIN));
  //Serial.println (map(analogRead (LDRPIN),0,950,255,0));
  //delay(500);
#endif
}
