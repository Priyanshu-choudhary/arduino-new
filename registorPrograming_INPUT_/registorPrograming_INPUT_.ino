void setup() {
  // put your setup code here, to run once:
pinMode(7,INPUT);
pinMode(13,OUTPUT);
}

void loop() {
if(PIND & B10000000){                                //RUN WHEN D7 IS HIGH
  PORTB |=B00100000;
 
  }
 else{
  PORTB &=B00000000;                                 //RUN WHEN D7 IS LOW
  }
  
}
