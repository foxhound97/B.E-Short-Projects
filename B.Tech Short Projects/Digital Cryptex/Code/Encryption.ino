 #include <SoftwareSerial.h>
 #include<EEPROM.h>
  SoftwareSerial mySerial(9, 10); 
String encrypted_msg="";
String public_key="";

int i,x,y,t=5;
String n,pkey,skey;
char w[15];
void setup() {
Serial.begin(9600);
mySerial.begin(9600);

 for(int i=0;i<=5;i++)
  {
    w[i]=EEPROM.read(i);
    public_key+=String(w[i]);
delay(100);
}

Serial.println("write public key");

 for(;;)   // get a secret key from receiver 
    {
        if(Serial.available()>0)
        {
        w[i] =Serial.read();
        
        if(w[i]==10)
       {
        break; 
       }
        pkey+=String(w[i]);
        }
    }
    Serial.print("\n");
x=public_key.length();
y=x;

for(int i=0;i<x;i++)
{
  if(public_key[i]==pkey[i])
  {
    y--;
    if(i==x-1)
    {
    if(y==0)
   {
    Serial.println("Public key is write");
    break;
   }
  }}
    }
if(y==0)
{
    Serial.println("write Sending msg");

    for(;;)
    {
        if(Serial.available()>0)
        {
        w[i] =Serial.read();
        
        if(w[i]==10)
       {
        break; 
       }
        n+=String(w[i]);
        }
    }
    
int i,j,s,f=0,x,g,a,b,c[30],m[100],k[4][8];
  k[0][0]=0;  k[0][1]=1;   k[0][2]=3;  k[0][3]=2;      k[0][4]=16; k[0][5]=17; k[0][6]=19;  k[0][7]=18;
  k[1][0]=4;  k[1][1]=5;   k[1][2]=7;  k[1][3]=6;      k[1][4]=20; k[1][5]=21;  k[1][6]=23;  k[1][7]=22;
  k[2][0]=12; k[2][1]=13;  k[2][2]=15; k[2][3]=14;     k[2][4]=28; k[2][5]=29;  k[2][6]=31;  k[2][7]=30;
  k[3][0]=8;  k[3][1]=9;   k[3][2]=11; k[3][3]=10;     k[3][4]=24; k[3][5]=25;  k[3][6]=27;  k[3][7]=26;


x=n.length();
n.replace(" ","");
  Serial.print("Orignal msg is :");
  Serial.print(n);
  Serial.print("\n");



  
  
for(i=0;i<x;i++)
  {
  a=n[i];
  b=a-32;
  
  if(a>=97 && a<=122)
  c[i]=b-64;
  
  else if(a>=65 && a<=90)
  c[i]=a-64;
   

   
 }
 for(i=0;i<x;i++)
 {
  for(j=0;j<=3;j++)
  {
   for(g=0;g<=7;g++)
   {
    if(c[i]==k[j][g])
     {
     k[j][g]=1;
   }
   }
   }
   }

  for(i=0;i<=3;i++)
   {
   for(j=0;j<=7;j++)
   {
   if(k[i][j]!=1)
   {
    k[i][j]=0;
   }



   }
  }

/*for(i=0;i<4;i++) // do comment
{
  for(j=0;j<8;j++)
  {
    Serial.print(k[i][j]);
    Serial.print("\t");
  }
}*/

for(i=0;i<4;i++)
{
  for(j=0;j<8;j++)
  {
    if(j==0 || j==4)
    {
      k[i][j]*=8;
    }
    
    else if(j==1 || j==5)
    {
      k[i][j]*=4;
    }
    
    else if(j==2 || j==6)
    {
      k[i][j]*=2;
    }
    
    else if(j==3 || j==7)
    {
      k[i][j]*=1;
    }
  }
}
int p[4][2],t;
for(i=0;i<4;i++)
{
  t=0;
  p[i][t]=0;
  for(j=0;j<4;j++)
  {
    p[i][t]+=k[i][j];
  }
  t=1;
  p[i][t]=0;
  for(j=4;j<8;j++)
  {
    p[i][t]+=k[i][j];
  }
}

for(i=0;i<4;i++)
{
  for(j=0;j<2;j++)
  {
  encrypted_msg+=String(p[i][j],HEX);

}}
  Serial.print("\n");
Serial.print("encrypted_msg : ");
Serial.print(encrypted_msg);
 Serial.print("\n");
  Serial.print("\n");
Serial.println("Press s for sending a msg");
  }
 else
 {
 t=0;  
   Serial.println("Public key is wrong you can not send msg");
 }
}
void loop()
{
  if (Serial.available()>0 && t==5)
  {
   switch(Serial.read())
  {
    case 's':
   SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
  }
  }
 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
     Serial.println("******");
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918264860070\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(encrypted_msg);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
 }
 



