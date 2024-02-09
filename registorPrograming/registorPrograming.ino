void setup() {
  // put your setup code here, to run once:
DDRB |= B00100000;
}

void loop() {
  // put your main code here, to run repeatedly:
PORTB |=B00100000;
delay(100);
PORTB &=B00000000;
delay(100);
}
