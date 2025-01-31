/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12         these have all changes look as code below to see what I used. Referr to your Tale of Pin Assignments to set your oun
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

  This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

/********************************************************************/
// First we include the libraries
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>  // include the library code:
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 8??
#define ONE_WIRE_BUS 7
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
/********************************************************************/
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 8, d4 = 12, d5 = 11, d6 = 10, d7 = 9;  // Orange, blue, red, black,    pins to auit fergus breadboard??
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
/********************************************************************/

float SoilTemp = 0;
int threshold = 22;  // not used not was used in testing for the relay
/********************************************************************/

void setup(void) {
  pinMode(3, OUTPUT);
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");
  // Start up the library
  sensors.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Tomas don't know shit!");
  delay(500);
  lcd.clear();
}
void loop(void) {
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  /********************************************************************/
  //Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures();  // Send the command to get temperature readings
  Serial.println("DONE");
  /********************************************************************/
  Serial.print("Temperature is: ");
  SoilTemp = sensors.getTempCByIndex(0);

  Serial.print(SoilTemp);  // Why "byIndex"?
                           // You can have more than one DS18B20 on the same bus.
                           // 0 refers to the first IC on the wire
  delay(100);
  /********************************************************************/  // Print to the LCD

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("Soil Temp ");
  lcd.print(SoilTemp, 1);  // prints to one decimal place
  lcd.print((char)223);    //print the small degrees symbol check out the full LCD datasheet for ASCI codes.
  lcd.print("C");

  lcd.setCursor(0, 0);
  // the 1 prints to one decil place

  /********************************************************************/

  int SetValue = analogRead(A0);

  SetValue = map(SetValue, 0, 1023, 0, 40);  //scale the value 0-1024 from the pot to 0-40 Degrees
  Serial.print("\t");
  lcd.print(SetValue);
  lcd.print(" Set Value");
  lcd.setCursor(10, 1);
  lcd.print(SetValue);  // Prints the current set value set by the Pot.



  if (SetValue > SoilTemp) {
    digitalWrite(3, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Fan ON ");
  } else {
    digitalWrite(3, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Fan OFF ");
  }

  /********************************************************************/
}
