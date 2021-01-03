# 红外跟随实验

## 课程内容

红外跟随实验

## 本课重点

pinMode

digitalWrite

digitalRead

软件 PWM 库

softPwmCreate 函数

softPwmWrite 函数

## 背景知识

1. 红外传感器

红外传感器具有一对红外发射与接收管，发射管发射出一定频率的红外线，当检测方向遇到障碍物时，发射出去的红外线反射回来被接收管接收。它常用于安装在小车上，判断前方是否有障碍物。可通过红外传感器模块上的电位器设置红外避障的距离。

2. 按键扫描函数

```
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
```

3. 小车控制函数

```
void run()
{
  digitalWrite(AIN1, HIGH);  
  digitalWrite(AIN2, LOW); 
  softPwmWrite(PWMA, 50);
  digitalWrite(BIN1, HIGH); 
  digitalWrite(BIN2, LOW);
  softPwmWrite(PWMB, 50);
}

void brake(int time)
{
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  delay(time * 100);
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
  softPwmWrite(PWMA,50);
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
```

## 红外跟随实验

程序模板：

```
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

void main()
{ 
  wiringPiSetup();
  
  //初始化电机驱动IO口为输出方式
  
  
  //创建两个软件控制的PWM脚
  

  //定义按键接口为输入接口
  

  //定义左右传感器为输入接口
  

  //调用按键扫描函数
  key_scan(); 
  
  while(1)
  {
    //遇到跟随物,红外跟随模块的指示灯亮,端口电平为LOW
    //未遇到跟随物,红外跟随模块的指示灯灭,端口电平为HIGH
    LeftSensorValue  = digitalRead(FollowSensorLeft);
    RightSensorValue = digitalRead(FollowSensorRight);

    //当两侧均检测到跟随物时调用前进函数


    //左边探测到有跟随物，有信号返回，原地向左转


    //右边探测到有跟随物，有信号返回，原地向右转


    //当两侧均未检测到跟随物时停止

    
  }
  return;
}
```

编译程序： 

```
gcc infrared_follow.c -o infrared_follow -lwiringPi -lpthread
```

运行程序：

```
./infrared_follow
```

需要停止时我们通过ctrl+c，表示向linux内核发送一个终止当前进程的信号。
