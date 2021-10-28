#include "setup_pin_Robot_DrSup.h"
void motorL(int pwm) {
  pwm=pwm*SpeedML;
  if (pwm == 0) {
    digitalWrite (M1_INA, 0);
    digitalWrite (M1_INB, 0);
    analogWrite (M1_PWM, 255);
  }
  if (pwm > 0) {
    if (pwm >= Maxspeedmotor)pwm = Maxspeedmotor;

    digitalWrite (M1_INA, 1);
    digitalWrite (M1_INB, 0);
    analogWrite (M1_PWM, pwm );
  }
  if (pwm < 0) {
    if (pwm <= -Maxspeedmotor)pwm = -Maxspeedmotor;
    digitalWrite (M1_INA, 0);
    digitalWrite (M1_INB, 1);
    analogWrite (M1_PWM, -pwm );

  }
}
void motorR(int pwm) {
   pwm=pwm*SpeedMR;
  if (pwm == 0) {
    digitalWrite (M2_INA, 0);
    digitalWrite (M2_INB, 0);
    analogWrite (M2_PWM, 255);
  }
  if (pwm > 0) {
    if (pwm >= Maxspeedmotor)pwm = Maxspeedmotor;

    digitalWrite (M2_INA, 1);
    digitalWrite (M2_INB, 0);
    analogWrite (M2_PWM, pwm );
  }
  if (pwm < 0) {
    if (pwm <= -Maxspeedmotor)pwm = -Maxspeedmotor;
    digitalWrite (M2_INA, 0);
    digitalWrite (M2_INB, 1);
    analogWrite (M2_PWM, -pwm );

  }
}
