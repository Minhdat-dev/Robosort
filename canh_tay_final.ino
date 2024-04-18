
#include <Servo.h>
#include<Wire.h>

Servo kep;
Servo truc;
Servo cotay;
Servo lenxuong;
int currentAngle[4]  = {20, 10, 5, 20};
void setup(){

  Serial.begin(9600);
  kep.attach(3);
  truc.attach(9);
  cotay.attach(5);
  lenxuong.attach(7);
  }
  void RotateServo(int index, int angle)
{
  int i;
  if(currentAngle[index] < angle)
  {
    for(i = currentAngle[index]; i < angle; i+=2)
    {
      if(index == 0) kep.write(i);
      else if(index == 1) cotay.write(i);
      else if(index == 2) lenxuong.write(i);
      else if(index == 3) truc.write(i);
      delay(100);
    }
    currentAngle[index] = angle;
  }
  else if(currentAngle[index] > angle)
  {
    for(i = currentAngle[index]; i > angle; i-=2)
    {
        if(index == 0) kep.write(i);
        else if(index == 1) cotay.write(i);
        else if(index == 2) lenxuong.write(i);
        else if(index == 3) truc.write(i);
        delay(100);
    }
    currentAngle[index] = angle;
  }
  
  
  
}
void loop(){
 if(Serial.available()>0){
  int str = Serial.read();
  Serial.println(str);
  if(str == 1){
    RotateServo(2, 90);
    RotateServo(1, 20);
    RotateServo(0, 130);
    RotateServo(2, 180);
    RotateServo(3, 120);
    delay(1000);
    RotateServo(0, 180);
    RotateServo(1, 20);
    RotateServo(3, 60);
    delay(1000);
    }
  else if(str == 2){
    RotateServo(2, 90);
    RotateServo(1, 20);
    RotateServo(0, 130);
    RotateServo(2, 180);
    RotateServo(3, 0);
    delay(1000);
    RotateServo(0, 180);
    RotateServo(1, 20);
    RotateServo(3, 60);
    delay(1000);
    }
  else if(str == 3){
    RotateServo(2, 90);
    RotateServo(1, 20);
    RotateServo(0, 130);
    RotateServo(2, 180);
    RotateServo(3, 30);
    delay(1000);
    RotateServo(0, 180);
    RotateServo(1, 20);
    RotateServo(3, 60);
    delay(1000);
    }
 }
  }
