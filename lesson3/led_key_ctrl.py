import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setup(21,GPIO.OUT)
GPIO.setup(17,GPIO.IN,pull_up_down=GPIO.PUD_DOWN)

while True:
    if(GPIO.input(17)==GPIO.HIGH):
        GPIO.output(21, GPIO.HIGH)
    else:
        GPIO.output(21, GPIO.LOW)
    time.sleep(.01)
