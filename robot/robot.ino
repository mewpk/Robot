#include <SPI.h>
#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MCP3008.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 OLED(-1);
Adafruit_MCP3008 adc;

/////// motor R ////////
#define DR1  14  /// 8  15
#define DR2  15  /// 7  14
#define PWMR 6  /// 6   5


/////// motor L ////////
#define DL1  7  ///     4
#define DL2  4  /// 9   6
#define PWML 5  /// 5   3


const int button = 8;

////////ตัวแปรเก็บค่าแสงจากเซนเซอร์
int S0 ;
int S1 ;
int S2 ;
int S3 ;
int S4 ;


//////////ค่ากลางเซนเซอร์  เอาไว้เปนียบเทียบค่าแสง//////////
int cen0 = 650;
int cen1 = 650;
int cen2 = 650;
int cen3 = 650;
int cen4 = 650;

///////////////////////องศา เซอร์โว///////////////////////
const int v_before = 180 ;      //กำหนดค่ายกมือขึ้น servo 0
const int v_after = 0
;    //กำหนดค่ายกมือลง servo 0

///////////////ตั้งพอร์ตเซอร์โว////////////////////////////////
int servo1 = 2;  // เปิดใช้งาน s1 ที่พอร์ต 10 zackrobot & 7 kruroRobot
int servo2 = 3; // เปิดใช้งาน s1 ที่พอร์ต 11           & 8
int servo3 = 9;  // เปิดใช้งาน s1 ที่พอร์ต 12

Servo sv1;     // ประกาศการใช้งาน sv1
Servo sv2;     // ประกาศการใช้งาน sv2
Servo sv3;     // ประกาศการใช้งาน sv3


void setup()
{ OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C); // กำหนดแอดเดรสของพอร์ตจอเป็น 0x3C (for the 128x64)
  pinMode(DL1, OUTPUT);
  pinMode(DL2, OUTPUT);
  pinMode(PWML, OUTPUT);
  pinMode(DR1, OUTPUT);
  pinMode(DR2, OUTPUT);
  pinMode(PWMR, OUTPUT);

  pinMode(button, INPUT);

  ///////////// ตั้งพอร์ตเซอร์โว////////////
  sv1.attach(servo1); // เรียกใช้งานเตรียมตอบสนองเซอร์โว sv1
  sv2.attach(servo2); // เรียกใช้งานเตรียมตอบสนองเซอร์โว sv2
  sv3.attach(servo3); // เรียกใช้งานเตรียมตอบสนองเซอร์โว sv3

  adc.begin(13, 11, 12, 10);//เริ่มจากใช้ adc จาก library

}

void set_servo() {
  while (1) {
    int vr = analogRead(A7);  // กำหนดตัวแปรจำนวนเต็มอ่านค่าอนาล็อกที่พอร์ต 7
    int nob = map(vr, 0, 1023, 0, 180); // ทำการ map อัตราส่วนจากสัญญาณ analog 0-1023 เป็น 0-180
    OLED.clearDisplay();    // เคลียร์หน้าจอ oled
    OLED.setTextColor(WHITE, BLACK);  //สีอักษรเป็นสีขาว ,พื้นหลังดำ
    OLED.setCursor(0, 0);       // เซตตำแหน่ง 0,0
    OLED.setTextSize(2);        // เซตขนาดอักษรมีขนาดเป็น 2
    OLED.println(nob);     // นำค่า nob มาแสดงใน oled
    OLED.display();        // เปิดฟังก์ชันแสดงผล
    sv1.write(nob);        // สั่งเซอร์โวมอเตอร์ให้หมุนไปตามค่าองศาที่ทำการ nob ไว้
    sv2.write(nob);        // สั่งเซอร์โวมอเตอร์ให้หมุนไปตามค่าองศาที่ทำการ nob ไว้
    sv3.write(nob);        // สั่งเซอร์โวมอเตอร์ให้หมุนไปตามค่าองศาที่ทำการ nob ไว้
    delay(50);             // หน่วงเวลา 0.05 วินาที
  }
}

