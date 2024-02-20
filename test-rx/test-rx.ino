
//Code for receiver:
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define led1 2


int buttonState = 0;

RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00002";

void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH); 
  radio.begin();
  radio.setAutoAck(false); 
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  delay(100);
}
void loop() {
  radio.startListening();
  while (!radio.available());
  radio.read(&buttonState, sizeof(buttonState));
  Serial.println(buttonState);
  delay (100);

  if (buttonState == 1) {
    digitalWrite(led1, LOW);
  }
  else  if (buttonState == 0) {
    digitalWrite(led1, HIGH);
  }
}
