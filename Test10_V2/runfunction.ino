/*
 * move_to_point(จุดที่จะวิ่งไปหยิบชิ้นงาน)
 * move_line5_countV2(ความเร็วที่ใช้ไม่เกิน255, จำนวณเส้นตัดที่จะวิ่ง);
 * spin(ความเร็วในการหมุนตัว+หมุนทางขวา,-หมุนทางซ้าย); จะหมุน1เส้นตัด
 * spin2(ความเร็วในการหมุนตัว+หมุนทางขวา,-หมุนทางซ้าย); หุ่นยนต์จะเดินหน้าไปจนกลางหุ่นอยู่ตรงเส้นตัด แล้วจะหมุน 90 องศา หรือ 1 เส้นตัด
 * Keep_Object(); ใช้วิ่งเข้าไปจับชิ้นงานแล้วหุ่นยนต์จะหยุดที่จุดวางชิ้นงานพร้อมกลับหลังหันให้
 *  moveout(); ใช้วิ่งไyปวางชิ้นงานที่จุด Start จากนั้นจะกลับหลังหันให้
 */

void move_to_point(int point)
{
 if (point == point_A)
  {
    move_line5_countV2(250, 2);
    spin(200);
    move_line5_countV2(250, 1);
    ////////////////////////////////////////////วิ่งไปจับSTART
    Keep_Object3();
    ////////////////////////////////////////////วิ่งไปจับEND
    move_line5_countV2(250, 2);
    spin(-200);
    move_line5_countV2(250, 3);
    spin(200);
    move_line5_countV2(250, 1);
    spin(200);
    move_line5_countV2(250, 1);
    ///////////////////////////////////////////วิ่งเข้าจุดเริ่มSTART
    moveout();
    ///////////////////////////////////////////วิ่งเข้าจุดเริ่มEND
  }
  else if (point == point_B)
  {
   move_line5_countV2(250, 1);
    spin(-200);
    
  
    move_line5_countV2(250, 1);
    spin(-200);
    move_line5_countV2(250, 1);
     spin(200);
     Keep_Object4();
     
    move_line5_countV2(250, 1);
    spin(200);
   move_line5_countV2(250, 1); 
   spin(150);
   move_line5_countV2(250, 1); 
   spin(-200);
   move_line5_countV2(250, 1); 
   spin(200);
      move_line5_countV2(250, 2); 
   spin(100);
 
    moveout2();
  }
  else if (point == point_C)
  {
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
    }
  else if (point == point_D)
  {
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
 
   }
else
{
  
}
}
