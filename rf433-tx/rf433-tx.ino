#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
#include <SoftwareSerial.h> // Include dependant SPI Library

RH_ASK rf_driver;
 int b=0;
void setup()
{
// Initialize ASK Object
rf_driver.init();
analogReference(INTERNAL);
Serial.begin(115200);
}
 
void loop()
{

int b=1012;
uint8_t data[2]={b,(b>>8)};

rf_driver.send((uint8_t*)&data,sizeof(data));
rf_driver.waitPacketSent();{}
}
float Volt(int pin,float factor,bool r){
   float AcsValue = 0.0, Samples = 0.0, AvgAcs = 0.0;
  for (int x = 0; x < 10; x++) {  // Get 150 samples
   int AcsValue = analogRead(pin);  
    Samples = Samples + AcsValue;  // Add samples together
    delay(2); // let ADC settle before following sample 3ms
  }
  AvgAcs = Samples / 10.0;
  Samples=0;
  float vout=(AvgAcs * (2.56 / 1023.0))+0.01;
  float volt = (vout*factor);
  if(r){
    return vout;
  }else{
return volt;
}
}
