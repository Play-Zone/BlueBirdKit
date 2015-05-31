#include <dht11.h>       //DHT11传感器头文件
dht11 DHT11;             
#define Dht11Pin A1      //DHT11引脚配置

void setup()
{
  Serial.begin(9600);    //初使化波特率9600
  Serial.println("DHT11 Monitoring");
  Serial.print("\n");
}
void loop()
{
  int val = DHT11.read(Dht11Pin);  //读取传感器数值
  Serial.print("Read sensor: ");
  switch (val)
  {
  case DHTLIB_OK:           //读取数据成功
    Serial.println("OK");
    break;
  case DHTLIB_ERROR_CHECKSUM:    //数据校验错误
    Serial.println("Checksum error"); 
    break;
  case DHTLIB_ERROR_TIMEOUT:    //接收数据超时
    Serial.println("Time out error"); 
    break;
  default:     //未知错误
    Serial.println("Unknown error"); 
    break;
  }
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity); //打印输出湿度
  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature);//打印输出温度
  delay(2000);
}
