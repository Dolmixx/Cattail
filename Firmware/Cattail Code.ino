#include <Servo.h>

// Constants
const int minimum = 0;
const int maximum = 30;
// pins
const int shooter1 = 8;
const int shooter2 = 13;
const int rotater = 9;
const int trigger = 4;
const int echo = 3; 

// servo setup
Servo servomotor; 
int pos = 0;

int getdistance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(10);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW); 

  int time = pulseIn(echo, HIGH);
  
  int distance = time * 0.034 / 2; 
  return distance;
  }

void setup() {
  Serial.begin(9600);
  servomotor.attach(9);

  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT); 

  pinMode(shooter1, OUTPUT);
  pinMode(shooter2, OUTPUT);

  digitalWrite(shooter1, LOW);
  digitalWrite(shooter2, LOW);


}

void loop() {
  for (pos = 0; pos <= 180; pos ++) {
    servomotor.write(pos);
    delay(10);

    int distance = getdistance();
    if (distance > minimum && distance <= maximum) {
      while (true) {
        distance = getdistance();
        if (distance <= 0) {
          digitalWrite(shooter1, LOW);
          digitalWrite(shooter2, LOW);
          Serial.println("hi");
          break;
        }
        digitalWrite(shooter1, HIGH);
        digitalWrite(shooter2, LOW); 
        delay(10);
      }
    }
  }

  for (int pos = 180; pos >= minimum; pos --) {
    servomotor.write(pos);
    delay(10);

    int distance = getdistance();

    if (distance > minimum && distance <= maximum){
      servomotor.write(pos);
      while (true) {
        int distance = getdistance();
        if (distance <=0) {
          break;
        }
        digitalWrite(shooter1, HIGH);
        digitalWrite(shooter1, LOW);
        delay(10);

      }
    }
  }

}
