/* CODE EDITED AND FINALIZED BY : D.SUKESH*/
   

#include<SoftwareSerial.h>

int LCW  = 2;
int LCCW = 3;
int RCW  = 4;
int RCCW = 5;
int encoderpower = 23;
int countL=0;
int countR=0;
const int rx = 11;
const int tx = 10;
int flag=1;
SoftwareSerial bluetooth(rx,tx);


void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  attachInterrupt(digitalPinToInterrupt(18),isrL,HIGH);
  attachInterrupt(digitalPinToInterrupt(19),isrR,HIGH);

  pinMode(LCW,OUTPUT);
  pinMode(LCCW,OUTPUT);
  pinMode(RCW,OUTPUT);
  pinMode(RCCW,OUTPUT);
  pinMode(encoderpower,OUTPUT);
  digitalWrite(encoderpower,HIGH);
  analogWrite(8,90);
  analogWrite(9,96);

}
 
 int angle=45,motor=2,distance=50,i,prevAngle=0;
 String angleTemp,motorTemp,distanceTemp;

void loop()
{ 

    while(bluetooth.available())
    {
      delay(10);  //REST FOR ARDUINO LOL

      //RECEIVING MOTOR NUMBER
      motorTemp = bluetooth.readString();
      Serial.print("Received MotorNumber is = ");
      Serial.println(motorTemp);
      bluetooth.write("2");  ///MOTOR NUMEBER RECEIVED

          motor = motorTemp[0]-'0';


      //RECEVING DISTANCE
      distanceTemp = bluetooth.readString();
      Serial.print("Received Distance is = ");
      Serial.println(distanceTemp);
      bluetooth.write("3");  ///DISTANCE RECEIVED
           for(i=0;i<4;i++)
              {
                if(i==0)
                   distance =  ( distanceTemp[i] - '0' );
                if(i==1)
                   distance += ( distanceTemp[i] - '0' )*10;
                if(i==2)
                   distance += ( distanceTemp[i] - '0' )*100;
                if(i==3)
                   distance += ( distanceTemp[i] - '0' )*1000;
              }
      
      //RECEIVING ANGLE
      angleTemp = bluetooth.readString();
      Serial.print("Received angle is = ");
      Serial.println(angleTemp);

      bluetooth.write("1");  ///ANGLE RECEIVED ACKNOWLEDGEMENT
            for(i=0;i<3;i++)
              {
                if(i==0)
                   angle = ( angleTemp[i] - '0' );
                if(i==1)
                   angle += ( angleTemp[i] - '0' )*10;
                if(i==2)
                   angle += ( angleTemp[i] - '0' )*100;
              }
      
    }*/
    control();
//    delay(1000);
}


void control()
{
  //ANGLE ROTATION AND MOTOR SELECTION
  if(motor == 1)
  {
    while(countL<(abs(angle-prevAngle)))
     {
        Serial.println("LEFT MOTOR");
        digitalWrite(LCW,HIGH);
        digitalWrite(LCCW,LOW);
        digitalWrite(RCW,LOW);
        digitalWrite(RCCW,LOW);
      //  Serial.print(countL);
     }
     countL=0;

     if(angle!=0)
      digitalWrite(LCW,LOW);
      delay(500);
  }
  else if(motor == 2)
  {
    while(countR<abs(angle-prevAngle))
     {
        Serial.println("RIGHT MOTOR");
        Serial.print(countR);
        digitalWrite(LCW,LOW);
        digitalWrite(LCCW,LOW);
        digitalWrite(RCW,HIGH);
        digitalWrite(RCCW,LOW);
     }
     countR=0;
     //ROTATION DONE TURN OFF MOTOR
      digitalWrite(RCW,LOW);
      delay(500);
      
  }
  if(flag==1)
  {
        countL=0;
  //DISTANCE CALCULATION AND TRAVERSING
    while(countL<=distance)
     {
    //  Serial.print("LEFT");
     // Serial.println(countL);
       //     Serial.print("RIGHT");
     // Serial.println(countL);
      digitalWrite(LCW,HIGH);
      digitalWrite(LCCW,LOW);
      digitalWrite(RCW,HIGH);
      digitalWrite(RCCW,LOW);
     }
     countL=0;
     countR=0;
      //DISTANCE DONE TURN OFF BOTH MOTORS
     digitalWrite(LCW,LOW);
     digitalWrite(LCCW,LOW);
     digitalWrite(RCW,LOW);
     digitalWrite(RCCW,LOW);
     flag=2;
     prevAngle = angle;
  }
}

void isrL()
{
  countL++;
}
void isrR()
{
  countR++;
}
