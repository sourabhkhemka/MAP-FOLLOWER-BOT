#include<SoftwareSerial.h>

int A = 7;
int B = 8;
int C = 9;
int D = 10;

const int rx = 13;
const int tx = 12;

SoftwareSerial bluetooth(rx,tx);

void setup() 
{
  Serial.begin(38400);
  bluetooth.begin(9600);
  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT);
}

void loop() 
{
  int i=0,x, dist=0,j,n=1;
  const 
  String a,d,m; 

  bluetooth.write(" "); 
  while(bluetooth.available() == 0)
  {
    ;
  }
  a = bluetooth.readString();
  Serial.print("a = ");
  Serial.println(a);
  
  if(a[0]==48||a[0]==50)
  {
    bluetooth.write("9");

    while(bluetooth.available()==0)
        {
          ;
        }
    d = bluetooth.readString();
        Serial.print("d is ::");
    Serial.println(d);
    i = 0;
    while(d[i]!='\0')
    {
      i++;
    }

    j = i;
    i = 0;
    j -= 3;
   
    dist = 0;
    while(j-->0)
     {
      n = n * 10;
     }
     

    while(d[i]!='.')
    {
      x = d[i++];
      dist += (x-48) * n;
      n /= 10;
    }

    Serial.print("dist = ");
    Serial.println(dist);

    //m = 0;
    //movecar();
  }

if(a[0]==49)
  {
    bluetooth.write("9");

    while(bluetooth.available()==0)
        {
          ;
        }
    d = bluetooth.readString();

    i = 0;
    while(d[i]!='\0')
    {
      i++;
    }

    j = i;
    i = 0;
    j -= 3;
   
    dist = 0;
    while(j-->0)
     {
      n = n * 10;
     }
     

    while(d[i]!='.')
    {
      x = d[i++];
      dist += (x-48) * n;
      n /= 10;
    }

    Serial.print("dist = ");
    Serial.println(dist);

    //m = 90;
    //movecar();
  }

 /* if(a==2)
  {
    bluetooth.write(9);

    while(bluetooth.available()==0)
    {
      ;
    }

    d = bluetooth.readString();
    Serial.println(d);

    while(bluetooth.available()==0)
    {
      ;
    }

    m = bluetooth.readString();
    Serial.println(m);

    movecar();
  }*/

}

void movecar()
{
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  digitalWrite(C,LOW);
  digitalWrite(D,LOW);
  //delay();
  
  digitalWrite(A,HIGH);
  digitalWrite(B,LOW);
  digitalWrite(C,HIGH);
  digitalWrite(D,LOW);

  //delay();

  digitalWrite(A,LOW);
  digitalWrite(C,LOW);

}