void analogs()
{
  S0 = adc.readADC(7);   // กำหนดตัวแปรเพื่อเก็บค่า ADC Ch0
  S1 = adc.readADC(6);   // กำหนดตัวแปรเพื่อเก็บค่า ADC Ch1
  S2 = adc.readADC(5);   // กำหนดตัวแปรเพื่อเก็บค่า ADC Ch2
  S3 = adc.readADC(4);   // กำหนดตัวแปรเพื่อเก็บค่า ADC Ch3
  S4 = adc.readADC(3);   // กำหนดตัวแปรเพื่อเก็บค่า ADC Ch4
}

void sensor()
{
  while (true) {
    analogs();

    OLED.clearDisplay();   //ล้างหน้าจอ
    OLED.setTextColor(WHITE, BLACK);  //สีอักษรเป็นสีขาว ,พื้นหลังดำ  จอที่ใช้ไม่สามารถเปลี่ยนสีได้
    OLED.setCursor(0, 0);       // เซตตำแหน่ง 0,0
    OLED.setTextSize(1);        // เซตขนาดอักษรมีขนาดเป็น 2
    OLED.print(" S0 : ");              //  แสดงข้อความ S0 :
    OLED.print(S0, DEC);     //  แสดงค่า S0
    OLED.print(" S1 : ");          //  แสดงข้อความ S1 :
    OLED.println(S1, DEC);     //  แสดงค่า S1
    OLED.print(" S2 : ");          //  แสดงข้อความ S2 :
    OLED.println(S2, DEC);     //  แสดงค่า S2
    OLED.print(" S3 : ");          //  แสดงข้อความ S3 :
    OLED.println(S3, DEC);     //  แสดงค่า S3
    OLED.print(" S4 : ");          //  แสดงข้อความ S4 :
    OLED.println(S4, DEC);     //  แสดงค่า S4
    OLED.display();  // สั่งให้ จอแสดงผล
    delay(100);
  }
}

void loop()
{

  int sw = digitalRead(button);     // ให้ sw อ่านค่า digital จากพอร์ต 2(button)
  int nob = analogRead(7);          // ให้ nob เทียบเท่าค่า A7
  int menu = map(nob, 0, 1023, 0, 9); // เทียบอัตราส่วนของพอร์ต A7 จาก 0-1023 เพื่อทำเป็นเมนู 0-12
  OLED.clearDisplay();              // ล้างค่าหน้าจอ
  OLED.setTextColor(WHITE, BLACK);  //สีอักษรเป็นสีขาว ,พื้นหลังดำ
  OLED.setCursor(0, 0);       // เซตตำแหน่ง 0,0
  OLED.setTextSize(3);        // เซตขนาดอักษรมีขนาดเป็น 2
  OLED.print("   ");         // วรรค
  OLED.println(menu);        // แสดงค่า Menu ที่ได้จากการ map nob ให้เหลือ 0-12
  OLED.setTextSize(1);        // เซตขนาดอักษรมีขนาดเป็น 2
  OLED.println(" ");
  OLED.println("  NBR.ROBOT");
  OLED.println(" ");
  OLED.print("  ");                      // วรรค
  OLED.print(nob);                     // แสดงค่าที่อ่านได้จาก nob หรือ Analog7
  OLED.println(" MeNu");
  OLED.display();
  int switchs = 1;

  if ((sw == switchs) and (menu == 0))
  {
    sensor();
  }
  if ((sw == switchs) and (menu == 1))
  {
    set_servo();
  }
  if ((sw == switchs) and (menu == 2))
  {
    menu2();
  }
  if ((sw == switchs) and (menu == 3))
  {
    menu3();
  }
  if ((sw == switchs) and (menu == 4))
  {
    menu4();
  }
  if ((sw == switchs) and (menu == 5))
  {
    menu5();
  }
  if ((sw == switchs) and (menu == 6))
  {
    menu6();
  }
  if ((sw == switchs) and (menu == 7))
  {
    menu7();
  }
  if ((sw == switchs) and (menu == 8))
  {
    menu8();
  }
  delay(100);
}

