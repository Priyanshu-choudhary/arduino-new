#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
  int th=0;
  int ya=0;
  int ro=0;
  int pi=0;
void setup()
{
// Initialize ASK Object
rf_driver.init();
// Setup Serial Monitor
Serial.begin(9600);
  
}
 
void loop()
{
uint8_t data[4];
//uint16_t c=(data[3]<<24 )|(data[2]<<16 )|(data[1]<<8 )| data[0];
if (rf_driver.recv((uint8_t*)&data,sizeof(data))){

     th =(data[1]<<8 )| data[0];
     ya =(data[3]<<8 )| data[2];
     ro =(data[5]<<8 )| data[4];
     pi =(data[7]<<8 )| data[6];
    
    Serial.print("Message Received: ");
    Serial.print(th);
    Serial.print("  ");
    Serial.print(ya);
    Serial.print("  ");
    Serial.print(ro);
    Serial.print("  ");
    Serial.println(pi);
    
  }
}
