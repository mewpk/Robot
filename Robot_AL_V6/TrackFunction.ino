
#include "setup_pin_Robot_DrSup.h"

void tracker_line(int speedx)
{
  LED_ST();
  if (digitalRead(SW1) == 0)
  {
    Serial.println("X1");
    MoveRobot = Robot_Stop;
    linecount = 99;
  }
  if (digitalRead(Sensor2) == 0 && digitalRead(Sensor3) == 0 && digitalRead(Sensor4) == 0)
  {
    Robot_position = 0;
    motorR(speedx);
    motorL(speedx);
  }
  else if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 0 && digitalRead(Sensor4) == 1)
  {

    Robot_position = 0;
    motorR(speedx);
    motorL(speedx);
  }
  else if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 0 && digitalRead(Sensor4) == 0)
  {
    Robot_position = 1;
    motorR(speedx * slow1);
    motorL(speedx);
  }
  else if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 1 && digitalRead(Sensor4) == 0)
  { Robot_position = 1;
    motorR(speedx * slow2);
    motorL(speedx * slow3);
  }
  else if (digitalRead(Sensor2) == 0 && digitalRead(Sensor3) == 0 && digitalRead(Sensor4) == 1)
  {
    Robot_position = 2;
    motorR(speedx);
    motorL(speedx * slow1);
  }
  else if (digitalRead(Sensor2) == 0 && digitalRead(Sensor3) == 1 && digitalRead(Sensor4) == 1)
  {
    Robot_position = 2;
    motorR(speedx * slow3);
    motorL(speedx * slow2);
  }
  else
  {
    if (Robot_position == 1)
    {
      motorR(0);
      motorL(speedx * slow3);
    }
    else if (Robot_position == 2)
    {
      motorL(0);
      motorR(speedx * slow3);
    }
    else {
      motorR(100);
      motorL(100);
    }
  }
}
void spin2(int speed)
{
  int spinline = 0;
  motorR(150);
  motorL(150);
  Robot_position = 0;
  while (1)
  {
    tracker_line(speed);
    if (digitalRead(Sensor1) == 0 || digitalRead(Sensor5) == 0)break;
  }

  motorR(-speed);
  motorL(speed);
  //  delay(200);

  while (1)
  { LED_ST();
    if (digitalRead(SW1) == 0)
    {
      Serial.println("X1");
      MoveRobot = Robot_Stop;
      break;
    }
    if (spinline >= spinline_deboud)
    { spinline = 0;
      motorR(0);
      motorL(0);
      break;
    }
    if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 1 && digitalRead(Sensor4) == 1)spinline++;
    else spinline = 0;
    motorR(-speed);
    motorL(speed);
  }
  while (1)
  { LED_ST();
    if (digitalRead(SW1) == 0)
    {
      Serial.println("X1");
      MoveRobot = Robot_Stop;
      break;
    }
    motorR(-speed);
    motorL(speed);
    if (digitalRead(Sensor2) == 1 && (digitalRead(Sensor3) == 0 || digitalRead(Sensor4) == 0))spinline++;
    else if ((digitalRead(Sensor2) == 0 || digitalRead(Sensor3) == 0) && digitalRead(Sensor4) == 1)spinline++;
    else spinline = 0;

    if (spinline >= 2)
    { break;
      motorR(0);
      motorL(0);
    }
  }
}
void spin(int speed)
{
  int spinline = 0;

  motorR(-speed);
  motorL(speed);
  delay(200);

  while (1)
  { LED_ST();
    if (digitalRead(SW1) == 0)
    {
      Serial.println("X1");
      MoveRobot = Robot_Stop;
      break;
    }
    if (spinline >= spinline_deboud)
    { spinline = 0;
      motorR(0);
      motorL(0);
      break;
    }
    if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 1 && digitalRead(Sensor4) == 1)spinline++;
    else spinline = 0;
    motorR(-speed);
    motorL(speed);
  }
  while (1)
  { LED_ST();
    if (digitalRead(SW1) == 0)
    {
      Serial.println("X1");
      MoveRobot = Robot_Stop;
      break;
    }
    motorR(-speed);
    motorL(speed);
    if (digitalRead(Sensor2) == 1 && (digitalRead(Sensor3) == 0 || digitalRead(Sensor4) == 0))spinline++;
    else if ((digitalRead(Sensor2) == 0 || digitalRead(Sensor3) == 0) && digitalRead(Sensor4) == 1)spinline++;
    else spinline = 0;

    if (spinline >= 2)
    { motorR(0);
      motorL(0);
      break;

    }
  }
}