//////////////////////////////////////////////////////////////////
void T() //ตัวหลักสำหรับแก้ความเร็วบนเส้นทางท้งหมด
{
  analogs();
  if ((S0 > cen0) and (S2 > cen2)) {
    run(150,150);
  }
  if (S0 < cen0) {
    run(75,-75);
  }
  if (S2 < cen2) {
    run(-75, 75);
  }
}

////////////////////////////////////////////////////////////////////

void B() //ตัวหลักสำหรับแก้ความเร็วบนเส้นทางท้งหมด
{ while (1) {
    analogs();
    if ((S3 > cen3) and (S4 > cen4)) {
      run(-100, -100);
    }
    if (S3 < cen3) {
      run(-75, 75);
    }
    if (S4 < cen4) {
      run(75, -75);
    }
    if ((S3 < cen3) and (S4 < cen4)) {
      run(0, 0);
      break;
    }
  }
}
void Pbas (int t,int sp) {
  int t1 =0;
  while(1){
    t1++;
  analogs();
   if ((S0 > cen0) and (S2 > cen2)) {run(sp,sp);}
    if (S0 < cen0) {run(75, -75);}
    if (S2 < cen2) {run(-75,75);}
    if (S1 < cen1){run(-130,-130); delay(250);
       run(0,0); delay(100); break;}
    if (t1>=t) {PT(); break;}
}
}
void Pmew (int t,int sp) {
  int t1 =0;
  while(1){
    t1++;
  analogs();
   if ((S0 > cen0) and (S2 > cen2)) {run(sp,sp);}
    if (S0 < cen0) {run(75, -75);}
    if (S2 < cen2) {run(-75,75);}
    if (S1 < cen1){run(-130,-130); delay(250);
       run(0,0); delay(100); break;}
    if (t1>=t) {run(0,0); delay(300); break;}
}
}
void PT() //pass เส้นT ==ถ้าเซนเซอร์ทั้ง 2 ตัวเจอดำ หยุด==
{ while (1) {
    T();

    if (S1 < cen1) {
      run(-100, -100); delay(320);
      run(0, 0); delay(200); break;
    }
  }
}

void PD(int times) //วิ่งไปเรื่อยๆจนกว่าจะหมดเวลา
{ int i = 0;
  while (1) {
    T();
    if (i > times) {
      run(0, 0);
      delay(500);
      break;
    }
    i++;
  }
}

void PL() //passleave ==ถ้าเซนเซอร์ทั้ง 3 ตัวเจอดำ หยุด เพื่อที่จะทิ้งถุงยังชีพ==
{ while (1) {
    T();
    if (S1 < cen1) {
      run(0, 0);
      delay(100);
      break;
    }
  }
}

void leave() {
  sv1.write(v_before); delay(100);
  sv2.write(v_before); delay(100);
  sv3.write(v_before); delay(100);
  sv1.write(v_after); delay(100);
  sv2.write(v_after); delay(100);
  sv3.write(v_after); delay(100);
}
void MM(){
  Serial.begin(9600);
   for (int i = 0; i < 9500; i++) 
   {
  analogs();
  if (S0  > cen0) {
 sv1.write(v_before); delay(100);
  sv2.write(v_before); delay(100);
  sv3.write(v_before); delay(100);
  delay(3000);
  }
  if(S0  > cen0){

     sv1.write(v_after);
  }
   }
}


void ST(int T) { //กรณีที่จุดstartเป็นพื้นที่ที่เซ็นเซอร์ไม่สามารถวัดค่าแบบตายตัวได้
  run(250, 250); delay(T); run(0, 0); delay(10);
}

