#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library

 RH_ASK rf_driver;
 float Sensitivity = 0.185;
 float d=0;  
 uint8_t data[8]; 
  
void setup(){
  rf_driver.init();
  Serial.begin(115200);
}

void loop(){

  if (rf_driver.recv((uint8_t*)&data,(uint8_t*)sizeof(data))){

  /*      
    int th =(data[3]<<24 )|(data[2]<<16 )|(data[1]<<8 )| data[0];
    int ya =(data[7]<<24 )|(data[6]<<16 )|(data[5]<<8 )| data[4];
    int ro =(data[11]<<24 )|(data[10]<<16 )|(data[9]<<8 )| data[8];
    int pi =(data[15]<<24 )|(data[14]<<16 )|(data[13]<<8 )| data[12];
*/

    uint16_t th =(data[1]<<8 )| data[0];
    uint16_t ya =(data[3]<<8 )| data[2];
    uint16_t ro =(data[5]<<8 )| data[4];
    uint16_t pi =(data[7]<<8 )| data[6];
    
    Serial.print("Message Received: ");
    Serial.print(data[0]);
    Serial.print("  ");
    Serial.print(data[1]);
    Serial.print("  ");
    Serial.print(ro);
    Serial.print("  ");
    Serial.println(pi);
    
  }else{
    
    //Serial.println("Message NOT Received: ");
    }
}
