# 亚博智能小车学习 第一课 七彩灯控制

**从这节课开始以```深圳亚博智能小车（树莓派版）```作为学习套件，以C语言为主要教学语言。**

## 课程内容

RGB三色灯控制：

所谓的RGB三色灯和普通的LED灯其实没有什么不同，只是在封装上，RGB灯内封装了三个LED（红，绿，蓝）。

## 本课重点

wiringPi库

pinMode 函数

digitalWrite 函数

delay 函数

C语言条件运算符

C语言int整数类型

C语言宏定义

## 背景知识

1. wiringPi库

wiringPi库是由Gordon Henderson所编写并维护的一个用C语言写成的类库。起初，
主要是作为 BCM2835 芯片的 GPIO 库。而现在，已经非常丰富，除了 GPIO 库，还包括了
I2C 库、SPI 库、UART 库和软件 PWM 库等。
由于其与 Arduino 的“wiring”系统较为类似，故以此命名。它是采用 GNU LGPLv3
许可证的，可以在 C 或 C++上使用，而且在其他编程语言上也有对应的扩展。
wiringPi 库包含了一个命令行工具 gpio，它可以用来设置 GPIO 管脚，可以用来读写
GPIO 管脚，甚至可以在 Shell 脚本中使用来达到控制 GPIO 管脚的目的。

2. pinMode 函数

该函数的原型为：void pinMode(int pin, int mode);

使用该函数可以将某个管脚设置为 INPUT（输入）、OUTPUT（输出）、PWM_OUTPUT
（脉冲输出）或者 GPIO_CLOCK（GPIO 时钟）。

需要注意的是仅有管脚 1（BCM_GPIO 18）支持 PWM_OUTPUT 模式，仅有管脚 7
（BCM_GPIO 4）支持 CLOCK 输出模式。

3. digitalWrite 函数

该函数的原型为：void digitalWrite(int pin, int value);

使用该函数可以向指定的管脚写入 HIGH（高）或者 LOW（低），写入前，需要将管脚
设置为输出模式。

4. delay 函数

该函数的原型为：void delay(unsigned int howLong);

该函数将会中断程序执行至少 howLong 毫秒。因为 Linux 是多任务的原因，中断时间
可能会更长。需要注意的是，最长的延迟值是一个无符号 32 位整数，其大约为 49 天。

5. C语言条件运算符

条件运算符（conditional operator）有时候也称为三元运算符（ternary operator，或者trinary operator），因为它是唯一需要 3 个操作数的运算符：

表达式为：表达式1？表达式2：表达式3

先求解表达式1，

若其值为真（非0）则将表达式2的值作为整个表达式的取值，

否则（表达式1的值为0）将表达式3的值作为整个表达式的取值。

例如:

1、max=(a>b)?a:b

就是将a和b二者中较大的一个赋给max。

2、min=(a<b)?a:b

就是将a和b二者中较小的一个赋给min。

6. C语言int整数类型

C语言提供了很多整数类型，简称整型，这些整型的区别在于它们取值范围的大小以及是否可以取负。

int是整型之一。

unsigned int是无符号整型。

7. C语言宏定义

#define 叫做宏定义命令，它也是C语言预处理命令的一种。所谓宏定义，就是用一个标识符来表示一个字符串，如果在后面的代码中出现了该标识符，那么就全部替换成指定的字符串。

## 课堂作业 七彩灯设计

```循环显示7种不同颜色的灯。```

程序模板：

```
#include <wiringPi.h>

#define ON 1 //打开LED
#define OFF 0 //关闭LED

//RGB引脚定义
int LED_R = 3;
int LED_G = 2;
int LED_B = 5;

int main()
{
    wiringPiSetup();

    //设置引脚模式

    while(1)
    {
        //七彩灯控制

    }

    return 0;
}
```

编译程序： 

```
gcc color_led.c -o color_led -lwiringPi
```

运行程序：

```
./color_led
```

需要停止时我们通过ctrl+c，表示向linux内核发送一个终止当前进程的信号。
