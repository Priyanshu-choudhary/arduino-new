
#include <Servo.h>

Servo myservo1; 
Servo myservo2; 
Servo myservo3; 
Servo myservo4; 
Servo myservo5; 
Servo myservo6; 
int Ich1= 2;
int Ich2= 4;
int Ich3= 7;
int Ich4= 8;
int Ich5= 12;
int Ich6= 13;
unsigned long ch1;
unsigned long ch2;
unsigned long ch3;
unsigned long ch4;
unsigned long ch5;
unsigned long ch6;
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(Ich1,INPUT);
pinMode(Ich2,INPUT);
pinMode(Ich3,INPUT);
pinMode(Ich4,INPUT);
pinMode(Ich5,INPUT);
pinMode(Ich6,INPUT);

myservo1.attach(3);
myservo2.attach(5);
myservo3.attach(6);
myservo4.attach(9);
myservo5.attach(10);
myservo6.attach(11);

}

void loop() {
  // put your main code here, to run repeatedly:
ch1= pulseIn(Ich1,HIGH);
ch2= pulseIn(Ich2,HIGH);
ch3= pulseIn(Ich3,HIGH);
ch4= pulseIn(Ich4,HIGH);
ch5= pulseIn(Ich5,HIGH);
ch6= pulseIn(Ich6,HIGH);

myservo1.writeMicroseconds(ch1);
myservo2.writeMicroseconds(ch2);
myservo3.writeMicroseconds(ch3);
myservo4.writeMicroseconds(ch4);
myservo5.writeMicroseconds(ch5);
myservo6.writeMicroseconds(ch6);

/*Serial.print(ch1);
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
*/
}
