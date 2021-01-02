# 小车控制实验

## 课程内容

控制小车前进/后退/左转/右转

## 本课重点

软件 PWM 库

softPwmCreate 函数

softPwmWrite 函数

## 背景知识

1. 软件 PWM 库

wiringPi 中包含了一个软件驱动的 PWM 处理库，可以在任意的树莓派 GPIO 上输出
PWM 信号。

2. softPwmCreate 函数

该函数的原型为：int softPwmCreate(int pin, int initialValue, int pwmRange);

pin： GPIO 管脚。

initialValue：PWM初始值，设为0。

pwmRange： PWM最大转速，设为100。

3. softPwmWrite 函数

该函数的原型为：void softPwmWrite(int pin, int value);

pin： GPIO 管脚。

value： PWM转速，范围是0~100。值越大，转速越快。

## 小车控制方法

PWMA越大，左边两个轮子转速越快。

PWMB越大，右边两个轮子转速越快。

AIN1 AIN2 BIN1 BIN2 PWMA PWMB 小车

1    0    1    0    30   30   前进

0    1    0    1    30   30   后退

1    0    1    0    20   70   右转

1    0    1    0    70   20   左转

## 控制小车前进

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
gcc car.c -o car -lwiringPi -lpthread
```

运行程序：

```
./car
```

需要停止时我们通过ctrl+c，表示向linux内核发送一个终止当前进程的信号。
