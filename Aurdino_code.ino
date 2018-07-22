#include<SoftwareSerial.h>

int M = 2;
int N = 3;
int O = 4;
int P = 5;
int count=0;
const int rx = 11;
const int tx = 10;

SoftwareSerial bluetooth(rx,tx);

void setup() 
{
  Serial.begin(38400);
  bluetooth.begin(9600);
  attachInterrupt(digitalPinToInterrupt(18),isr,HIGH);
  pinMode(M,OUTPUT);
  pinMode(N,OUTPUT);
  pinMode(O,OUTPUT);
  pinMode(P,OUTPUT);
}

  int i=0,x, dist=0,j,n=1;
  String a,d,deg;
  float m=0;
void loop() 
{ 
  dist = 0; i = 0; n = 1;
  bluetooth.write(" "); 
  while(bluetooth.available() == 0)
  {
    ;
  }
  a = bluetooth.readString();
  
  Serial.print("a = ");
  Serial.println(a[0]);
  
  if(a[0]==48)
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
    j -= 1;
    n = 1;
    
    dist = 0;
    while(j-->0)
     {
      n = n * 10;
     }
     

    while(d[i]!='\0')
    {
      x = d[i++];
      dist += (x-48) * n;
      n /= 10;
    }

    Serial.print("dist = ");
    Serial.println(dist);

    m = 0;
    movecar();
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
    j -= 1;
   
    dist = 0;
    n=1;
    while(j-->0)
     {
      n = n * 10;
     }
     

    while(d[i]!='\0')
    {
      x = d[i++];
      dist += (x-48) * n;
      n /= 10;
    }

    Serial.print("dist = ");
    Serial.println(dist);

    m = 90;
    movecar();
  }

if(a[0]==50)
  {
//    Serial.println(F("+++"));
    bluetooth.write("8");

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
    j -= 1;
   
    dist = 0;
    n = 1;
    while(j-->0)
     {
      n = n * 10;
     }
     

    while(d[i]!='\0')
    {
      x = d[i++];
      dist += (x-48) * n;
      n /= 10;
    }

    Serial.print("dist = ");
    Serial.println(dist);
    bluetooth.write(" ");  
    while(bluetooth.available() == 0)
    {
      ;
    }
    deg = bluetooth.readString();
    i = 0;
    while(deg[i]!='\0')
    {
      i++;
    }
    j = i;
    i = 0;
    j -= 1;
    n = 1;
    m = 0;
    while(j-->0)
     {
      n = n * 10;
     }
    while(deg[i]!='\0')
    {
      x = deg[i++];
      m += (x-48) * n;
      n /= 10;
    }    
    Serial.print("m = ");
    Serial.println(m);  
    movecar();
  }
}







//********************///
void movecar()
{
  while(count<(0.8*m))
   {
    Serial.println("tttttttttttttttttttt");
    digitalWrite(M,HIGH);
    digitalWrite(N,LOW);
    digitalWrite(O,LOW);
    digitalWrite(P,LOW);
   }
  count=0;

  if(m!=0)
  digitalWrite(M,LOW);
  
  while(count<(dist/10))
  {
    Serial.println("ddddddddddddddddddddddddddddddddddd");
   digitalWrite(M,HIGH);
   digitalWrite(N,LOW);
   digitalWrite(O,HIGH);
   digitalWrite(P,LOW);
  }
  count=0;
  
  digitalWrite(M,LOW);
  digitalWrite(O,LOW);
}
//********************************//




void isr()
{
  count++;
}
