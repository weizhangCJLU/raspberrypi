import RPi.GPIO as GPIO            #导入树莓派提供的python模块
import time                                   #导入时间包，用于控制闪烁

GPIO.setmode(GPIO.BCM)        #设置GPIO模式，BCM模式在所有数码派通用
GPIO.setup(21, GPIO.OUT)       #设置GPIO21为电流输出

while True:
    GPIO.output(21, GPIO.HIGH)      #GPIO21 输出3.3V
    time.sleep(0.5)                          #程序控制流程睡眠0.5秒
    GPIO.output(21, GPIO.LOW)     #GPIO21 输出0V
    time.sleep(0.5)                         #程序控制流程睡眠0.5秒