import argparse
import cv2
import RPi.GPIO as GPIO
import time
import serial
import picamera
import os

camera = picamera.PiCamera()
GPIO.setmode(GPIO.BCM)
GPI0_IR=18
GPIO.setup(GPI0_IR, GPIO.IN,pull_up_down=GPIO.PUD_DOWN)

ser = serial.Serial(
     port = '/dev/ttyACM0',
     baudrate = 9600,
     parity = serial.PARITY_NONE,
     stopbits = serial.STOPBITS_ONE,
     bytesize = serial.EIGHTBITS,
     timeout = 1
     )

while True:
    if GPIO.input(18)==0:
        
        camera.capture('/home/pi/anhmoi.jpg')
        print('da chup anh')
        path = '/home/pi/anhmoi.jpg'
        img= cv2.imread('/home/pi/anhmoi.jpg')
        original = img.copy()

        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        thresh = cv2.threshold(gray, 100, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)[1]
        thresh = ~thresh
        ROI_number = 0
        cnts = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
        cnts = cnts[0] if len(cnts) == 2 else cnts[1]
for cnt in cnts:
            approx = cv2.approxPolyDP(cnt,0.01*cv2.arcLength(cnt,True),True)
            print(len(approx))
            if len(approx)==3:
                print("Green = tamgiac")
                cv2.drawContours(img,[cnt],0,(0,255,0),-1)
                ser.write(3)
                ser.flush()
                time.sleep(3)
            elif len(approx)==4:
                print("Red = vuong")
                cv2.drawContours(img,[cnt],0,(0,0,255),-1)
                ser.write(2)
                ser.flush()
                print('da gui')
                time.sleep(3)
            elif len(approx) > 6:
                print("Yellow = tron")
                cv2.drawContours(img,[cnt],0,(0,255,255),-1)
                ser.write(1)
                ser.flush()
                print('da gui')
                time.sleep(3)

        cv2.imshow('image', img)
        cv2.imshow('Binary',thresh)
        cv2.waitKey(500)
