#define Servo1 11
#define Servo2 10
#define M1_INB 7
#define M1_INA 8
#define M1_PWM 6
#define M2_INB 12
#define M2_INA 13
#define M2_PWM 5
//***** set Joy pin *********
#define Up A4
#define Down A5
#define Left A3

#define right A0
#define X1 A1
#define X2 A2
#include <Servo.h>
Servo myservo1;
Servo myservo2;
int servomin = 90;
int servomax = 130;
int speedmotor=255;
 int positionservo=servomax;
void setup()
{ Serial.begin(9600);
  pinMode(M1_INA, OUTPUT);
  pinMode(M1_INB, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_INA, OUTPUT);
  pinMode(M2_INB, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(Up, INPUT_PULLUP);
  pinMode(Down, INPUT_PULLUP);
  pinMode(Left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(X1, INPUT_PULLUP);
  pinMode(X2, INPUT_PULLUP);
  myservo1.attach(Servo1);
  myservo2.attach(Servo2);
  myservo1.write(servomax);
  myservo2.write(90);
}
void loop()
{
  if (digitalRead(Up) == 0)
  {
    Serial.println("up");
     digitalWrite(M2_INB, 1);
     digitalWrite(M2_INA, 0);
     analogWrite(M2_PWM, speedmotor);
      digitalWrite(M1_INB, 1);
     digitalWrite(M1_INA, 0);
     analogWrite(M1_PWM, speedmotor);
  }
  else if (digitalRead(Left) == 0)
  {
    Serial.println("left");
     digitalWrite(M1_INB, 1);
     digitalWrite(M1_INA, 0);
     analogWrite(M1_PWM, 125);
   /* digitalWrite(M1_INB, 0);
     digitalWrite(M1_INA, 1);
     analogWrite(M1_PWM, 200);*/
  }
  else if (digitalRead(right) == 0)
  {
    Serial.println("right");
     digitalWrite(M2_INB, 1);
     digitalWrite(M2_INA, 0);
     analogWrite(M2_PWM, 125);
 /*     digitalWrite(M2_INB, 0);
     digitalWrite(M2_INA, 1);
     analogWrite(M2_PWM, 200);*/
  }
  else if (digitalRead(Down) == 0)
  {
    Serial.println("down");
     digitalWrite(M2_INB, .0);
     digitalWrite(M2_INA, 1);
     analogWrite(M2_PWM, speedmotor);
      digitalWrite(M1_INB, 0);
     digitalWrite(M1_INA, 1);
     analogWrite(M1_PWM, speedmotor);
  }

  else if (digitalRead(X1) == 0)
  {
    Serial.println("X1");
   
    if (positionservo <= servomin){
      positionservo=servomin; }
      else { positionservo=positionservo-3;
        myservo1.write(positionservo);
        delay(20);
    }
  }

     else if (digitalRead(X2) == 0)
  {
    Serial.println("X2");
   
    if (positionservo >= servomax){
      positionservo=servomax; }
      else { positionservo=positionservo+3;
        myservo1.write(positionservo);
        delay(20);
    }
  
  }
  
  else
  {
    Serial.println("No SW");
    digitalWrite(M2_INB, 0);
     digitalWrite(M2_INA, 0);
     analogWrite(M2_PWM, 0);
  digitalWrite(M1_INB, 0);
     digitalWrite(M1_INA, 0);
     analogWrite(M1_PWM, 0);
  }
}
