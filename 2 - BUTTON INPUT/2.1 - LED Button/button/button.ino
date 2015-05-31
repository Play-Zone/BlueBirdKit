int buttonPin = 8;      //按键输入引脚
int ledPin = 13;        //灯输出控制引脚 
int ledState = LOW;
void setup() {
  pinMode(ledPin,OUTPUT);//   //13号数字口设置为输出状态
}
void loop() { 
 if(!digitalRead(buttonPin)) //检测按键是否被按下
 {
   delay(15);                //延时10ms，消除按键机械抖动
   if(!digitalRead(buttonPin))  //再次检测按键值
   {
     while(!digitalRead(buttonPin)) ;     //松手检测，等待按键释放
     digitalWrite(ledPin,ledState);       //控制灯的亮灭
     ledState = !ledState;              //状态取反
   }
 }
}
