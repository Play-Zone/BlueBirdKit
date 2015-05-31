#define LED 10  // 定义LED引脚为 10
int val = 0;    // 定义变量val储存传感器值
void setup(){
  pinMode(LED ,OUTPUT); // 定义LED引脚为输出

}
void loop(){
  val = analogRead(2);
  if (val > 1000){          // 开关断开时，A2通过10K上拉至VCC
    digitalWrite(LED,HIGH);  // 点亮LED灯 
  } else{  
    digitalWrite(LED,LOW); // 熄灭LED灯
  }
}
