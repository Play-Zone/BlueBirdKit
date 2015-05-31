int led=11;
void setup()
{
  pinMode(led,OUTPUT);         //数字口要选择带~号的具有pwm功能的输出口
}
 
void loop()
{
  int n = analogRead(A0);      //读取A0模拟口的数值（0-5V 对应 0-1204取值）
  analogWrite(led,n/4);        //PWM最大取值255  模拟转换的最大值为1024，所以
}                       
