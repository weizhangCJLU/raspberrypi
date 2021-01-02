#include <wiringPi.h>

#define ON 1 //打开LED
#define OFF 0 //关闭LED

//RGB引脚定义
int LED_R = 3;
int LED_G = 2;
int LED_B = 5;

void color_led(int v_iRed, int v_iGreen, int v_iBlue)
{
	v_iRed == ON ? digitalWrite(LED_R, HIGH): digitalWrite(LED_R, LOW);
	v_iGreen == ON ? digitalWrite(LED_G, HIGH) : digitalWrite(LED_G, LOW);
	v_iBlue == ON ? digitalWrite(LED_B, HIGH) : digitalWrite(LED_B, LOW);
}

int main()
{
    wiringPiSetup();

    //设置引脚模式
	pinMode(LED_R, OUTPUT);
	pinMode(LED_G, OUTPUT);
	pinMode(LED_B, OUTPUT);

    while(1)
    {
        //七彩灯控制
		color_led(ON, OFF, OFF);
		delay(1000);
		color_led(OFF, ON, OFF);
		delay(1000);
		color_led(OFF, OFF, ON);
		delay(1000);
		color_led(ON, ON, OFF);
		delay(1000);
		color_led(ON, OFF, ON);
		delay(1000);
		color_led(OFF, ON, ON);
		delay(1000);
		color_led(ON, ON, ON);
    }

    return 0;
}