void Move_to_line(int speedx)
{
  while (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 1 && digitalRead(Sensor4) == 1)
  { LED_ST();
    motorR(speedx);
    motorL(speedx );
  }

  // delay(300);
}
void move_line5_countV2(int speedx, int count)
{
  long incout = 0, incout_T = 0;
  linecount = 0;
  linecheck = 0;
  debount = 0;
  int gg = 1;
  incout_T = millis();
  while (1)
  {

    if (linecount >= count)break;


    if ((digitalRead(Sensor1) == 0 || digitalRead(Sensor5) == 0) && millis() - incout_T > 400)//เจอเส้นตัด จะเช็คเมื่อผ่านไป 400 mS
    {
      debount_in++;
    }
    else
    {
      debount_in--;
      if (debount_in < 0)debount_in = 0;
    }
    if (debount_in > 7)//เจอเส้นตัดนานพอไหม
    {
      if (gg == 1) {
        linecount++;//นับเส้นตัด
        gg = 0;
      }
      debount_in = 8;
      linecheck = 1;
      debount = 0;
    }
    else //เลยเส้นตัดไปแล้ว
    {
      if (linecheck == 1)
      {
        debount++;
        Serial.print("debount");
        Serial.println(debount);
      }
      else
      {
        debount = 0;
      }
      if (linecheck == 1 && debount >= 1)//เช็คว่าเลยเส้นตัดไปนานพอหรือยัง
      { //Serial.print("debount = 2");
        linecheck = 0;
        // linecount++;
         incout_T = millis();
        gg = 1;
        Serial.print("linecount");
        Serial.println(linecount);
        debount = 0;
      }
    }
    /////////////////////--------------------tracker_line-----------------------------------
    tracker_line(speedx);
  }
}
void move_line5_countV3(int speedx, int count)
{
  long incout = 0, incout_T = 0;
  linecount = 0;
  linecheck = 0;
  debount = 0;
  int gg = 1;

  while (1)
  {

    if (linecount >= count)break;


    if ((digitalRead(Sensor2) == 0 && digitalRead(Sensor4) == 0))//เจอเส้นตัด จะเช็คเมื่อผ่านไป 400 mS
    {
      debount_in++;
    }
    else
    {
      debount_in--;
      if (debount_in < 0)debount_in = 0;
    }
    if (debount_in > 7)//เจอเส้นตัดนานพอไหม
    {
      if (gg == 1) {
        linecount++;//นับเส้นตัด
        gg = 0;
      }
      debount_in = 8;
      linecheck = 1;
      debount = 0;
    }
    else //เลยเส้นตัดไปแล้ว
    {
      if (linecheck == 1)
      {
        debount++;
        Serial.print("debount");
        Serial.println(debount);
      }
      else
      {
        debount = 0;
      }
      if (linecheck == 1 && debount >= 1)//เช็คว่าเลยเส้นตัดไปนานพอหรือยัง
      { //Serial.print("debount = 2");
        linecheck = 0;
        //linecount++;
        gg = 1;
        Serial.print("linecount");
        Serial.println(linecount);
        debount = 0;
      }
    }
    /////////////////////--------------------tracker_line-----------------------------------
    tracker_line(speedx);
  }
}
void back_with_Mid() //use front sensor for detect
{
  motorR(-150);
  motorL(-150);
  while (1)
  {
    if (digitalRead(Sensor1) == 0 || digitalRead(Sensor5) == 0)break;
  }
  motorR(0);
  motorL(0);
}
void go_To_outline()
{
  motorR(120);
  motorL(120);
  while (1)
  {
    tracker_line(120);
    if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 1 && digitalRead(Sensor4) == 1)break;
  }
  motorR(0);
  motorL(0);
}
void moveout()
{
  motorR(-150);
  motorL(-150);
  delay(250);
  motorR(0);
  motorL(0);
  myservo1.write(140);//////90หนีบ 130ปล่อย
  delay(200);


}
void moveout2()
{
  motorR(100);
  motorL(100);
  delay(700);
  motorR(0);
  motorL(0);
  myservo1.write(140);//////90หนีบ 130ปล่อย
  delay(200);
  back_with_Mid();
  spin(200);
  spin(200);
}
int Keep_Object()//หยิบชิ้นงานแล้วหุ่นจะจอดที่จุดวางชิ้นงาน
{
  ////////////////////////////////////////////วิ่งไปจับSTART
  move_line5_countV2(150, 1);
  motorR(0);
  motorL(0);
  myservo1.write(90);//////90หนีบ 130ปล่อย
  delay(100);
  // spin(200);
  //spin(200);
  ////////////////////////////////////////////วิ่งไปจับEND

}
