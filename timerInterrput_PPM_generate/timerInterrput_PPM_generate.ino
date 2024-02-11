int ch=1;
long int timedelay=10.5;
int ch1Value=1000;
int ch2Value=1000;
int ch3Value=2000;
int ch4Value=1000;
int ch5Value=1000;
int ch6Value=1000;
int ch7Value=1000;



void setup() {
  pinMode(2,OUTPUT);
  cli();                      //stop interrupts for till we make the settings 
  //Timer 1 (interrupt each 50ms)
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  TIMSK1 |= B00000110;        //Set OCIE1A and OCIE1B to 1 -> compare match A and B
  sei();       //Enable back the interrupts  
                    
  OCR1A=(10.5*1000)/16;        
Serial.begin(115200);
}

void loop() {
  


  
}



ISR(TIMER1_COMPA_vect){
  TCNT1=0;
  OCR1B = (400)/16; //400 us pulse to start a channel
  PORTD |=B00000100;//Write 1 on pin D3
  Serial.println("1");
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
  Serial.println("0");
  PORTD &=B00000000;  //Write 0 on pin D3
}
