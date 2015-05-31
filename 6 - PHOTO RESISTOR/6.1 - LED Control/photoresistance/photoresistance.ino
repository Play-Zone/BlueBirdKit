int photoresPin = A0;  //定义变量photoresPin=0，为电压读取端口。
int ledPin = 11;        //设置led数字IO脚
int val = 0;             //定义变量val
void setup() 
{ 
  pinMode(ledPin, OUTPUT);     //设置ledPin脚模式，OUTPUT为输出
} 
void loop()
 { 
  val = analogRead(photoresPin);     //从传感器读取值
  if(val<=512)
  {     
    digitalWrite(ledPin, HIGH);     //当光照强度过强时led灭。
  }
  else
  {
     digitalWrite(ledPin, LOW);     //当光照强度过低时led亮。
  }
}
