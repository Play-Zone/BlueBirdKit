#define SENSOR A0     //定义传感器输入引脚为模拟1 口
int val = 0;            //定义变量储存传感器的返回值
void setup()
{
  Serial.begin(9600); //打开串口并设置通信波特率为9600
}
void loop()
{
  val = analogRead(SENSOR); //读取传感器接口反馈值
  Serial.println(val);         //串口监视窗口显示传感器返回值
  delay(100);               //每100 毫秒发送一次数据
}
