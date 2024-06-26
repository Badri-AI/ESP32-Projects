
/*  Getting_BPM_to_Monitor prints the BPM to the Serial Monitor, using the least lines of code and PulseSensor Library.
 *  Tutorial Webpage: https://pulsesensor.com/pages/getting-advanced
 *
--------Use This Sketch To------------------------------------------
1) Displays user's live and changing BPM, Beats Per Minute, in Arduino's native Serial Monitor.
2) Print: "♥  A HeartBeat Happened !" when a beat is detected, live.
2) Learn about using a PulseSensor Library "Object".
4) Blinks the builtin LED with user's Heartbeat.
--------------------------------------------------------------------*/
#define TOUCH_MODULES_CST_SELF
#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include "HeartRate.h"
#include "TouchLib.h"
#include "Wire.h"
#include "pin_config.h"

TouchLib touch(Wire, PIN_IIC_SDA, PIN_IIC_SCL, CTS820_SLAVE_ADDRESS, PIN_TOUCH_RES);
bool deb=0;
//  Variables
const int PulseWire = 13;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
//const int LED = LED_BUILTIN;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 900;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 

int adc_h = 0;    
int myBPM = 0;
int flag = 0;
int t_curr =0;
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"

#define c1 0x528A //dark gray
#define c2 0xA1C7 //dark red
#define c3 0x22A4 //dark green
#define c4 0xE71C

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);
TFT_eSprite fire = TFT_eSprite(&tft);


void setup() {   

  Serial.begin(115200);          // For Serial Monitor

  // Configure the PulseSensor object, by assigning our variables to it. 
  pulseSensor.analogInput(PulseWire);   
  //pulseSensor.blinkOnPulse(LED);       //auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);
  analogReadResolution(10);   
  pinMode(PIN_POWER_ON, OUTPUT);
  digitalWrite(PIN_POWER_ON, HIGH);
  pinMode(PIN_TOUCH_RES, OUTPUT);
  digitalWrite(PIN_TOUCH_RES, LOW);
  delay(500);
  digitalWrite(PIN_TOUCH_RES, HIGH);
  Wire.begin(PIN_IIC_SDA, PIN_IIC_SCL);

  tft.init();
  tft.setSwapBytes(true);
  tft.setRotation(1);
  sprite.createSprite(320,170);
  sprite.setSwapBytes(true);

  sprite.fillSprite(TFT_WHITE);
  sprite.setTextColor(c1,TFT_WHITE);
  sprite.pushImage(100,10,80,71,HeartRate);
  


  // Double-check the "pulseSensor" object was created and "began" seeing a signal. 
   if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset. 

  }
}

void drawSprite()
{
  adc_h = analogRead(PulseWire);
  Serial.println(adc_h);
  
 
  if (pulseSensor.sawStartOfBeat()) {            // Constantly test to see if "a beat happened".
    myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                // "myBPM" hold this BPM value now. 
    //Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
    //Serial.print("BPM: ");                        // Print phrase "BPM: " 
    //Serial.println(myBPM);
    //sprite.fillSprite(TFT_WHITE);
    //sprite.setTextColor(c1,TFT_WHITE);

    sprite.setTextDatum(0);
    sprite.setTextColor(c2,TFT_WHITE);
    //sprite.drawString("HEART RATE",10,10,4);


    sprite.setTextDatum(0);
    sprite.setTextColor(TFT_BLUE,TFT_WHITE);
    sprite.drawString(String(myBPM),100,100,6);    

    sprite.pushSprite(0,0);
}

}
void loop() {

  drawSprite();
  delay(20);                    // considered best practice in a simple sketch.  
 
}

  