void Fall(int T) { //กรณีที่จุดstartเป็นพื้นที่ที่เซ็นเซอร์ไม่สามารถวัดค่าแบบตายตัวได้
  run(-130, -130); delay(T); run(0, 0); delay(10);
}

void LD(int T) { //เลี้ยวซ้ายโดยไม่สนเซ็นเซอร์แต่ใช้การdelayเอา
  run(-195, 195); delay(T); run(0, 0); delay(10);
}

void RD(int T) { //เลี้ยวขวาโดยไม่สนเซ็นเซอร์แต่ใช้การdelayเอา
  run(200, -200); delay(T); run(0, 0); delay(10);
}

/////////////////////////////////////////////////////////////////////

/*                             **MENU**                             */

void menu2()   /// code 2 ที่นี่
{
PT();
}
void menu3()
{
  LD(280);
}
void menu4()   /// code 4 ที่นี่
{
RD(280);
}
void menu5()   /// code 5 ที่นี่
{
RD(540);

}
void menu6()   /// code 6 ที่นี
{
    if (S1 < cen1)
    {
  sv1.write(v_before); delay(100);
  sv2.write(v_before); delay(100);
  sv3.write(v_before); delay(100);
  delay(3000);
  sv1.write(v_after); delay(100);
  sv2.write(v_after); delay(100);
  sv3.write(v_after); delay(100);
}
    else if (S1 > cen1)
    {
    delay(200);
  }
}
void menu7()   /// code 7 ที่นี่
{
  
MM();

}
void menu8()   /// code 8 ที่นี่
{
  ST(500);PT();RD(280);PT();RD(280);B();PT();RD(280);B();PT();LD(280);B();run(100,100);delay(150);run(0,0);delay(50);B();
  PL();leave();run(-100,-100);delay(200);run(0,0);delay(50);RD(540);B();run(100,100);delay(150);run(0,0);delay(50);B();
  Pmew(300,180);RD(280);B();run(100,100);delay(150);run(0,0);delay(50);B();PT();LD(280);PT();RD(280);PT();RD(280);B();PT();RD(280);B();
 PL();leave();B();run(100,100);delay(200);run(0,0);delay(200);RD(280);B();Pmew(700,180);RD(280);PT();LD(280);
 PL();leave();run(-100,-100);delay(200);run(0,0);delay(50);RD(540);B();run(100,100);delay(150);run(0,0);delay(50);B();
 PL();leave();run(-100,-100);delay(200);run(0,0);delay(50);RD(540);B();run(100,100);delay(150);run(0,0);delay(50);B();
 
 
 Pmew(570,180);LD(280);B();run(100,100);delay(150);run(0,0);delay(50);B();PT();RD(295);PT();LD(260);PT();LD(280);B();
  PT();RD(280);PT();RD(260);PT();RD(260);PT();LD(260);B();PT();LD(260);PT();LD(260);PT();run(200,200);delay(400);run(0,0);delay(100000000000);

 
}


/*
  PT();
  PD(เวลา);
  PL();
  B();
  leave();
  ST(เวลา);
  LD(เวลา);
  RD(เวลา);
  Fall(เวลา);

*/

///////////////////////////////////////////////////////////////////////
void run(int spl, int spr)
{
  if (spl > 0)
  {
    digitalWrite(DL1, LOW);
    digitalWrite(DL2, HIGH);
    analogWrite(PWML, spl);
  }
  else if (spl < 0)
  {
    digitalWrite(DL1, HIGH);
    digitalWrite(DL2, LOW);
    analogWrite(PWML, -spl);
  }
  else
  {
    digitalWrite(DL1, HIGH);
    digitalWrite(DL2, HIGH);
    analogWrite(PWMR, -255);
  }
  /////////////////////////////////////////////
  if (spr > 0)
  {
    digitalWrite(DR1, LOW);
    digitalWrite(DR2, HIGH);
    analogWrite(PWMR, spr);}
}
