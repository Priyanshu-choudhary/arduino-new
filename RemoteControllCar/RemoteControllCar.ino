

int Ich1= 2;
int Ich2= 4;
int Ich3= 7;
int Ich4= 8;
int Ich5= 12;
int Ich6= 13;

int ln=9;
int lp=6;
int sl=5;

int rn=10;
int rp=11;
int sr=3;

int led=A4; 

unsigned long ch1=0;
unsigned long ch2=0;
unsigned long ch3=0;
unsigned long ch4=0;
unsigned long ch5=0;
unsigned long ch6=0;

void setup() {
//Serial.begin(115200);
pinMode(Ich1,INPUT);
pinMode(Ich2,INPUT);
pinMode(Ich3,INPUT);
pinMode(Ich4,INPUT);
pinMode(Ich5,INPUT);
pinMode(Ich6,INPUT);

pinMode(lp,OUTPUT);
pinMode(ln,OUTPUT);
pinMode(sl,OUTPUT);
pinMode(sr,OUTPUT);
pinMode(rp,OUTPUT); 
pinMode(rn,OUTPUT);
pinMode(led,OUTPUT);
ch6=0;
}

void loop() {
  
ch1= pulseIn(Ich1,HIGH);
//ch2= pulseIn(Ich2,HIGH);
//ch3= pulseIn(Ich3,HIGH);
ch4= pulseIn(Ich4,HIGH);
//ch5= pulseIn(Ich5,HIGH);
ch6= pulseIn(Ich6,HIGH);  
if(ch6>1600){
//////////////////////////moving///////////////////////


if(ch4>1530){
  digitalWrite(ln,0);
  digitalWrite(lp,1);  
  
  digitalWrite(rn,0);
  digitalWrite(rp,1);  

  
  digitalWrite(sl,1);
  digitalWrite(sr,1);
  
 // int speed=map(ch4,1510,1990,0,255);
  
  //analogWrite(sl,speed);
  //analogWrite(sr,speed);
  }
else if(ch4<1470){
  digitalWrite(ln,1);
  digitalWrite(lp,0);
  
  digitalWrite(rn,1);
  digitalWrite(rp,0);  


  
  digitalWrite(sl,1);
  digitalWrite(sr,1);
  
  //int speed=map(ch4,1000,1490,255,0);
  //analogWrite(sl,speed);
  //analogWrite(sr,speed);
  }

  else if(ch4>1470&&ch4<1530){
    
  digitalWrite(sl,0);
  digitalWrite(sr,0);
  
    }
//////////////////////////turning/////////////////
if(ch1>1530 && ch4<1530 && ch4>1470){
  digitalWrite(ln,0);
  digitalWrite(lp,1);  
  
  digitalWrite(rn,1);
  digitalWrite(rp,0);

  digitalWrite(sl,1);
  digitalWrite(sr,1);
  
  }
else if(ch1<1470 && ch4<1530 && ch4>1470){
  digitalWrite(ln,1);
  digitalWrite(lp,0);  
  
  digitalWrite(rn,0);
  digitalWrite(rp,1);  
  
  digitalWrite(sl,1);
  digitalWrite(sr,1);
  
  }
  
if(ch6>1600){
  digitalWrite(led,1);
  }else{
    digitalWrite(led,0);
    }
  /*
Serial.print(ch1);
Serial.print("\t");
Serial.print(ch2);
Serial.print("\t");
Serial.print(ch3);
Serial.print("\t");
Serial.print(ch4);
Serial.print("\t");
Serial.print(ch5);
Serial.print("\t");
Serial.print(ch6);
Serial.print("\t");
Serial.println();

delay(50);
*/
}
else{
  
  digitalWrite(sl,1);
  digitalWrite(sr,1);
  
  }
}
