#include   "NewPing.h"
float xn1 = 0;
float yn1 = 0;
#define TRIGGER_PIN A3
#define ECHO_PIN A2
#define MAX_DISTANCE 400   
 int ch=1;
int led=1;
int Ich1= 2;
int Ich2= 4;
int Ich3= 7;
int Ich4= 8;
int Ich5= 12;
int Ich6= 13;
unsigned long ch1Value;
unsigned long ch2Value;
unsigned long ch3Value;
unsigned long ch4Value;
unsigned long ch5Value;
unsigned long ch6Value;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
   
   Serial.begin(115200);
   pinMode(9,OUTPUT);
   
   pinMode(Ich1,INPUT);
   pinMode(Ich2,INPUT);
   pinMode(Ich3,INPUT);
   pinMode(Ich4,INPUT);
   pinMode(Ich5,INPUT);
   pinMode(Ich6,INPUT);


   //pinMode(A4,OUTPUT);
   //pinMode(A5,OUTPUT);
   cli();                      //stop interrupts for till we make the settings 
  
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  TIMSK1 |= B00000110;        //Set OCIE1A and OCIE1B to 1 -> compare match A and B
  sei();                      //Enable back the interrupts  
                    
  OCR1A=(10.5*1000)/16;       //set ocrc1a to 10.5 millisec compare A match

}

void loop() {
  int noice=sonar.ping_cm();
  float filteredSignal= 0.969*yn1+0.0155*noice+0.0155*xn1;
  
  xn1=noice;
  yn1=filteredSignal;
  Serial.println(noice);
  
  /*
ch1Value= pulseIn(Ich1,HIGH);
ch2Value= pulseIn(Ich2,HIGH);
ch3Value= pulseIn(Ich3,HIGH);
ch4Value= pulseIn(Ich4,HIGH);
ch5Value= pulseIn(Ich5,HIGH);
ch6Value= pulseIn(Ich6,HIGH);
Serial.println("p");
*/
/*
ch1Value=1200;
ch2Value=1200;
ch3Value=1200;
ch4Value=1200;
ch5Value=1200;
ch6Value=1200;

 
 */}



ISR(TIMER1_COMPA_vect){
  TCNT1=0;
  OCR1B = (400)/16; //400 us pulse to start a channel
  PORTB |=B00000010;//Write 1 on pin D3
 switch (ch){
  case 1:
  OCR1A=(ch1Value)/16;
  break;
  case 2:
  OCR1A=(ch2Value)/16;
  break;
  case 3:
  OCR1A=(ch3Value)/16;
  break;
  case 4:
  OCR1A=(ch4Value)/16;
  break;
  case 5:
  OCR1A=(ch5Value)/16;
  break;
  case 6:
  OCR1A=(ch6Value)/16;
  break;
  case 7:
  OCR1A=(ch6Value)/16;
  break;
  
  }  
 ch=ch+1;
 if(ch>7){
  TCNT1=0;
  OCR1A=(10.5*1000)/16; //10.5 milli sec pulse for next data frame
  ch=1;
  }
  
}

ISR(TIMER1_COMPB_vect){
  
  PORTB &=B00000000;  //Write 0 on pin D3
}
