////------------- Include library ------------------
#include <Servo.h>
#include "setup_pin_Robot_DrSup.h"
#define slow1 0.9 //check line lavel 1

#define slow2 0 //check line lavel 2
#define slow3 0.95 //check line lavel 2

#define Spin_speed 90
#define spinline_deboud 20
///-------------- setup initial value ------------------
Servo myservo1;
Servo myservo2;
int i = 0,  linecount = 0, linecheck = 0, Robot_position = 0;
int debount = 0;
int mission = 0;
int debount_in = 0;
int speed1 = 150;

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
  myservo1.write(130);//////90หนีบ 130ปล่อย
}

void loop()
{
  while (1)
  { Serial.print("Sensor = ");
    Serial.print(digitalRead(Sensor1));
    Serial.print(digitalRead(Sensor2));
    Serial.print(digitalRead(Sensor3));
    Serial.print(digitalRead(Sensor4));
    Serial.println(digitalRead(Sensor5));
    Serial.print(" SW = ");
    Serial.print(digitalRead(SW1));
    Serial.println(digitalRead(SW2));

    if (digitalRead(SW1) == 0)//สวิตซ์1ที่ตัวหุ่นยนต์
    {
move_line5_countV2(250, 2);
    spin(200);
    move_line5_countV2(250, 1);
    ////////////////////////////////////////////วิ่งไปจับSTART
    Keep_Object3();
    ////////////////////////////////////////////วิ่งไปจับEND
    move_line5_countV2(250, 2);
    spin(-200);
    move_line5_countV2(250, 4);
    spin(200);
    move_line5_countV2(250, 3);
    spin(200);
    move_line5_countV2(250, 1);
    spin(-200);
    move_line5_countV2(250, 1);
    spin(200);
    move_line5_countV2(250, 2);
    spin(200);
    move_line5_countV2(250, 1);
    ///////////////////////////////////////////วิ่งเข้าจุดเริ่มSTART
    moveout();
    move_line5_countV2(250, 1);
    spin(-200);
    move_line5_countV2(250, 2);
    spin(-200);
    move_line5_countV2(250, 3);
    spin(-200);
    move_line5_countV2(250, 1);
    spin(200);
Keep_Object();
     move_line5_countV2(250, 1);
    spin(-200);
   move_line5_countV2(250, 2); 
   spin(200);
  
      move_line5_countV2(250, 2); 
   spin(80);

  
    moveout2();
   
    move_line5_countV2(250, 2);
    spin(-200);
    move_line5_countV2(250, 1);
    spin(200);
    move_line5_countV2(250, 1);
    spin(-200);
move_line5_countV2(250, 2);
motorR(100);
  motorL(100);
  delay(200);
    spin(-200);

    move_line5_countV2(250, 2);
    spin(200);
    
    Keep_Object3();
    move_line5_countV2(250, 1);
    spin(200);
    move_line5_countV2(250, 1);
    spin(-200);
    move_line5_countV2(250, 1);
 
    moveout();
    
    move_line5_countV2(250, 2);
    Keep_Object();
    move_line5_countV2(250, 3);
    spin(200);
     move_line5_countV2(250, 2);
     motorR(100);
  motorL(100);
  delay(200);
     spin(200);
      move_line5_countV2(250, 1);
      spin(-200);
       move_line5_countV2(250, 1);
       spin(200);
        move_line5_countV2(250, 3);
     motorR(100);
  motorL(100);
  delay(700);
  motorR(0);
  motorL(0);
  myservo1.write(140);//////90หนีบ 130ปล่อย
  delay(200);
  back_with_Mid();
    ///////////////////////////


      
    }
    else if (digitalRead(SW2) == 0)//สวิตซ์2ที่ตัวหุ่นยนต์
    {
      //----------A to 1----------------------
     move_to_point(point_A);
      move_to_point(point_B);
       move_to_point(point_C);
        move_to_point(point_D);

     
    }
    else
    {
      digitalWrite(T_LED6, 0);//สั่งให้ LED6 ที่ตัวหุ่นยนต์ดับ
      motorR(0);
      motorL(0);

    }
    myservo1.write(130);//////มือจับ 90หนีบ 130ปล่อย
  }
}
