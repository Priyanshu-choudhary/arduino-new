#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <RH_ASK.h> 
#include <SPI.h> 

RH_ASK rf_driver;
LiquidCrystal_I2C lcd(  0x3F,16,2);

uint16_t  th=0;
uint16_t  ya=0;
uint16_t  pi=0;
uint16_t  ro=0;

int th_low=0;
int ya_low=0;
int pi_low=0;
int ro_low=0;

int th_high=1023;
int ya_high=1023;
int pi_high=1023;
int ro_high=1023;

int th_corr=0;
int ya_corr=0;
int pi_corr=0;
int ro_corr=0;

int buttonPin=7;
long int time_press=0;
long int dur=0;
long int bps=0;
uint8_t flag=0;
uint8_t sw1_s=0;
uint8_t sw2_s=0;
uint8_t sw1=2;
uint8_t sw2=6;
void setup() {
  pinMode(8, OUTPUT);
  digitalWrite(8,1);
  delay(200);
  digitalWrite(8,0);
  dur=0;
  Serial.begin(9600);
  rf_driver.init();
  
  analogReference(DEFAULT);
  
  lcd.init();                      
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("YADI");
  delay(500);
  lcd.clear();
  
  pinMode(buttonPin, INPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  digitalWrite(buttonPin,1);

  EEPROM.get(0,th_high);
  EEPROM.get(5,ya_low);
  EEPROM.get(10,pi_high);
  EEPROM.get(15,ro_low);
  
  EEPROM.get(20,th_low);
  EEPROM.get(25,ya_high);
  EEPROM.get(30,pi_low);
  EEPROM.get(35,ro_high);

 
  EEPROM.get(40,th_corr);
  EEPROM.get(45,ya_corr);
  EEPROM.get(50,pi_corr);
  EEPROM.get(55,ro_corr);


}

void loop() { 
   read_pot();
   if(flag==0){lcd_display();}
   send_data(); 
   callibrate();
   adjustButtons();
   
   if(flag==1){showBattery(); }
    
 
}
void showBattery(){
  analogReference(INTERNAL);
  float bat=Volt(1,3.7056,0);
  lcd.setCursor(0,0);
  lcd.print("Battery:");
  lcd.setCursor(0,1);
  lcd.print(bat);
  
  
  }
void adjustButtons(){
  int buttonRead=952-analogRead(A0);
  //lcd.clear();
  
  if(buttonRead>=330 && buttonRead<=340){th_corr++;digitalWrite(8,1);delay(200);  EEPROM.put(40,th_corr);}
  if(buttonRead>=180 && buttonRead<=185){th_corr--;digitalWrite(8,1);delay(200);  EEPROM.put(40,th_corr);}
  
  if(buttonRead>=460 && buttonRead<=465){ya_corr++;digitalWrite(8,1);delay(200);  EEPROM.put(45,ya_corr);}
  if(buttonRead>=615 && buttonRead<=625){ya_corr--;digitalWrite(8,1);delay(200);  EEPROM.put(45,ya_corr);}

  if(buttonRead>=525 && buttonRead<=535){pi_corr++;digitalWrite(8,1);delay(200);  EEPROM.put(50,pi_corr);}
  if(buttonRead>=712 && buttonRead<=718){pi_corr--;digitalWrite(8,1);delay(200);  EEPROM.put(50,pi_corr);}

  if(buttonRead>=690 && buttonRead<=710){ro_corr++;digitalWrite(8,1);delay(200);  EEPROM.put(55,ro_corr);}
  if(buttonRead>=155 && buttonRead<=165){ro_corr--;digitalWrite(8,1);delay(200);  EEPROM.put(55,ro_corr);}

  digitalWrite(8,0);
  }

float Volt(int pin,float factor,bool r){
   float AcsValue = 0.0, Samples = 0.0, AvgAcs = 0.0;
  for (int x = 0; x < 30; x++) {  // Get 10 samples
   int AcsValue = analogRead(pin);  
    Samples = Samples + AcsValue;  // Add samples together
    delay(2); // let ADC settle before following sample 3ms
  }
  AvgAcs = Samples / 30.0;
  Samples=0;
  float vout=(AvgAcs * (1.1 / 1023.0));
  float volt = (vout*factor);
  if(r){
    return vout;
  }else{
return volt;
}
}

void read_pot(){
  analogReference(DEFAULT);
  th=map(analogRead(A3),th_high,th_low,1000,2000);
  ya=map(analogRead(A2),ya_low,ya_high,1000,2000);
  ro=map(analogRead(A7),ro_low,ro_high,1000,2000);
  pi=map(analogRead(A6),pi_high,pi_low,1000,2000); 

  th=th+th_corr;
  ya=ya+ya_corr;
  pi=pi+pi_corr;
  ro=ro+ro_corr;
  int state=digitalRead(buttonPin);
  
  if(state!=bps){
    if (state == LOW) { 
        time_press=millis();
    }  else {
        dur=millis()-time_press;
      }
  }
  bps=state;
  sw1_s=digitalRead(sw1);
  sw2_s=digitalRead(sw2);
}

void lcd_display(){
  
  lcd.setCursor(8,0);
  lcd.print("Y ");
  lcd.print(ya);
  
  lcd.setCursor(0,0);
  lcd.print("T ");
  lcd.print(th);

  lcd.setCursor(8,1);
  lcd.print("R ");
  lcd.print(ro);

  lcd.setCursor(0,1);
  lcd.print("P ");
  lcd.print(pi);
  if(sw1_s==1){lcd.setCursor(15,0); lcd.print("0");}
  else{lcd.setCursor(15,0); lcd.print("1");}
  
  if(sw2_s==1){lcd.setCursor(15,1); lcd.print("0");}
  else{lcd.setCursor(15,1); lcd.print("1");}
}

void serial_display(){

  Serial.print(ya);
  Serial.print("  ");
  Serial.print(th);
  Serial.print("  ");
  Serial.print(ro);
  Serial.print("  ");
  Serial.println(pi);


  
  }
void send_data(){
  //uint8_t data[16]={th,(th>>8),(th>>16),(th>>24),ya,(ya>>8),(ya>>16),(ya>>24),ro,(ro>>8),(ro>>16),(ro>>24),pi,(pi>>8),(pi>>16),(pi>>24)};
  uint8_t data[10]={th,(th>>8),ya,(ya>>8),ro,(ro>>8),pi,(pi>>8),sw1_s,sw2_s};

  rf_driver.send((uint8_t*)&data,sizeof(data));
  rf_driver.waitPacketSent();{}
  
  
  }  
 void callibrate(){
    
    
    if(dur<1000&&dur>50){
    lcd.clear();
    dur=0;
    flag++;
    if(flag>1){flag=0;}
    digitalWrite(8,1);
    delay(200);
    digitalWrite(8,0);
    dur=0;
    }
    
    if(dur>2000&&dur<5000){
    digitalWrite(8,1);
    delay(200);
    digitalWrite(8,0);
    lcd.setCursor(0,0);  
    lcd.clear();
    lcd.print("Callibrating....");
    lcd.setCursor(0,1);
    lcd.print("LOW POINTS");

    delay(2800);


    th_high=analogRead(A3);
    ya_low=analogRead(A2);
    pi_high=analogRead(A6);
    ro_low=analogRead(A7);
    
    EEPROM.put(0,th_high);
    EEPROM.put(5,ya_low);
    EEPROM.put(10,pi_high);
    EEPROM.put(15,ro_low);
    
    lcd.clear();

    digitalWrite(8,1);
    delay(200);
    digitalWrite(8,0);    
    lcd.setCursor(0,0);  
    lcd.print("Callibrating....");
    lcd.setCursor(0,1);
    lcd.print("HIGH POINTS");
    delay(2800);    
    th_low=analogRead(A3);
    ya_high=analogRead(A2);
    pi_low=analogRead(A6);
    ro_high=analogRead(A7);

    
    EEPROM.put(20,th_low);
    EEPROM.put(25,ya_high);
    EEPROM.put(30,pi_low);
    EEPROM.put(35,ro_high);
    
    lcd.clear();
    digitalWrite(8,1);
    delay(200);
    digitalWrite(8,0);
    delay(200);    
    digitalWrite(8,1);
    delay(200);
    digitalWrite(8,0);
    dur=0;
    }
 } 
 
