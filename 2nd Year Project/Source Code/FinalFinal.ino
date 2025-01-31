#include <Arduino.h>
//#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "rgb_lcd.h"
#include "DHT20.h"  // Include the DHT20 library


// Pin Definitions
#define ONE_WIRE_BUS 7          // Pin for Dallas temperature sensor
#define RELAY_PIN 8             // Pin for relay connected to the fan
#define POT_PIN A0              // Analog pin connected to the potentiometer
#define BUTTON_PIN 12           // Button pin for changing the display
#define LDR_PIN A1              // LDR connected to analog pin A1


// Constants for the LDR readings
#define MAX_ADC_READING 1023
#define ADC_REF_VOLTAGE 5.03
#define REF_RESISTANCE 10160
#define LUX_CALC_SCALAR 2355175
#define LUX_CALC_EXPONENT -1.2109


// Sensor setup
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT20 DHT;  // Instantiate the DHT20 sensor object


// LCD setup
rgb_lcd lcd;
const int colorR = 50;
const int colorG = 50;
const int colorB = 255;


// Variables for storing temperature and control logic
float SoilTemp = 0;
bool FanState = false;
int SetValue = 0;              // Read temperature from potentiometer for setting
int temp_limit = 0;            // Variable to store the temperature limit
int menu = 0;                  // Menu state variable
float ldrLux = 0;              // Variable to store LDR lux value


float humidity = 22;  // Get humidity from DHT20
float temperature = 33;  // Get temperature from DHT20


void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);          // Initialize the LCD
    lcd.setRGB(colorR, colorG, colorB);
    lcd.setCursor(4, 0);
    lcd.print("TU Tech");  // Initial message on LCD
    delay(2000);               // Wait for 2 seconds
    lcd.clear();


    pinMode(RELAY_PIN, OUTPUT);  // Set the relay pin as an output
    digitalWrite(RELAY_PIN, LOW);  // Ensure relay is off at start
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Setup button

    sensors.begin();  // Start the Dallas temperature sensor library
    DHT.begin();      // Initialize the DHT20 sensor
}


void loop() { // Display based on menu state. Menu is updated every 4 seconds
 
 int status = DHT.read();  //this is the line I added ---
   
 
humidity = DHT.getHumidity();  // Get humidity from DHT20
temperature = DHT.getTemperature(); 


delay(1000);


    ldrLux = calculateLux();  // Calculate LDR lux value
    sensors.requestTemperatures();  // Request new temperature reading from Dallas sensor
    SetValue = analogRead(POT_PIN); // Read and scale the set value from the potentiometer
    temp_limit = map(SetValue, 0, 1023, 0, 40);  // Scale the value from 0-1023 to 0-40 degrees
    SoilTemp = sensors.getTempCByIndex(0);  // Get temperature reading
    
    


    for (menu >=4; menu++;){
    switch(menu) {
        case 0:
        lcd.setCursor(0, 0);
            
            lcd.setCursor(0, 0);
            lcd.print("Soil Temp: ");
            lcd.print(SoilTemp, 1);
            lcd.print((char)223);
            lcd.print("C");
            lcd.setCursor(0, 1);
            lcd.print("Set Value: ");
            lcd.print(temp_limit);
            lcd.print((char)223);
            lcd.print("C");
            delay(4000); // delays the flipping of menu for 4 seconds
            lcd.clear();
            break;


        case 1:
            lcd.setCursor(0, 0);
            lcd.print("Probe Temp");
            lcd.setCursor(0, 1);
            lcd.print(SoilTemp, 1);
            lcd.print((char)223);
            delay(4000); // delays the flipping of menu for 4 seconds
            lcd.clear();
            break;


        case 2:
            lcd.setCursor(0, 0);
            lcd.print("Temp Limit");
            lcd.setCursor(0, 1);
            lcd.print(temp_limit);
            lcd.print((char)223);
            lcd.print("C");
            delay(4000); // delays the flipping of menu for 4 seconds
            lcd.clear();
            break;


        case 3:
            lcd.setCursor(0, 0);
            lcd.print("LDR Lux:");
            lcd.setCursor(0, 1);
            lcd.print(ldrLux);
            lcd.print(" lux");
            delay(4000); // delays the flipping of menu for 4 seconds
            lcd.clear();
            break;
        case 4:
            lcd.setCursor(0, 0);
            lcd.print("DHT20 Temp:");
            lcd.print(temperature, 1);
            lcd.print((char)223);
            lcd.print("C");
            lcd.setCursor(0, 1);
            lcd.print("Humidity:");
            lcd.print(humidity, 1);
            delay(4000); // delays the flipping of menu for 4 seconds
            lcd.clear();
            break;
        


     }
    }


    // Fan control logic with hysteresis
    manageFan(SoilTemp, temp_limit);
    delay(500);  // Short delay to prevent rapid firing of the loop
}


float calculateLux() {
    int ldrRawData = analogRead(LDR_PIN);
    float resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;
    float ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
    float ldrResistance = ldrVoltage / resistorVoltage * REF_RESISTANCE;
    float lux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);
    return lux;
}


void manageFan(float currentTemp, int setTemp) {
    if (FanState && currentTemp <= setTemp) {
        digitalWrite(RELAY_PIN, LOW);
        lcd.setCursor(5, 1);
        lcd.print("Fan OFF");  // Clear rest of line
        FanState = false;
    } else if (!FanState && currentTemp > setTemp) {
        digitalWrite(RELAY_PIN, HIGH);
        lcd.setCursor(5, 1);
        lcd.print("Fan ON");  // Clear rest of line
        FanState = true;
    }
}