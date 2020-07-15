#include<EEPROM.h>
int s2[32]={0,1,3,2,16,17,19,18,4,5,7,6,20,21,23,22,12,13,15,14,28,29,31,30,8,9,11,10,24,25,27,26};
int s3[32],i,j,o,x,m,n;
char s4[32],w[15];
String decrypt_msg,key,pkey,s5,encrypted_msg,s1;
String public_key="";
void setup() {
Serial.begin(9600);

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
n=x;

for(int i=0;i<x;i++)
{
  if(public_key[i]==pkey[i])
  {
    n--;
    if(i==x-1)
    {
    if(n==0)
   {
    Serial.println("Public key is write");
    break;
   }
  }}
    }
if(n==0)
{
  Serial.print("\n");
Serial.println("write private key");

 for(;;)   // get a secret key from receiver 
    {
        if(Serial.available()>0)
        {
        w[i] =Serial.read();
        
        if(w[i]==10)
       {
        break; 
       }
        key+=String(w[i]);
        }
    }

m=key.length();
Serial.print("private key is:");
Serial.print("\t");
Serial.println(key);
Serial.print("\n");
Serial.println("write received msg:");

    for(;;)   // get a  encrypted msg from receiver 
    {
        if(Serial.available()>0)
        {
        w[i] =Serial.read();
        
        if(w[i]==10)
       {
        break; 
       }
        encrypted_msg+=String(w[i]);
        }
    }
Serial.print("encrypted msg is: ");    
Serial.println(encrypted_msg);  
 for(i=0;i<encrypted_msg.length();i++)
    {
        switch(encrypted_msg[i])
        {
            case '0':
                s1+="0000";
                break;
            case '1':
                s1+="0001";
                break;
            case '2':
                s1+="0010";
                break;
            case '3':
                s1+="0011";
                break;
            case '4':
                s1+="0100";
                break;
            case '5':
                s1+="0101";
                break;
            case '6':
                s1+="0110";
                break;
            case '7':
                s1+="0111";
                break;
            case '8':
                s1+="1000";
                break;
            case '9':
                s1+="1001";
                break;
            case 'a':
            case 'A':
                s1+="1010";
                break;
            case 'b':
            case 'B':
                s1+="1011";
                break;
            case 'c':
            case 'C':
                s1+="1100";
                break;
            case 'd':
            case 'D':
                s1+="1101";
                break;
            case 'e':
            case 'E':
                s1+="1110";
                break;
            case 'f':
            case 'F':
                s1+="1111";
                break;
        }
}
//Serial.print(s1);
//Serial.print("\n");


for(i=0;i<32;i++)
{
 if(s1[i]=='0')
 {
   s3[i]=0;
 }
 else if(s1[i]='1')
 {
   s3[i]=s2[i]+64;
 }

}

 for(i=0;i<32;i++)
 {
  if(s3[i]!=0)
  {
    s4[i]=s3[i];
  }

  s5+=String(s4[i]);

 }
  o=s5.length();
  char t,u[m];
 for(i=0;i<o;i++)
{
for(j=i+1;j<o;j++)
{
if(s5[i]>s5[j])
{
t=s5[i];
s5[i]=s5[j];
s5[j]=t;
}
}
}
//Serial.println(s5);

for(int i=0;i<m;i++)
{
 int t=key[i]-'0';
  u[i]=s5[t];
}

for(int i=0;i<m;i++)
{
decrypt_msg+=String(u[i]);
}
Serial.print("\n");
Serial.print("decrypt_msg:");
Serial.print(decrypt_msg);
 }
else
{
  Serial.println("public key is wrong");
}
}
void loop() {
 

}
