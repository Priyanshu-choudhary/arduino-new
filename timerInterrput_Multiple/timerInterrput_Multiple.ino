bool LED_STATE1 = true;
bool LED_STATE2 = true;

void setup() {
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  cli();                      //stop interrupts for till we make the settings 
  //Timer 1 (interrupt each 100ms)
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A
  OCR1A = 6250;              //Finally we set compare register A to this value 

  //Timer2 (interrupt each 8.128 ms)
  // interrupt time = 1/(16Mhz/1024) * 127 =  8.128ms;
  TCCR2A = 0;                 // Reset entire TCCR1A to 0 
  TCCR2B = 0;                 // Reset entire TCCR1B to 0
  TCCR2B |= B00000111;        //Set CS20, CS21 and CS22 to 1 so we get prescalar 1024  
  TIMSK2 |= B00000100;        //Set OCIE1B to 1 so we enable compare match B
  OCR2B = 127;                //Finally we set compare register B to this value 
  sei();                      //Enable back the interrupts
}

void loop() {
  // put your main code here, to run repeatedly:
}


//With the settings above, this IRS will trigger each 8.128ms.
ISR(TIMER2_COMPB_vect){                               
  LED_STATE1 = !LED_STATE1;    //Invert LED state
  digitalWrite(5,LED_STATE1);  //Write new state to the LED on pin D5
}

//With the settings above, this IRS will trigger each 100ms.
ISR(TIMER1_COMPA_vect){
  TCNT1  = 0;                  //First, set the timer back to 0 so it resets for next interrupt
  LED_STATE2 = !LED_STATE2;    //Invert LED state
  digitalWrite(6,LED_STATE2);  //Write new state to the LED on pin D5
}
