int forcePin = 34; // input pin for the Force sensor
int irPin = 35;  // input pin for the IR sensor
int forceValue = 0;// variable to store the value coming from the sensor
int irValue = 0;
#define NB_SAMPLE 25
int ir_val[NB_SAMPLE];
int distanceCM;

//Load Cell
#include "HX711.h"

const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 4;

HX711 scale;


void setup(){
  Serial.begin(115200);
  Serial.println("Load Cell Interfacing with ESP32");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale(4900.28);    // this value is obtained by calibrating the scale with known weights as in previous step
  scale.tare();				         // reset the scale to 0 
}

void loop(){
 forceValue = analogRead(forcePin);// read the value from the analog channel
 Serial.print("Force value = ");
 Serial.println(forceValue);       //print digital value on serial monitor
 irValue = analogRead(irPin);// read the value from the analog channel
 Serial.print("IR ADC = ");
 Serial.println(irValue);       //print digital value on serial monitor
 Serial.println(" ");
//  Serial.print("Dist cm = ");
//  Serial.println(" "); 
 for (int i=0; i<NB_SAMPLE; i++){
        // Read analog value
        ir_val[i] = analogRead(irPin);
    }

 // Sort it 
 sort(ir_val,NB_SAMPLE);

 //y = 0.0053x - 3.3855

 distanceCM = 0.0053 * ir_val[NB_SAMPLE / 2] - 3.3855;
 Serial.print("Dist << 15 in cm  = ");
 Serial.println(distanceCM);

//y = 56004x-1.002
 distanceCM = 56004 * pow(ir_val[NB_SAMPLE / 2],-1.002);
 Serial.print("Dist >> 15 in cm  = ");
 Serial.println(distanceCM);


 Serial.println(" ");
 Serial.print("Weight: ");
 Serial.println(scale.get_units(10), 2);
 Serial.println(" ");
 scale.power_down();			        // put the ADC in sleep mode
 delay(1000);
 scale.power_up();



 distanceCM = 60.374 * pow(map(ir_val[NB_SAMPLE / 2], 0, 4095, 0, 5000)/1000.0, -1.16);
// Serial.print("IR Dist in cm  = ");
 //Serial.println(distanceCM);
 

 //delay(1000);
}





void sort(int a[], int size) {
    for(int i=0; i<(size-1); i++) {
        bool flag = true;
        for(int o=0; o<(size-(i+1)); o++) {
            if(a[o] > a[o+1]) {
                int t = a[o];
                a[o] = a[o+1];
                a[o+1] = t;
                flag = false;
            }
        }
        if (flag) break;
    }
}

