#include "NewPing.h"
float xn1 = 0;
float yn1 = 0;
#define TRIGGER_PIN A2
#define ECHO_PIN A3
#define MAX_DISTANCE 400  


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int led=1;
void setup() {
  Serial.begin(9600);
  pinMode(A5,OUTPUT);
}

void loop() {
  if(led==1){
    PORTC |=B00100000;
    led=0;
    }
    else{
    PORTC &=B00000000;
     led=1;
      }
  int noice=sonar.ping_cm();
 
  
  Serial.print(noice);
  Serial.print("  ");
  float filteredSignal= 0.969*yn1+0.0155*noice+0.0155*xn1;
  Serial.println(filteredSignal);
  
  xn1=noice;
  yn1=filteredSignal;
  
  //delay(10);
}
