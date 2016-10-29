import serial
ser = serial.Serial('/dev/cu.usbmodem14231', 9600)
while True:
    print ser.readline()

