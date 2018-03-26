import traceback
import time
import struct 
import math

import serial
import pyautogui

scr = (1440, 900) 
port = "/dev/cu.wchusbserial1420"
ser = serial.Serial(port)
pyautogui.FAILSAFE = False
pyautogui.moveTo(scr[0]/2, scr[1]/2)

# read once to discard so we don't start in the middle of a line
ser.readline()

# value to be adjusted based on pyautogui's mouse movement latency
S_PER_UPDATE = 0.3
prev = time.time()
lag = 0.0
rclick = 0
lclick = 0
while True:
    x_inc = 0
    y_inc = 0
    cur = time.time()
    elapsed = cur - prev
    prev = cur
    lag += elapsed

    val = ser.readline()
    if len(val) == 7:
        rv, lv, roll, pitch, _ = struct.unpack("bbhhb", val)

        rclick |= rv
        lclick |= lv

        # Threshold to ignore sensor jitter
        roll = roll if abs(roll) > 1000 else 0
        pitch = pitch if abs(pitch) > 1000 else 0

        x_inc += -(scr[0] / 2) * (roll / 65535.0)
        y_inc += -(scr[1] / 2) * (pitch / 65535.0)
        
    if lag >= S_PER_UPDATE:
        #: Our biggest bottleneck. Blocks but also can't be threaded because 
        #: there's only a single mouse.
        pyautogui.moveRel(x_inc, y_inc)
        if rclick:
#            pyautogui.typewrite(["left"])
            pyautogui.click(button="right")
            rclick = 0
        if lclick:
#            pyautogui.typewrite(["right"])
            pyautogui.click()
            lclick = 0

        rclick = 0
        lclick = 0
        lag = 0

