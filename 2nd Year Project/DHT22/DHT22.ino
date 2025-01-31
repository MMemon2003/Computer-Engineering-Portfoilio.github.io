/* 
 COnnecting the DHT22 Temperature and humidity Sensor to an Arduino uno

You will need to install the Liabrarys using the library manager to operate this sensor.
I used the DHT22 liabrary by Sparkfun (Search for "Sparkfun RHT03 Arduino Library").
 
*/

//Libraries  
#include <DHT.h>;

//Constants
#define DHTPIN 9     // Connect the sensor pin 2 to Pin 2 on the Uno
#define DHTTYPE DHT22   // DHT 22  (AKA  AM2302)
DHT dht(DHTPIN, DHTTYPE); // Initialise the DHT sensor for normal 16mhz Arduino


//Variables

float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup()
{
  
  Serial.begin(9600);
  dht.begin();

}

void loop()
{
    //Read the data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp = dht.readTemperature();
    //Print the temp and humidity values to the serial monitor
    Serial.print(" Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius ");
    delay(2000); //Delay 2 sec.
}

   
