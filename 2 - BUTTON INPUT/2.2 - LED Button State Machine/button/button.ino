int buttonPin = 8;
int ledPin = 13;
int ledState = LOW;

void setup() {
  pinMode(ledPin,OUTPUT);   //13号数字口设置为输出状态
}

#define buttonStateOff  0     //状态1，无键按下
#define buttonStateOn  1     //状态2，有键按下，但无法确定是否有效
#define buttonStateOnOff  2  //状态3，确定按键是否按下

char buttonValue()
{
  static int buttonState = 0;    //按键状态值，必须定义为static类型
  int buttonValue = 0;        //读取到的按键状态
  int buttonReturn = 0;       //返回的状态值
  buttonValue = digitalRead(buttonPin);  //读当前按键值
  switch(buttonState)        //判断当前按键状态
  {
    case buttonStateOff:       //状态1
      if(!buttonValue)         //如果键按下
      buttonState = buttonStateOn; //则转到状态2
      break;
    case buttonStateOn:  	  //状态2
      if(!buttonValue)  	       //如果按键仍被按下
      {
        buttonReturn = 1;       //按键赋值
        buttonState = buttonStateOnOff;  //进入状态3，松手检测
      }
      else  //否则存在抖动
      {
        buttonState = buttonStateOff;
      }
      break;
    case buttonStateOnOff:
      if(buttonValue) buttonState = buttonStateOff; //松手检测
      break;
  }
  return buttonReturn;  //返回按键值
}
void loop() { 
  if(buttonValue()){
    digitalWrite(ledPin,ledState);
    ledState=!ledState;
 }
}
