import serial
import time
import math

port = "COM3"

bluetooth = serial.Serial(port,9600);
print('CONNECTED');

count = 0

while(count<len(inst)):
   bluetooth.write(str(inst[count][0]))
   print(inst[count][0])
   x = bluetooth.read()
   if(x == '9'):
       bluetooth.write(str(int(inst[count][1])))
       print(int(inst[count][1]))
   else:
       bluetooth.write(str(int(inst[count][1])))
       print(int(inst[count][1]))
       bluetooth.read()
       deg = int(90 - math.degrees(math.
                                   atan(inst[count][2])))
       bluetooth.write(str(deg))
       print(int(deg))
       
       

   count += 1
   bluetooth.read()
