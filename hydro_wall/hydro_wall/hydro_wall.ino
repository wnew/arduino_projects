/*
 The circuit:
 * SD card attached to SPI bus as follows:
 ** UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (CS pin can be changed)
  and pin #10 (SS) must be an output
 ** Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 4 (CS pin can be changed)
  and pin #52 (SS) must be an output
 ** Leonardo: Connect to hardware SPI via the ICSP header
 		Pin 4 used here for consistency with other Arduino examples
 */
 
//=================
// #includes
//=================
#include <SPI.h>
#include <SD.h>
#include <TimerOne.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pin 8 - Serial clock out (SCLK)
// pin 7 - Serial data out (DIN)
// pin 6 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
Adafruit_PCD8544 display = Adafruit_PCD8544(8, 7, 6, 5, 3);

const int solenoidPin = 13;
bool solenoidState = false;

const int pollTime = 5;

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 4;

File dataFile;


//=================
// Program Config
//=================
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  setupSD();
}


//========================
// Main Program Loop
//========================
void loop()
{
  Timer1.initialize(pollTime * 1000000);
  Timer1.attachInterrupt(pollSensors);
}


//========================
// Configure the SD Card
//========================
void setupSD () {
  Serial.println("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(SS, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    while (1); // don't do anything more:
  } else {
    Serial.println("Card initialized");
  }
  
  // Open up the file we're going to log to!
  dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (! dataFile) {
    Serial.println("error opening datalog.txt");
    // Wait forever since we cant write data
    while (1) ;
  }
}


//====================
// Reads the sensors
//====================
void pollSensors (void) {
  // read each of the analog pins and map to a percentage (inverted)
  int sensor0 = map(analogRead(A0), 1023, 0, 0, 100);
  int sensor1 = map(analogRead(A1), 1023, 0, 0, 100);
  int sensor2 = map(analogRead(A2), 1023, 0, 0, 100);
  int sensor3 = map(analogRead(A3), 1023, 0, 0, 100);
  
  String dataString = String(sensor0) + "," + String(sensor1) + "," + String(sensor2) + "," + String(sensor3);  
  
  // write out the state of the solenoid
  digitalWrite(solenoidPin, solenoidAlgm (sensor0, sensor1, sensor2, sensor3));
  writeToLCD(sensor0, sensor1, sensor2, sensor3);
  writeToSD (dataString);
  Serial.println(dataString);
}


//===============================================
// Writes the sesnor percentages to the SD Card
//===============================================
void writeToSD (String dataString) {
  dataFile.println(dataString);
  // The following line will 'save' the file to the SD card after every
  // line of data - this will use more power and slow down how much data
  // you can read but it's safer! 
  // If you want to speed up the system, remove the call to flush() and it
  // will save the file only every 512 bytes - every time a sector on the 
  // SD card is filled with data.
  dataFile.flush();
}


//===========================================
// Writes the sesnor percentages to the lcd
//===========================================
void writeToLCD(int sensor0, int sensor1, int sensor2, int sensor3) {
  // congifure lcd 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  // write display text to buffer
  display.println(String(sensor0) + " " +String(sensor1));
  display.println(String(sensor2) + " " +String(sensor3));
  // send to display
  display.display();
}


//=======================================================
// Figures out whether the solenoid should be on or off
//=======================================================
bool solenoidAlgm (int sensor0, int sensor1, int sensor2, int sensor3) {
  // simple algorithm which takes the average of the 4 sensors
  //return ((sensor0 + sensor1 + sensor2 + sensor3) / 4 < 40);
  return ((sensor0 + sensor1) / 2 < 40);
}






