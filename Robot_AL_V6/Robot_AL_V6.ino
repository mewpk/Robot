////------------- Include library ------------------
#include <Servo.h>
#include "setup_pin_Robot_DrSup.h"
#include <SoftwareSerial.h>

#define Lock_Object 75
#define UnLock_Object 120
///-------------- setup initial value ------------------
SoftwareSerial mySerial(2, 3); // RX, TX
Servo myservo1;

#define slow1 0.8 //check line lavel 1

#define slow2 0 //check line lavel 2
#define slow3 0.85 //check line lavel 2

#define Spin_speed 90
#define spinline_deboud 20
//------------------ปรับความเร็วแต่ละล้อให้ใกล้กัน ถ้าล้อขวาเร็ว ก็ใส่ค่าล้อขวาเหลือ 0.9 หมายความว่าลดความเร็วล้อขวาเหลือ 90%------------------------------
#define SpeedML 1 //ปรับความเร็วมอเตอร์ล้อซ้าย
#define SpeedMR 1 //ปรับความเร็วมอเตอร์ล้อขวา
//------------------------------------------------
int i = 0,  linecount = 0, linecheck = 0, Robot_position = 0;
int debount = 0;
int mission = 0;
int debount_in = 0;
int SpeedMotor = 255;
int MoveRobot = 0;
int sttt = 0;
unsigned long RAW_Time = 0, mint_1 = 0, mint_1_30 = 0, mint_2 = 0, timeStart = 0;
void setup()
{ Serial.begin(19200);
  mySerial.begin(19200);
  pinMode(M1_INA, OUTPUT);
  pinMode(M1_INB, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_INA, OUTPUT);
  pinMode(M2_INB, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
  pinMode(Servo2, OUTPUT);
  myservo1.attach(Servo1);
  myservo1.write(UnLock_Object);//////90หนีบ 130ปล่อย

}
void loop()
{
  while (0)
  {
    LED_ST();
  }
  while (1)
  {
    LED_ST();

    if (digitalRead(SW1) == 0)
    {
      Serial.println("X1");
      MoveRobot = Robot_Stop;
    }
    else if (digitalRead(SW2) == 0)
    {
      while (digitalRead(SW2) == 0);
      MoveRobot = Robot_StartTo3;
      if (sttt == 0)
      {
        sttt = 1;
        RAW_Time = millis() / 1000;
        timeStart = RAW_Time;
        mint_1 = RAW_Time + (60 );
        mint_1_30 = RAW_Time + (90 );
        mint_2 = RAW_Time + (120 );
      }
      Serial.println("X2");
    }


    RAW_Time = millis() / 1000;
    Serial.print(RAW_Time - timeStart);
    Serial.print(" ");
    if (MoveRobot == Robot_StartTo3)////////////////////////////////////////////////-----------3--------------------//////////////////////////////////
    {
      Move_to_line(150);
      move_line5_countV2(150, 1);
      spin2(-120);
      move_line5_countV2(120, 2);
      spin2(120);
      move_line5_countV2(120, 2);

      Serial.println("Robot_StartTo3");
      if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
      else if (RAW_Time < mint_1) MoveRobot = Robot_3ToY;
      else
      {
        Serial.println("spin");
        spin(-120);
        MoveRobot = Robot_3;
      }
    }
    else if (MoveRobot == Robot_3)////////////////////////////////////////////////-----------3--------------------//////////////////////////////////
    { Serial.println("Robot_3");
      motorR(0);
      motorL(0);
      if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
      else if (RAW_Time < mint_1_30) MoveRobot = Robot_3;
      else MoveRobot = Robot_3To1;
    }

    else if (MoveRobot == Robot_3ToY)
    {
      move_line5_countV2(120, 1);
      // delay(1000);
      Serial.println("Robot_3ToY");
      if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
      else  if (RAW_Time < mint_1) MoveRobot = Robot_YToX;
      else MoveRobot = Robot_YTo3;
    }
    else if (MoveRobot == Robot_YTo3)////////////////////////////////////////////////-----------3--------------------//////////////////////////////////
    {
      spin2(120);
      spin(120);
      move_line5_countV2(120, 1);
      // delay(1000);
      Serial.println("Robot_YTo3");
      if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
      else  if (RAW_Time < mint_1) MoveRobot = Robot_Stop;
      else
      { Serial.println("spin-");
        spin(120);
        MoveRobot = Robot_3;
      }
    }
    else if (MoveRobot == Robot_YToX)
    {

      spin2(120);
      spin(120);
      move_line5_countV2(120, 1);
      RAW_Time = millis() / 1000;
      if (RAW_Time < mint_1)
      {
        move_line5_countV2(120, 2);
        spin2(-120);
        move_line5_countV2(120, 2);
        spin2(120);
        spin(120);
        Serial.println("Robot_YToX");
        if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
        else  if (RAW_Time < mint_1) MoveRobot = Robot_XTo3;
        else MoveRobot = Robot_XTo3;
      }
      else
      {
        Serial.println("spin-");
        spin(120);
        MoveRobot = Robot_3;

      }
      // delay(1000);

    }
    else if (MoveRobot == Robot_XTo3)////////////////////////////////////////////////-----------3--------------------//////////////////////////////////
    {
      move_line5_countV2(120, 2);
      spin2(120);
      move_line5_countV2(120, 2);
      // delay(1000);
      Serial.println("Robot_XTo3");
      if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
      else  if (RAW_Time < mint_1) MoveRobot = Robot_3ToY;
      else
      { Serial.println("spin-");
        spin(-120);
        MoveRobot = Robot_3;
      }
    }
    else if (MoveRobot == Robot_3To1)
    {
      move_line5_countV2(200, 3);
      // delay(1000);
      Serial.println("Robot_3To1");
      if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
      else  if (RAW_Time < mint_2) MoveRobot = Robot_1;
      else
        MoveRobot = Robot_1;

    }
    else if (MoveRobot == Robot_1)
    {
      motorR(0);
      motorL(0);
      //  delay(1000);
      Serial.println("Robot_1");
      if (MoveRobot == Robot_Stop)MoveRobot = Robot_Stop;
      else if (RAW_Time < mint_2) MoveRobot = Robot_1;
      else
        MoveRobot = Robot_1ToZ;

    }
    else if (MoveRobot == Robot_1ToZ)
    {
      spin(120);
      move_line5_countV2(200, 1);
      // delay(1000);
      Serial.println("Robot_1ToZ");
      motorR(0);
      motorL(0);
      while (1);

    }
    else
    {
      motorR(0);
      motorL(0);
    }

  }
}
