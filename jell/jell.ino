#define echoPin 3 // Echo Pin
#define trigPin 2 // Trigger Pin
#define LEDPin 13 // Onboard LED
#include <Servo.h>

int pos = 0;

Servo servo_9;

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT);
  servo_9.attach(9);
  
  
  
  
  // Use LED indicator (if required)
}


  

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  if (distance >= maximumRange || distance <= minimumRange) {
    Serial.println("-1");  //เมื่ออยู่นอกระยะให้ใช้ Print -1
    digitalWrite(LEDPin, HIGH);
    (pos = 0; pos <= 180; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
    }
      (pos = 180; pos >= 0; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_9.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
      }
  }
  else {
    Serial.println(distance);  //แสดงค่าระยะทาง
    digitalWrite(LEDPin, LOW);
  }
    delay(100);
  
}
  }
