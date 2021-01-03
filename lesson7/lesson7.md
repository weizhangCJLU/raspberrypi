# 舵机旋转控制七彩探照灯

## 课程内容

舵机旋转控制七彩探照灯

## 本课重点

pinMode

digitalWrite

delayMicroseconds

## 背景知识

1. 舵机的控制：

一般需要一个20ms左右的时基脉冲，该脉冲的高电平部分一般为0.5ms-2.5ms范围内的角度控制脉冲部分。

本次实验的采用的舵机是180度伺服，控制关系如下：

             0.5ms-----------------0度
             1.0ms-----------------45度
             1.5ms-----------------90度
             2.0ms-----------------135度
             2.5ms-----------------180度

2. 舵机控制函数

myangle取值范围0~180

```
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
```

## 舵机旋转控制七彩探照灯

程序模板：

```
#include <wiringPi.h>
#include <softPwm.h>

#define ON  1
#define OFF 0

int LED_R = 3;
int LED_G = 2;
int LED_B = 5;
int ServoPin = 4;

int main()
{
  wiringPiSetup();
  
  //write code here
  
  while(1)
  {
    //write code here
  }

  return 0;
}
```

编译程序： 

```
gcc ServoControlCorlor.c -o ServoControlCorlor -lwiringPi -lpthread
```

运行程序：

```
./ServoControlCorlor
```

需要停止时我们通过ctrl+c，表示向linux内核发送一个终止当前进程的信号。
