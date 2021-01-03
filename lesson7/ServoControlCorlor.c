#include <wiringPi.h>
#include <softPwm.h>

#define ON  1
#define OFF 0

int LED_R = 3;
int LED_G = 2;
int LED_B = 5;
int ServoPin = 4;

void corlor_light(int);
void corlor_led(int, int, int);

void servo_pulse(int myangle)
{
  int PulseWidth;                    //定义脉宽变量
  PulseWidth = (myangle * 11) + 500; //将角度转化为500-2480 的脉宽值
  digitalWrite(ServoPin, HIGH);      //将舵机接口电平置高
  delayMicroseconds(PulseWidth);     //延时脉宽值的微秒数
  digitalWrite(ServoPin, LOW);       //将舵机接口电平置低
  delay(20 - PulseWidth / 1000);     //延时周期内剩余时间
  return;
}

void servo_control_color()
{
  //定义舵机转动位置
  int pos = 0;
  for (pos = 0; pos < 180; pos++)
  {
    //舵机0旋转到180,每次延时20ms
    servo_pulse(pos);
    //旋转到相应的角度,判断调用相关函数
    corlor_light(pos);
    delay(20);
  }

  for (pos = 180; pos > 0; pos--)
  {
    //舵机180旋转到0,每次延时20ms
    servo_pulse(pos);
    //旋转到相应的角度,判断调用相关函数
    corlor_light(pos);
    delay(20);
  }
  return;
}

void corlor_light(int pos)
{
  //当转动在150-180度时,点亮一种颜色
  if (pos > 150)
  {
    corlor_led(ON, OFF, OFF);
  }
  //当转动在125-150度时,点亮一种颜色
  else if (pos > 125)
  {
    corlor_led(OFF, ON, OFF);
  }
  //当转动在100-125度时,点亮一种颜色
  else if (pos > 100)
  {
    corlor_led(OFF, OFF, ON);
  }
  //当转动在75-100度时,点亮一种颜色
  else if (pos > 75)
  {
    corlor_led(OFF, ON, ON);
  }
  //当转动在50-75度时,点亮一种颜色
  else if (pos > 50)
  {
    corlor_led(ON, ON, OFF);
  }
  //当转动在25-50度时,点亮一种颜色
  else if (pos > 25)
  {
    corlor_led(ON, OFF, ON);
  }
  //当转动在0-25度时,点亮一种颜色
  else if (pos > 0)
  {
    corlor_led(ON, ON, ON);
  }
  else
  {
    corlor_led(OFF, OFF, OFF);
  }
}

void corlor_led(int v_iRed, int v_iGreen, int v_iBlue)
{
  //红色LED
  v_iRed == ON ? digitalWrite(LED_R, HIGH): digitalWrite(LED_R, LOW);
 
  //绿色LED
  v_iGreen == ON ? digitalWrite(LED_G, HIGH) : digitalWrite(LED_G, LOW);
  
  //蓝色LED
  v_iBlue == ON ? digitalWrite(LED_B, HIGH) : digitalWrite(LED_B, LOW);
}

void main()
{
  wiringPiSetup();
  
  pinMode(ServoPin, OUTPUT);
  
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  int ServoPos = 90;
  servo_pulse(ServoPos);
  
  while(1)
  {
   delay(500);
   servo_control_color();
  }
  return;
}


