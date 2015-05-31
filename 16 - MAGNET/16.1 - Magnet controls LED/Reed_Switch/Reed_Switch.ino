#define LED_pin 13   
#define Magnetic_pin 4 
void setup() 
{  
  pinMode(LED_pin,OUTPUT);     
  pinMode(Magnetic_pin,INPUT); 
}
void loop() 
{  
  if(digitalRead(Magnetic_pin)  == LOW) {  
    digitalWrite(LED_pin,HIGH);  
  }
  else { 
    digitalWrite(LED_pin,LOW); 
  }
}
