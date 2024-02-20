#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
  int th=0;
  int ya=0;
  int ro=0;
  int pi=0;
  uint8_t aux1=0;
  uint8_t aux2=0;
  int ch5=0;
  int ch6=0;
int ch=1;

void setup(){
  rf_driver.init();
 pinMode(2,OUTPUT);
  cli();                      //stop interrupts for till we make the settings 
  //Timer 1 (interrupt each 50ms)
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  TIMSK1 |= B00000110;        //Set OCIE1A and OCIE1B to 1 -> compare match A and B
  sei();       //Enable back the interrupts  
                    
  OCR1A=(10.5*1000)/16;    
    
Serial.begin(9600);
}

void loop(){
  uint8_t data[9];
if (rf_driver.recv((uint8_t*)&data,sizeof(data))){

     th =(data[1]<<8 )| data[0];
     ya =(data[3]<<8 )| data[2];
     ro =(data[5]<<8 )| data[4];
     pi =(data[7]<<8 )| data[6];
    aux1=data[8];
    aux2=data[9];
    
    Serial.print("Message Received: ");
    Serial.print(th);
    Serial.print("  ");
    Serial.print(ya);
    Serial.print("  ");
    Serial.print(ro);
    Serial.print("  ");
    Serial.print(pi);
    Serial.print("  ");
    Serial.print(ch5);
    Serial.print("  ");
    Serial.println(ch6);
    
  }
  if(aux1==1){ch5=1000;}else{ch5=2000;}
  if(aux2==1){ch6=1000;}else{ch6=2000;}
}



ISR(TIMER1_COMPA_vect){
  cli(); 
  TCNT1=0;
  OCR1B = (400)/16; //400 us pulse to start a channel
  PORTD |=B00000100;//Write 1 on pin D2
  //Serial.println("1");
 switch (ch){
  case 1:
  OCR1A=(ro)/16;
  break;
  case 2:
  OCR1A=(pi)/16;
  break;
  case 3:
  OCR1A=(th)/16;
  break;
  case 4:
  OCR1A=(ya)/16;
  break;
  case 5:
  OCR1A=(ch5)/16;
  break;
  case 6:
  OCR1A=(ch6)/16;
  break;
  case 7:
  OCR1A=(1000)/16;
  break;
  
  }  
 ch=ch+1;
 if(ch>7){
  TCNT1=0;
  OCR1A=(10.5*1000)/16; //10.5 milli sec pulse for next data frame
  ch=1;
  }
 sei(); 
}

ISR(TIMER1_COMPB_vect){
  cli(); 
  //Serial.println("0");
  PORTD &=B00000000;  //Write 0 on pin D2
  sei();
}
