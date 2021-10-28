void AAA()
{
  if (digitalRead(Sensor2) == 0 && digitalRead(Sensor3) == 0 && digitalRead(Sensor4) == 0)
  {
    motorR(250);
    motorL(250);
  }
  else if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 0 && digitalRead(Sensor4) == 1)
  {
    motorR(255);
    motorL(255);
  }
  else if (digitalRead(Sensor2) == 1 && digitalRead(Sensor3) == 0 && digitalRead(Sensor4) == 0)
  {
    motorR(255*0.8);
    motorL(255);
  }
}
