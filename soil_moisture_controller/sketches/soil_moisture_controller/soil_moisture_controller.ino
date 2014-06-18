//===========================================================================//
//===========================================================================//
//                                                                           //
//    Sketch: Hydro Wall                                                     //
//    Date: Oct 2013                                                         //
//    Description: This sketch takes in inputs from 4 moisture sensors and   //
//                 and determines whether or not to turn on a solenoid to    //
//                 water the soil. The output from the sensors is written to //
//                 an SD Card and also displayed on a 5110 LCD screen.       //
//                                                                           //
//                                                                           //
//===========================================================================//
//===========================================================================//

//===========
// #includes
//===========
#include <SPI.h>
#include <SD.h>
#include <TimerOne.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <LiquidCrystal.h>

//=================
// Nokia LCD Pins
//=================
// pin 8 - Serial clock out (SCLK)
// pin 7 - Serial data out (DIN)
// pin 6 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(8, 7, 6, 5, 3);

//=================
// 2x16 LCD Pins
//=================
//  The circuit:
// * LCD RS pin to digital pin 12
// * LCD Enable pin to digital pin 11
// * LCD D4 pin to digital pin 5
// * LCD D5 pin to digital pin 4
// * LCD D6 pin to digital pin 3
// * LCD D7 pin to digital pin 2
// * LCD R/W pin to ground
// * 10K resistor:
// * ends to +5V and ground
// * wiper to LCD VO pin (pin 3)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


//================
// SD Card Config
//================
// The SD card can be connected to either the ICSP header (with the ecxeption
// of CS) or it can be connected to the following pins:
// ** UNO:  MOSI - pin 11, MISO - pin 12, CLK - pin 13, CS - pin 4 (CS pin can
// be changed) and pin #10 (SS) must be an output
// ** Mega:  MOSI - pin 51, MISO - pin 50, CLK - pin 52, CS - pin 4 (CS pin can
// be changed) and pin #52 (SS) must be an output.
// On the Ethernet Shield, CS is pin 4. Note that even if it's not used as the
// CS pin, the hardware CS pin (10 on most Arduino boards, 53 on the Mega) must
// be left as an output or the SD library functions will not work.
const int chipSelect = 4;
File dataFile;


//==============
// User Config
//==============
const long pollTime = 4; // time in seconds between polling the sensors
const long solenoidOnTime = 2; // time in seconds that the solenoid stays on


//==================
// Solenoid config
//==================
const int solenoidPin = 13;
bool solenoidState = false;


//=================
// Program Config
//=================
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  setupSD();
  
  // nokia lcd setup
  //display.begin();
  //display.setContrast(20);
  //display.clearDisplay();
  //display.display();
  
  // 2x16 lcd display
  lcd.begin(16, 2);
}

long lastPollTime = 0;
//========================
// Main Program Loop
//========================
void loop()
{
  pollSensors();
}


//========================
// SD Card Configuration
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
  int sensor0 = map(analogRead(A0), 1023, 220, 0, 100);
  int sensor1 = map(analogRead(A1), 1023, 220, 0, 100);
  int sensor2 = map(analogRead(A2), 1023, 220, 0, 100);
  int sensor3 = map(analogRead(A3), 1023, 220, 0, 100);
  
  bool solenoidState = solenoidAlgm (sensor0, sensor1, sensor2, sensor3);
  
  // put all sensor values into a comma delimited string
  String dataString = String(sensor0) + ", " + String(sensor1) + ", " 
                    + String(sensor2) + ", " + String(sensor3) + ", "
                    + String(solenoidState);
  
  // write out the state of the solenoid
  writeToLCD(sensor0, sensor1, sensor2, sensor3, solenoidState);
  writeToSD (dataString);
  Serial.println(dataString);
  
  // write the output of the solenoid algor to the solenoid pin
  digitalWrite(solenoidPin, solenoidState);
  // wait the set amount of configured amount of time
  delay(solenoidOnTime*1000);
  // turn off the solenoid
  digitalWrite(solenoidPin, 0);
  // delay the remaining time until the next poll
  delay((pollTime - solenoidOnTime)*1000);
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


//=================================================
// Writes the sesnor percentages to the nokia lcd
//=================================================
/*void writeToLCD(int sensor0, int sensor1, int sensor2, int sensor3, int solenoidState) {
  // congifure lcd 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  // write display text to buffer
  display.println(String(sensor0) + " " +String(sensor1));
  display.println(String(sensor2) + " " +String(sensor3));
  display.setTextSize(1);
  display.println  (" Water   1  2");
  if (solenoidState == 0)
    display.println("  Off    3  4");
  else
    display.println("  On     3  4");
  display.println();
  // send to display
  display.display();
}*/


//================================================
// Writes the sesnor percentages to the 2x16 lcd
//================================================
void writeToLCD(int sensor0, int sensor1, int sensor2, int sensor3, int solenoidState) {
  lcd.setCursor(0, 0);
  lcd.print(String(sensor0) + " " + String(sensor1));
  lcd.setCursor(8, 0);
  lcd.print("Water 12");
  lcd.setCursor(0, 1);
  lcd.print(String(sensor2) + " " + String(sensor3));
  lcd.setCursor(9,1);
  if (solenoidState == 0)
    lcd.print("on   34");
  else
    lcd.print("off");
}


//=======================================================
// Figures out whether the solenoid should be on or off
//=======================================================
bool solenoidAlgm (int sensor0, int sensor1, int sensor2, int sensor3) {
  // simple algorithm which takes the average of the 4 sensors
  //return ((sensor0 + sensor1 + sensor2 + sensor3) / 4 < 40);
  return ((sensor0 + sensor1) / 2 < 40);
}
