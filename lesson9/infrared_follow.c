#include <wiringPi.h>
#include <softPwm.h>

int AIN1 = 28;     
int AIN2 = 29;   
int BIN1 = 24;    
int BIN2 = 25;  
int PWMA = 27;    
int PWMB = 23;   
int key = 10;               
const int FollowSensorLeft =  26; 
const int FollowSensorRight = 0;  
int LeftSensorValue ;           
int RightSensorValue ;

void run()
{
  digitalWrite(AIN1, HIGH);  
  digitalWrite(AIN2, LOW); 
  softPwmWrite(PWMA, 50);
  digitalWrite(BIN1, HIGH); 
  digitalWrite(BIN2, LOW);
  softPwmWrite(PWMB, 50);
}

void brake()
{
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void left()
{
  digitalWrite(AIN1, LOW);    
  digitalWrite(AIN2, LOW);  
  softPwmWrite(PWMA, 0);
  digitalWrite(BIN1, HIGH);  
  digitalWrite(BIN2, LOW); 
  softPwmWrite(PWMB, 50);
}

void right()
{
  digitalWrite(AIN1, HIGH);  
  digitalWrite(AIN2, LOW); 
  softPwmWrite(PWMA, 50);
  digitalWrite(BIN1, LOW);  
  digitalWrite(BIN2, LOW);
  softPwmWrite(PWMB, 0);
}

void spin_left(int time)
{
  digitalWrite(AIN1, LOW);    
  digitalWrite(AIN2, HIGH); 
  softPwmWrite(PWMA, 50);
  digitalWrite(BIN1, HIGH);  
  digitalWrite(BIN2, LOW); 
  softPwmWrite(PWMB, 50);

  delay(time * 100);
}

void spin_right(int time)
{
  digitalWrite(AIN1, HIGH);   
  digitalWrite(AIN2, LOW);  
  softPwmWrite(PWMA, 50);                          
  digitalWrite(BIN1, LOW);   
  digitalWrite(BIN2, HIGH);
  softPwmWrite(PWMB, 50);   

  delay(time * 100);
}

void back(int time)
{
  digitalWrite(AIN1, LOW);    
  digitalWrite(AIN2, HIGH); 
  softPwmWrite(PWMA, 50);
  digitalWrite(BIN1, LOW);   
  digitalWrite(BIN2, HIGH);
  softPwmWrite(PWMB, 50);

  delay(time * 100);
}

void key_scan()
{
  while (digitalRead(key));       //当按键没有被按下一直循环
  while (!digitalRead(key))       //当按键被按下时
  {
    delay(10);	                  //延时10ms
    if (digitalRead(key)  ==  LOW)//第二次判断按键是否被按下
    {
      delay(100);
      while (!digitalRead(key));  //判断按键是否被松开
    }
  }
}

void main()
{ 
  wiringPiSetup();
  
  //初始化电机驱动IO口为输出方式
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  
  //创建两个软件控制的PWM脚
  softPwmCreate(PWMA,0,100); 
  softPwmCreate(PWMB,0,100);

  //定义按键接口为输入接口
  pinMode(key, INPUT);

  //定义左右传感器为输入接口
  pinMode(FollowSensorLeft, INPUT);
  pinMode(FollowSensorRight, INPUT);

  //调用按键扫描函数
  key_scan(); 
  
  while(1)
  {
    //遇到跟随物,红外跟随模块的指示灯亮,端口电平为LOW
    //未遇到跟随物,红外跟随模块的指示灯灭,端口电平为HIGH
    LeftSensorValue  = digitalRead(FollowSensorLeft);
    RightSensorValue = digitalRead(FollowSensorRight);

    if (LeftSensorValue == LOW && RightSensorValue == LOW)
    {
      run();        //当两侧均检测到跟随物时调用前进函数
    }
    else if (LeftSensorValue == LOW && RightSensorValue == HIGH)
    {
      spin_left(2); //左边探测到有跟随物，有信号返回，原地向左转
    }
    else if (RightSensorValue == LOW && LeftSensorValue == HIGH)
    {
      spin_right(2);//右边探测到有跟随物，有信号返回，原地向右转
    }
    else if (LeftSensorValue == HIGH && RightSensorValue == HIGH)
    {
      brake();     //当两侧均未检测到跟随物时停止
    }
  }
  return;
}
