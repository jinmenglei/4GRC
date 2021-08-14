import serial
import time
import threading


serial_your = serial.Serial("COM3", 115200, timeout=5)


def serial_send():
    while True:
        time.sleep(0.02)
        if serial_your.isOpen():
            serial_your.write(bytes([0xAA, 0xBB, 0xCC, 0xDD]))
            pass
        else:
            time.sleep(5)
            print("serial not open please check")


task_send = threading.Thread(target=serial_send, args=())
