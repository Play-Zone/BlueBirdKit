#include <Servo.h>      // 引用官方舵机库
Servo myservo;         // 创建一个舵机控制对象
void setup(){  
  Serial.begin(9600);
  myservo.attach(7);     // 绑定至数字引脚D7  
}
void loop(){  
  myservo.write(180);   // 写入角度
  Serial.println(myservo.read());  // 打印舵机角度
  delay(1000);
  myservo.write(0);
  Serial.println(myservo.read());
  delay(1000);
}
