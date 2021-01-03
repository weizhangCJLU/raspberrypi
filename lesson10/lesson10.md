# 寻光行走实验

## 课程内容

寻光行走实验

## 本课重点

pinMode

digitalWrite

digitalRead

软件 PWM 库

softPwmCreate 函数

softPwmWrite 函数

## 背景知识

1. 光敏电阻器

光敏电阻器是利用半导体的光电导效应制成的一种电阻值随入射光的强弱而改变的电阻器，又称为光电导探测器；入射光强，电阻减小，入射光弱，电阻增大。我们通过光敏电阻连接到主控板上的引脚的电平变化来决定是否有光。

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

## 寻光行走实验

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
const int LdrSensorLeft =  11;  
const int LdrSensorRight = 22;  
int LdrSersorLeftValue ;        
int LdrSersorRightValue ;

void main()
{
  //wiringPi初始化
  wiringPiSetup();
	
  //初始化电机驱动IO口为输出方式
  
  
  //创建两个软件控制的PWM脚
  

  //定义按键接口为输入接口
  
  
  //定义左右光敏电阻传感器为输入接口
  
 
  //调用按键扫描函数
  key_scan();
  
  while(1)
  {
  //遇到光线,寻光模块的指示灯灭,端口电平为HIGH
  //未遇光线,寻光模块的指示灯亮,端口电平为LOW
  LdrSersorRightValue = digitalRead(LdrSensorRight);
  LdrSersorLeftValue  = digitalRead(LdrSensorLeft);

  //两侧均有光时信号为HIGH，光敏电阻指示灯灭,小车前进

  //左边探测到有光，有信号返回，向左转

  //右边探测到有光，有信号返回，向右转

  //均无光，停止

  }
  return;
}
```

编译程序： 

```
gcc light_follow.c -o light_follow -lwiringPi -lpthread
```

运行程序：

```
./light_follow
```

需要停止时我们通过ctrl+c，表示向linux内核发送一个终止当前进程的信号。
