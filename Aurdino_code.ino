/*
   author : D SUKESH
*/

#include<SoftwareSerial.h>

 //MPU
 #include<Wire.h>
 #include<MPU6050.h>
 const int MPU6050_addr=0x68; 
 int16_t AccX,AccY,AccZ,Temp,GyroX,GyroY,GyroZ;
 float dps;
 long long unsigned int loop_timer;

 //MOTORS
int L1_CW  = 53;
int L1_CCW = 52;
int R1_CW  = 4;
int R1_CCW = 5;
int L2_CW  = 51;
int L2_CCW = 50;
int R2_CW  = 6;
int R2_CCW = 7;
int j,k;
int timedistance=0;


const int rx = 11;
const int tx = 10;
int tempf;
float anglempu=0;
SoftwareSerial bluetooth(rx,tx);


void setup() {
  Serial.begin(19200);
  bluetooth.begin(9600);
  //MOTORS
  pinMode(L1_CW,OUTPUT);
  pinMode(L1_CCW,OUTPUT);
  pinMode(R1_CW,OUTPUT);
  pinMode(R1_CCW,OUTPUT);
  pinMode(L2_CW,OUTPUT);
  pinMode(L2_CCW,OUTPUT);
  pinMode(R2_CW,OUTPUT);
  pinMode(R2_CCW,OUTPUT);
  //PWM FOR MOTOR DRIVER
  analogWrite(8,255);//right
  analogWrite(9,255);//right
  analogWrite(12,255);//left
  analogWrite(13,255);//left
  //MPU
  Wire.begin();
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  

  Wire.beginTransmission(MPU6050_addr);                                       
  Wire.write(0x1B);                                                   
  Wire.write(0x08);                                                   
  Wire.endTransmission(true); 

  MPU6050 accelgyro(MPU6050_addr);
  accelgyro.setZGyroOffset(-62); 

}
 
 int angle,motor,distance,i,prevangle=0,angleLength,distanceLength,angleRotate;
 String angleTemp,motorTemp,distanceTemp;

void loop()
{ 
    while(bluetooth.available()==0);
      Serial.println("abhcd");
      //RECEIVING MOTOR NUMBER
      motorTemp = bluetooth.readString();
      Serial.print("Received MotorNumber is = ");
      Serial.println(motorTemp);
      
      motor = motorTemp[0]-'0';

      bluetooth.write("2");  ///MOTOR NUMEBER RECEIVED

      //RECEVING DISTANCE
      while(bluetooth.available()==0);
      distanceTemp = bluetooth.readString();
      
      Serial.print("Received Distance is = ");
      Serial.println(distanceTemp);
      distanceLength = distanceTemp.length();
      Serial.println(distanceLength);
     

        if(distanceLength == 2)
            {
           for(i=0;i<2;i++)
              {
                if(i==0)
                   distance =  ( distanceTemp[i] - '0' )*10;
                if(i==1)
                  distance += ( distanceTemp[i] - '0' );
              }
              Serial.println(distance);
            }
         else if(distanceLength == 3)
         {
           for(i=0;i<3;i++)
              {
                if(i==0)
                   distance =  ( distanceTemp[i] - '0' )*100;
                if(i==1)
                  distance += ( distanceTemp[i] - '0' )*10;
                if(i==2)
                  distance += ( distanceTemp[i] - '0' );
              }
              Serial.println(distance);
         }    
         else if(distanceLength == 4)
         {
           for(i=0;i<4;i++)
              {
                if(i==0)
                   distance =  ( distanceTemp[i] - '0' )*1000;
                if(i==1)
                  distance += ( distanceTemp[i] - '0' )*100;
                if(i==2)
                  distance += ( distanceTemp[i] - '0' )*10;
                if(i==3)
                  distance += ( distanceTemp[i] - '0' );
              }
              Serial.println(distance);
         }
      bluetooth.write("3");  ///DISTANCE RECEIVED
      
      //RECEIVING ANGLE      
      while(bluetooth.available()==0);
      angleTemp = bluetooth.readString();
      Serial.print("Received angle is = ");
      Serial.println(angleTemp);
      angleLength = angleTemp.length();
      Serial.println(angleLength);
         if(angleLength == 1)
          {
            for(i=0;i<1;i++)
              {
                if(i==0)
                   angle = ( angleTemp[i] - '0' );
              }
                    Serial.println(angle);
          }
          if(angleLength == 2)
          {
            for(i=0;i<2;i++)
              {
                if(i==0)
                   angle = ( angleTemp[i] - '0' )*10;
                if(i==1)
                   angle += ( angleTemp[i] - '0' );
              }
                    Serial.println(angle);
          }

         else if(angleLength == 3)
          {
             for(i=0;i<2;i++)
             {
               if(i==0)
                   angle = ( angleTemp[i] - '0' )*100;
                if(i==1)
                   angle += ( angleTemp[i] - '0' )*10;
                if(i==2)
                   angle += ( angleTemp[i] - '0' );
             }
                    Serial.println(angle);
          }
          
      bluetooth.write("1");  ///ANGLE RECEIVED ACKNOWLEDGEMENT
      
      control();
      bluetooth.write(" ");
      Serial.println(F("EXECUTED !!"));
    
     
    }

