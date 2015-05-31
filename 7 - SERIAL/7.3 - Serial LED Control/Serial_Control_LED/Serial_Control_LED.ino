byte ch;                    //定义变量ch
int led = 13;                 //定义LED灯端口
void setup()
{
  Serial.begin(9600);         //设置通信波特率为9600
  pinMode(led,OUTPUT);
}

void loop()
{
  if ( Serial.available() )       //判断缓冲器是否接收到数据
  {
    ch = Serial.read();        //有数据，将接收到的数据赋值ch
if ( ch == '1' )           //收到数据‘1’
    {
      Serial.println("Turn ON");
      digitalWrite(led, HIGH);
    }
    else if(ch == '0')          //收到数据‘0’
    {
      Serial.println("Turn OFF");
      digitalWrite(led, LOW);
    }
  }
}
