/***************************************
 * 光控延时灯
 * 光照强度强时，保持LED熄灭
 *   光照强度低，按键按下，点亮LED并保持5S
 * BY YFROBOT
 ****************************************/

int photoresistancePin = 0;  
int ledPin = 11;  
int buttonPin = 3;

int photoresistancevVal = 0;   
int buttonVal = 3;

void setup() 
{ 
  pinMode(ledPin, OUTPUT);  
  pinMode(photoresistancePin, INPUT); 
  pinMode(buttonPin, INPUT); 
} 

void loop() { 
  //读取传感器值
  photoresistancevVal = analogRead(photoresistancePin);

  if(photoresistancevVal<=512){ 
    //光照强度强时，白天，保持LED熄灭   
    digitalWrite(ledPin, LOW);
  }
  else{
    buttonVal = digitalRead(buttonPin);
    //光照强度低，晚上，按键按下，点亮LED并保持5S
    if(buttonVal == HIGH){
      delay(40);
      digitalWrite(ledPin, HIGH); 
      delay(5000);
      digitalWrite(ledPin, LOW);
    }
  }
}