void mpuangle()
{ 
  loop_timer = millis();
  
  Wire.beginTransmission(MPU6050_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_addr,14,true);  // REQUESTING 14 BYTES FROM DEVICE ADDRESSED AS MPU6050_addr
  AccX=Wire.read()<<8|Wire.read();         // Wire.read() READS ONE BYTE WHERE AS DATA IS OF 2 BYTE SO, READ THE FIRST BYTE , <<8 , OR IT WITH NEXT BYTE TO MAKE 16 BIT(2 BYTE) DATA
  AccY=Wire.read()<<8|Wire.read();
  AccZ=Wire.read()<<8|Wire.read();
  Temp=Wire.read()<<8|Wire.read();
  GyroX=Wire.read()<<8|Wire.read();
  GyroY=Wire.read()<<8|Wire.read();
  GyroZ=Wire.read()<<8|Wire.read();
  dps = GyroZ/65.5;
  anglempu += dps*0.004;
//  anglempu = anglempu*3;

   Serial.println(anglempu); 
  while((millis()-loop_timer)<4);
}

void control()
{
 k= anglempu*2.66;
  //ANGLE ROTATION AND MOTOR SELECTION
  angleRotate = abs(angle-prevangle);
    if(angleRotate >=180)
   { angleRotate = abs(360-angleRotate);}

  if(motor == 1)
  {
    
    while( abs(k) < angleRotate)
     {
        Serial.println("LEFT MOTOR");
        digitalWrite(L1_CCW,LOW);
        digitalWrite(L1_CW,HIGH);
        digitalWrite(L2_CCW,LOW);
        digitalWrite(L2_CW,HIGH);
        digitalWrite(R1_CW,LOW);
        digitalWrite(R1_CCW,HIGH);
        digitalWrite(R2_CW,LOW);
        digitalWrite(R2_CCW,HIGH);
        mpuangle();
        k= anglempu*2.66;
     }
        prevangle = angle;
        anglempu = 0;
        digitalWrite(L1_CCW,LOW);
        digitalWrite(L1_CW,LOW);
        digitalWrite(L2_CCW,LOW);
        digitalWrite(L2_CW,LOW);
        digitalWrite(R1_CW,LOW);
        digitalWrite(R1_CCW,LOW);
        digitalWrite(R2_CW,LOW);
        digitalWrite(R2_CCW,LOW) ;
      //delay(500);
  }
 else if(motor == 2)
  {
    
    while(abs(k) < angleRotate)
      {
         mpuangle();
        Serial.println("RIGHT MOTOR");
         digitalWrite(L1_CW,LOW);
         digitalWrite(L1_CCW,HIGH);
         digitalWrite(L2_CW,LOW);
         digitalWrite(L2_CCW,HIGH);
         digitalWrite(R1_CCW,LOW);
         digitalWrite(R1_CW,HIGH);
         digitalWrite(R2_CCW,LOW);
         digitalWrite(R2_CW,HIGH);
           k= anglempu*2.66;
     }
  
     //ROTATION DONE TURN OFF MOTOR
        prevangle = angle;
        anglempu = 0;
        digitalWrite(L1_CCW,LOW);
        digitalWrite(L1_CW,LOW);
        digitalWrite(L2_CCW,LOW);
        digitalWrite(L2_CW,LOW);
        digitalWrite(R1_CW,LOW);
        digitalWrite(R1_CCW,LOW);
        digitalWrite(R2_CW,LOW);
        digitalWrite(R2_CCW,LOW) ;
  
      
  }
 
 
       
   //DISTANCE CALCULATION AND TRAVERSING
   //ADJUSTING DIFFERENT PWM FOR TRAVERSING
   

      Serial.print("FORWARD");
  digitalWrite(L1_CW,HIGH);
  digitalWrite(L1_CCW,LOW);
  digitalWrite(L2_CW,HIGH);
  digitalWrite(L2_CCW,LOW);
  digitalWrite(R1_CW,HIGH);
  digitalWrite(R1_CCW,LOW);
  digitalWrite(R2_CW,HIGH);
  digitalWrite(R2_CCW,LOW);
  timedistance = distance/10;
  for(j=0;j<timedistance;j++){
     delay(1000);}
     
     Serial.println("DONE");
   
      //DISTANCE DONE TURN OFF BOTH MOTORS

  digitalWrite(L1_CCW,LOW);
  digitalWrite(L1_CW,LOW);
  digitalWrite(L2_CCW,LOW);
  digitalWrite(L2_CW,LOW);
  digitalWrite(R1_CW,LOW);
  digitalWrite(R1_CCW,LOW);
  digitalWrite(R2_CW,LOW);
  digitalWrite(R2_CCW,LOW) ;

}
