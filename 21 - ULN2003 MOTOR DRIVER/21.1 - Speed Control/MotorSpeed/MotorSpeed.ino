int motorPin = 11;
void setup() {
  pinMode(motorPin,OUTPUT);
}

void loop() {
  int value = analogRead(A0)/4;   // A0读到模拟值转到0－255之间
  analogWrite(motorPin,value);    // PWM调节电机速度
}
