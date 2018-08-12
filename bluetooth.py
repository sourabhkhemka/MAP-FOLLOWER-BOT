import serial
#import time
#import math

port = "COM3"

#bluetooth = serial.Serial(port,9600);
print('CONNECTED');

count = 0

while(count<len(inst)):
     
    #SENDING MOTOR NUMBER
   #print('###')
   #bluetooth.read()
   print('+++')
   bluetooth.write(str(int(inst[count][0])))
   #print(int(str(inst[count][0])))
   #x = bluetooth.read()
   #print x
   if(bluetooth.read()=='2'):
       print('ACKNOWLEDGED :)')
   
    #SENDING DISTANCE IN PIXELS
    
   bluetooth.write(str((int(inst[count][1]))/10))  
   if(bluetooth.read()=='3'):
       print('ACKNOWLEDGED :)')
   
    #SENDING ANGLE IN DEGREES [0,360)
   
   bluetooth.write(str(int(inst[count][2])))
   if(bluetooth.read()=='1'):
       print('ACKNOWLEDGED :)')
    
    #COUNTER INCREMENTATION
   count += 1
   bluetooth.read()



