long int pluseS=0;
long int pluseE=0;
bool flag=true;
long int val=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
PCICR  |=B00000001;
PCMSK0 |=B00100000;
pinMode(13,INPUT);
}

ISR(PCINT0_vect){
  pluseS=micros();
  if(PINB & B00100000){ //RUN WHEN D7 IS HIGH
      if(flag==0){
        flag=1;
        pluseE=pluseS; 
        }
  }
 else if(flag==1){
  flag=0;
  val=pluseS-pluseE;                                
  }
}
void loop() {
  // put your main code here, to run repeatedly:
Serial.println(val);
}
