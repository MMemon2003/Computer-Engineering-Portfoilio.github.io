/* 
 *  
 *  works fine - places the calculation into a function - USe this if copying into existing code - FM
 *  
 *  LDR Lux Meter
 *  origional By David Williams
 *  Modified by Fergus
 *  https://www.allaboutcircuits.com/projects/design-a-luxmeter-using-a-light-dependent-resistor/ 
 *  the constants LUX_CALC_SCALAR and  LUX_CALC_EXPONENT were found by setting up an expiernment in the lab using the Light box. 
 *  The data was then plotted and the slope and offset found. I will post the excell sheet I used for this on Moodle.
 *  
 *  when you have this data - or just use mine - plug it into the code as I have done.
 *  **********************************************************************************
 *  
 *  This sketch calculates the lux from a voltage reading of a voltage divider circuit
 *  
 *  The hardware connected to Analog Pin 1 should be a voltage divider circuit between an LDR and a 
 *  resistor (nominally 10kohm).  The resistor should be connected to ground and the LDR should be
 *  connected to 5V.  The point in between should be connected to Analog Pin 1 - (I used Analoug pin 1).
 *  
 *  There are three steps to this
 *  
 *  1) Calculate voltage based on reading
 *  2) Calculate resistance of LDR based on voltage
 *  3) Calculate the lux that must be falling on LDR based on the resistance
 *   
 *  
 *  I have it available in Labview also. Might be on the student share..
*/


//#include <Wire.h>

// These constants, define values needed for the LDR readings and ADC
#define LDR_PIN                   1    // LDR connected to analoug input pin on the arduino - I used Pin 1
#define MAX_ADC_READING           1023 // already set - leave this alone.
#define ADC_REF_VOLTAGE           5.03  // Voltage supply to the voltage divider.. (Measure it)
#define REF_RESISTANCE            10160  // measure this for best results, Fergus is using a 10K resistor so set this to 10K
#define LUX_CALC_SCALAR           2355175 //from Excell sheet - scalar (10^(y-intercept))  - This Y intecept is found by experimentation using the light box and a lux meter. I need to develope a lab sheet for this.
#define LUX_CALC_EXPONENT         -1.2109   // From Excell sheet - Slope of plot - from Excel

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
void setup(void) 
{
  Serial.begin(9600);
  Serial.println(F("Light Sensor Test")); Serial.println("");
  delay(1000);
}

/**************************************************************************/

    

/**************************************************************************/
void loop(void) 
{  
  
Lux_Value();
  
}



float Lux_Value()
{
  int   ldrRawData;
  float resistorVoltage, ldrVoltage;
  float ldrResistance;
  float ldrLux;
  
  // Perform the analog to digital conversion  
  ldrRawData = analogRead(LDR_PIN);
 
  // RESISTOR VOLTAGE_CONVERSION  Step 1
  // Convert the raw digital data back to the voltage that was measured on the analog pin
  resistorVoltage = (float)ldrRawData / MAX_ADC_READING * ADC_REF_VOLTAGE;         //   Res Voltage =  (raw data / 1023) * 5

  // voltage across the LDR is the 5V supply minus the 10k resistor voltage
  ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
  
  // LDR_RESISTANCE_CONVERSION   Step 2
  // resistance that the LDR would have for that voltage  
  ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
  
  // LDR_LUX                     Step 3
  // Change the code below to the proper conversion from ldrResistance to
  // ldrLux
  
  ldrLux = LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);   // This is the formula that calculates Lux... See lab notes that I havent written yet(20/2/2020)!!!!!
 
  // print out the results
  Serial.print("LDR Raw Data   : "); Serial.println(ldrRawData);
  Serial.print("LDR Voltage    : "); Serial.print(ldrVoltage); Serial.println(" volts");
  Serial.print("LDR Resistance : "); Serial.print(ldrResistance); Serial.println(" Ohms");
  Serial.print("LDR Illuminance: "); Serial.print(ldrLux); Serial.println(" lux");
 
  return(ldrLux);
  delay(500);
  

}

