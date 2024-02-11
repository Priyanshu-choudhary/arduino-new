#include   "NewPing.h"
#include <PIDController.h>
PIDController pid; // Create an instance of the PID controller class, called "pid"

#include <PID_v1.h>
double Setpoint, Input, Output;
double Kp=1.07, Ki=10, Kd=1.08;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


float xn1 = 0;
float yn1 = 0;
#define TRIGGER_PIN A3
#define ECHO_PIN A2
#define MAX_DISTANCE 400   

int ch=1;
 int sum=0;
  int avg=0;
  int noice=0;
unsigned long counter_1, counter_2, counter_3, counter_4, current_count,counter_5,counter_6;
byte last_CH1_state, last_CH2_state, last_CH3_state, last_CH4_state,last_CH5_state,last_CH6_state;

int input_YAW =1000;      //In my case channel 4 of the receiver and pin D12 of arduino
int input_PITCH=1000;    //In my case channel 2 of the receiver and pin D9 of arduino
int input_ROLL=1000; 
int input_aux1=1000;    //In my case channel 2 of the receiver and pin D9 of arduino
int input_aux2=1000;     //In my case channel 1 of the receiver and pin D8 of arduino
int input_THROTTLE=1000; //In my case channel 3 of the receiver and pin D10 of arduino
int auto_YAW=1000;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
   
   Serial.begin(115200);
   pinMode(2,OUTPUT);

  PCICR |= (1 << PCIE0); 
                                               
  PCMSK0 |= (1 << PCINT0);  //Set pin D8 trigger an interrupt on state change. 
  PCMSK0 |= (1 << PCINT1);  //Set pin D9 trigger an interrupt on state change.                                             
  PCMSK0 |= (1 << PCINT2);  //Set pin D10 trigger an interrupt on state change.                                               
  PCMSK0 |= (1 << PCINT3);  //Set pin D12 trigger an interrupt on state change.  
  PCMSK0 |= (1 << PCINT4);  //Set pin D10 trigger an interrupt on state change.                                               
  PCMSK0 |= (1 << PCINT5);  //Set pin D12 trigger an interrupt on state change. 
                                                 
 

   cli();                      //stop interrupts for till we make the settings 
  
  TCCR1A = 0;                 // Reset entire TCCR1A to 0 
  TCCR1B = 0;                 // Reset entire TCCR1B to 0
  TCCR1B |= B00000100;        //Set CS12 to 1 so we get prescalar 256  
  TIMSK1 |= B00000110;        //Set OCIE1A and OCIE1B to 1 -> compare match A and B
  sei();                      //Enable back the interrupts  
                    
  OCR1A=(10.5*1000)/16;       //set ocrc1a to 10.5 millisec compare A match
  


  pid.begin(80 );             // initialize the PID instance
  pid.setpoint(0);        // The "goal" the PID controller tries to "reach"
  pid.tune(15, 9,30);     // Tune the PID, arguments: kP, kI, kD
  pid.limit(1350, 1500);

  
  Setpoint = 70;
  myPID.SetMode(AUTOMATIC);
}

void loop() {
  for(int i=0;i<10;i++){
     noice=sonar.ping_cm();
    sum=sum+noice;
    }
    
  avg= sum/10;
  
  
  xn1=avg;
  yn1=filteredSignal;

  Input =(int)filteredSignal;
  myPID.Compute();

  if((int)filteredSignal>0.5){
     auto_YAW = Output;
    }
  else{
    auto_YAW=1350;
    }

   Serial.print((int)filteredSignal);
   Serial.print("        ");
   Serial.println(auto_YAW);
   /*
   Serial.println("        ");
   Serial.print(input_ROLL);
   Serial.print("    ");
   Serial.print(input_YAW);
   Serial.print("    ");
   Serial.print(input_PITCH);
   Serial.print("    ");
   Serial.print(input_THROTTLE);
   Serial.print("    ");
   Serial.print(input_aux1);
   Serial.print("    ");
   Serial.println(input_aux2);
 */
 
 sum=0;
}

