//===========================================================================//
//===========================================================================//
//                                                                           //
//    Sketch: Storm Cloud Lamp                                               //
//    Date: 2014                                                             //
//    Description: Controls a blue LED and a yellow LED to simulate a strom  //
//                 cloud                                                     //
//                                                                           //
//    Notes: This is just the skeleton code for now                          //
//                                                                           //
//===========================================================================//
//===========================================================================//

//==================
// Hardware Circuit
//==================


//==========
// #defines
//==========
#define BAUDRATE      57600
#define BLUELEDPIN   3
#define YELLOWLEDPIN 4


//===========
// #includes
//===========


//================
// Global ojbects
//================
int pulseWidth = 100;


//================
// Program Config
//================
void setup() {
  // Open serial communications:
  Serial.begin(BAUDRATE);
  // turn on blue LED
  digitalWrite(BLUELEDPIN,   HIGH);
}


//===================
// Main Program Loop
//===================
void loop() {
  // a few lightning strikes in a row (1 to 5)
  for (int i; i++; i < 5*rand()) {
    digitalWrite(YELLOWLEDPIN, HIGH);
    // Lightning length (10ms - 100ms)
    delay(100*rand());
    digitalWrite(YELLOWLEDPIN, LOW);
    // short delay beteen lightning (10ms - 500ms)
    delay(500*rand());
  }
  //longer delay bewteen sets of lighting strikes (1sec - 10sec)
  delay(10000*rand());
}