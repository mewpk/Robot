////------------- Include library ------------------
#include <Servo.h>
#include "setup_pin_Robot_DrSup.h"

#define slow1 0.8 //check line lavel 1

#define slow2 0 //check line lavel 2
#define slow3 0.85 //check line lavel 2

#define P_lock 90
#define P_unlock 130


///-------------- setup initial value ------------------
Servo myservo1;
Servo myservo2;
int i = 0,  linecount = 0, linecheck = 0, Robot_position = 0;
int debount = 0;
int mission = 0;
int debount_in = 0;
int speed1 = 150;

int speedx = 200;

void setup()
{ Serial.begin(115200);
  pinMode(M1_INA, OUTPUT);
  pinMode(M1_INB, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(M2_INA, OUTPUT);
  pinMode(M2_INB, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(Sensor1, INPUT_PULLUP);
  pinMode(Sensor2, INPUT_PULLUP);
  pinMode(Sensor3, INPUT_PULLUP);
  pinMode(Sensor4, INPUT_PULLUP);
  pinMode(Sensor5, INPUT_PULLUP);
  pinMode(Sensor_Object, INPUT);

  pinMode(SW1, INPUT_PULLUP);
  pinMode(T_LED6, OUTPUT);
  pinMode(SW2, INPUT_PULLUP);

  myservo1.attach(Servo1);
  myservo2.attach(Servo2);
}
void loop()
{
  while (1)
  {
    Serial.print(digitalRead(Sensor1));
    Serial.print(digitalRead(Sensor2));
    Serial.print(digitalRead(Sensor3));
    Serial.print(digitalRead(Sensor4));
    Serial.print(digitalRead(Sensor5));
    Serial.print(digitalRead(SW1));
    Serial.println(digitalRead(SW2));

    if (digitalRead(SW1) == 0)
    {

      while (1)
      {
        AAA();
        if (digitalRead(Sensor1) == 0 || digitalRead(Sensor5) == 0)
        {
          break;
        }
      }
      motorR(0);
      motorL(0);
       
    }
    else if (digitalRead(SW2) == 0)
    {
    }
    else
    {
    }

  }
}
