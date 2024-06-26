#include <Wire.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;

void setup(void) 
{
  Serial.begin(9600);
  ads.begin();
}

void loop(void) 
{
  int16_t adc0;
  float volts0;
  float milli_Vol;
  adc0 = ads.readADC_SingleEnded(0);
  volts0 = ads.computeVolts(adc0);
  milli_Vol = volts0 * 1000;
  Serial.print("ADC VALUE:"); 
  Serial.print(adc0);
  Serial.print(",");
  Serial.print("MINIPID mV:"); 
  Serial.println(milli_Vol,2);  
  //Serial.println("mV");


  delay(1000);

}