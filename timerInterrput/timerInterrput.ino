bool led=1;

long int timedelay=1;


void setup() {
DDRD |=B01000000; //set d6 as output
cli();

TCCR1A=0;
TCCR1B=0;
TCCR1B |= B00000100; //set prescale to 256 16us pulse [OCR1A=(timeInMilliSecound*1000)/16;]
TIMSK1 |= B00000010;//Set OCIE1A  to enable compare change A match 

OCR1A=1;
//OCR1A=(timedelay*1000)/16;  //100 millisec
sei();
}

ISR(TIMER1_COMPA_vect){
  TCNT1=0;
  if(led==1){
    PORTD |=B01000000;
    led=0;
  }else{
    PORTD &=B00000000;
    led=1;
    }
 
  
  }
void loop() {
  // put your main code here, to run repeatedly:

}
