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

    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    softPwmCreate(PWMA,0,100);
    softPwmCreate(PWMB,0,100);

    delay(2000);

    while(1)
    {
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        softPwmWrite(PWMA, 30);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
        softPwmWrite(PWMB, 30);
        delay(2000);
    }

    return 0;
}
