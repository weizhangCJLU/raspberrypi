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
  //wiringPi初始化
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
  
  //定义左右光敏电阻传感器为输入接口
  pinMode(LdrSensorLeft, INPUT);
  pinMode(LdrSensorRight, INPUT);
 
  //调用按键扫描函数
  key_scan();
  
  while(1)
  {
  //遇到光线,寻光模块的指示灯灭,端口电平为HIGH
  //未遇光线,寻光模块的指示灯亮,端口电平为LOW
  LdrSersorRightValue = digitalRead(LdrSensorRight);
  LdrSersorLeftValue  = digitalRead(LdrSensorLeft);

  if (LdrSersorLeftValue == HIGH && LdrSersorRightValue == HIGH)
  {
    run();   //两侧均有光时信号为HIGH，光敏电阻指示灯灭,小车前进                                   
  }
  else if (LdrSersorLeftValue == HIGH && LdrSersorRightValue == LOW)       
  {
    left(); //左边探测到有光，有信号返回，向左转
  }
  else if (LdrSersorRightValue == HIGH && LdrSersorLeftValue == LOW)       
  {
    right();//右边探测到有光，有信号返回，向右转
  }
  else if (LdrSersorLeftValue == LOW && LdrSersorRightValue == LOW)        
  {
    brake();//均无光，停止
  }
  }
  return;
}
