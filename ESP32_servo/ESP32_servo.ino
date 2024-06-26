


#include <ESP32Servo.h> 

Servo myservo;  // create servo object to control a servo

int servoPin = 13;

char result=0;
int td=1000;
int pos=0;
void setup()
{
  
  Serial.begin(115200);
  	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);// Standard 50hz servo
  myservo.attach(servoPin, 500, 2400); 
  
}

void loop() {
  // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
	// 	// in steps of 1 degree
	// 	myservo.write(pos);    // tell servo to go to position in variable 'pos'
	// 	delay(15);             // waits 15ms for the servo to reach the position
	// }
  // delay(5000);
	// for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
	// 	myservo.write(pos);    // tell servo to go to position in variable 'pos'
	// 	delay(15);             // waits 15ms for the servo to reach the position
	// }
  // delay(5000);


  result=Serial.read();
  myservo.write(90);
  //delay(td);
  if(result=='o'){
    Serial.println(result);
    myservo.write(0);delay(td);
    myservo.write(90);delay(td);
    // for (pos = 90; pos <= 180; pos += 1) {
    //   myservo.write(pos);delay(tdelay);}

    // for (pos = 180; pos >= 90; pos -= 1) {
    //   myservo.write(pos);delay(tdelay);}
  }

  else if(result=='d'){
    Serial.println(result);
    myservo.write(180);delay(td);
    myservo.write(90);delay(td);
    // for (pos = 90; pos >= 0; pos -= 1) {
    //   myservo.write(pos);delay(tdelay);}

    // for (pos = 0; pos <= 90; pos += 1) {
    //   myservo.write(pos);delay(tdelay);}

  }

  else {
    result=0;
      
    }
      
}