#include <Servo.h>
#include <IRremote.h>
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
int motorPin = 6;
Servo myServo;
int powerState = 0;
int swingState = 0;
int motorSpeed = 255;
int pos = 0;    // variable to store the servo position 
void setup() {
  pinMode(motorPin,OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  myServo.attach(12);
}

void irRec(){
  if (irrecv.decode(&results)) {
    irrecv.resume(); // Receive the next value
    switch(results.value){
      case 0xFFA25D:
        powerState = !powerState;
        break;
      case 0xFF629D:
        swingState = !swingState;
        break;
      case 0xFF906F:
        motorSpeed += 50;
        if(motorSpeed>250){
          motorSpeed = 255;
        }
        break;
      case 0xFFA857:
        motorSpeed -=50;
        if(motorSpeed <=50){
          motorSpeed = 50;
        }
    }
  }
  if(powerState == 1){
    analogWrite(motorPin,motorSpeed);
    if(swingState == 1){
      for(pos = 40; pos < 140; pos += 1){     
        for(int j=40;j<800;j++){  
          myServo.write(pos);
          if (irrecv.decode(&results))  
            break;
        }  
     } 
     for(pos = 140; pos>=40; pos-=1){                                
       for(int j=40;j<800;j++){    
         myServo.write(pos);
         if (irrecv.decode(&results))  
           break;  
       } 
     } 
   }
   else{
     myServo.write(90);
   }
  }
  else{
    analogWrite(motorPin,0);
  }
}
void loop() {
  irRec();
}
