int buzzer = 3;
int SW520D = A2;
int val = 0;    // 定义变量val储存传感器值
void setup(){
  pinMode(buzzer,OUTPUT);
}
void buzzer_didi(){
  for(int i=3;i>0;i--){
  digitalWrite(buzzer,HIGH);
  delay(90);
  digitalWrite(buzzer,LOW);
  delay(90);
  }
  delay(600);
}
void buzzer_stop(){
  digitalWrite(buzzer,LOW);
}
void loop(){
  if(analogRead(SW520D) > 1000)
    buzzer_didi();
  else
    buzzer_stop();
}
