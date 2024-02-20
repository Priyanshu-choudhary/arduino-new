#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
// Initialize ASK Object
rf_driver.init();
// Setup Serial Monitor
Serial.begin(9600);
analogReference(INTERNAL);
}
 
void loop()
{
uint16_t a=analogRead(A0);
uint8_t data[2]={a,(a>>8)};

rf_driver.send((uint8_t*)&data,sizeof(data));
rf_driver.waitPacketSent();{}
Serial.println(a);
}