ISR(PCINT0_vect){
//First we take the current count value in micro seconds using the micros() function
  
  current_count = micros();
  ///////////////////////////////////////Channel 1
  if(PINB & B00000001){                              //We make an AND with the pin state register, We verify if pin 8 is HIGH???
    if(last_CH1_state == 0){                         //If the last state was 0, then we have a state change...
      last_CH1_state = 1;                            //Store the current state into the last state for the next loop
      counter_1 = current_count;                     //Set counter_1 to current value.
    }
  }
  else if(last_CH1_state == 1){                      //If pin 8 is LOW and the last state was HIGH then we have a state change      
    last_CH1_state = 0;                              //Store the current state into the last state for the next loop
    input_ROLL = current_count - counter_1;   //We make the time difference. Channel 1 is current_time - timer_1.
  }



  ///////////////////////////////////////Channel 2
  if(PINB & B00000010 ){                             //pin D9 -- B00000010                                              
    if(last_CH2_state == 0){                                               
      last_CH2_state = 1;                                                   
      counter_2 = current_count;                                             
    }
  }
  else if(last_CH2_state == 1){                                           
    last_CH2_state = 0;                                                     
    input_YAW = current_count - counter_2;                             
  }

///////////////////////////////////////Channel 3
  if(PINB & B00000100 ){                             //pin D10 - B00000100                                         
    if(last_CH3_state == 0){                                             
      last_CH3_state = 1;                                                  
      counter_3 = current_count;                                               
    }
  }
  else if(last_CH3_state == 1){                                             
    last_CH3_state = 0;                                                    
    input_PITCH = current_count - counter_3;                            

  }


  
  ///////////////////////////////////////Channel 4
  if(PINB & B00010000 ){                             //pin D12  -- B00010000                      
    if(last_CH4_state == 0){                                               
      last_CH4_state = 1;                                                   
      counter_4 = current_count;                                              
    }
  }
  else if(last_CH4_state == 1){                                             
    last_CH4_state = 0;                                                  
    input_THROTTLE = current_count - counter_4;                            
  }
   ///////////////////////////////////////Channel 5
  if(PINB & B00100000 ){                             //pin D13  -- B00010000                      
    if(last_CH5_state == 0){                                               
      last_CH5_state = 1;                                                   
      counter_5 = current_count;                                              
    }
  }
  else if(last_CH5_state == 1){                                             
    last_CH5_state = 0;                                                  
    input_aux1 = current_count - counter_5;                            
  }


  ///////////////////////////////////////Channel 6
  if(PINB & B00001000 ){                             //pin D11  -- B00010000                      
    if(last_CH6_state == 0){                                               
      last_CH6_state = 1;                                                   
      counter_6 = current_count;                                              
    }
  }
  else if(last_CH6_state == 1){                                             
    last_CH6_state = 0;                                                  
    input_aux2 = current_count - counter_6;                            
  }
}



ISR(TIMER1_COMPA_vect){
  TCNT1=0;
  OCR1B = (400)/16; //400 us pulse to start a channel
  PORTD |=B00000100;//Write 1 on pin D2
   //Serial.println("1");
 switch (ch){
  case 1:
  OCR1A=(input_ROLL)/16;
  break;
  case 2:
  OCR1A=(input_PITCH)/16;
  break;
  case 3:
  if(input_aux1<1700){
  OCR1A=(input_YAW)/16;
  }else{
  OCR1A=(auto_YAW)/16;
  }
  break;
  case 4:
  OCR1A=(input_THROTTLE)/16;
  break;
  case 5:
  OCR1A=(input_aux1)/16;
  break;
  case 6:
  OCR1A=(input_aux2)/16;
  break;
  case 7:
  OCR1A=(1000)/16;
  break;
  
  }  
 ch=ch+1;
 if(ch>7){
  TCNT1=0;
  OCR1A=(10.5*1000)/16; //10.5 milli sec pulse for next data frame
  ch=1;
  }
  
}

ISR(TIMER1_COMPB_vect){
 // Serial.println("0");
  PORTD &=B00000000;  //Write 0 on pin D2
}
