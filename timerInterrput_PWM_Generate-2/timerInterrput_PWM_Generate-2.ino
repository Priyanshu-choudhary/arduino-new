bool A_STATE = true;
bool B_STATE = true;
long int timedelay=16.5;
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  cli();                      //stop interrupts for till we make the settings 
  //Timer 1 (interrupt each 50ms)
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  TIMSK1 |= B00000110;        //Set OCIE1A and OCIE1B to 1 -> compare match A and B
  sei();                      //Enable back the interrupts                    
}

void loop() {
  long int pwm=map(analogRead(A1),0,1024,1000,2000);
  OCR1B = (pwm)/16;
  OCR1A=(timedelay*1000)/16;  
}



ISR(TIMER1_COMPA_vect){
  TCNT1=0;
  PORTD |=B00000100;  //Write new state to the LED on pin D5
}

ISR(TIMER1_COMPB_vect){
  
  PORTD &=B00000000;  //Write new state to the LED on pin D5
}
