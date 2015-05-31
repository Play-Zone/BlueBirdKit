int Flame=A0;     //定义火焰接口为模拟0接口
int Buzzer=12;    //定义蜂鸣器接口为数字12接口
int val=0;        //定义数字变量val
int Sensor_threshold = 200; //传感器阀值为200,可自行调节
void setup() 
{ 
  pinMode(Buzzer,OUTPUT); //定义蜂鸣器为输出接口
  Serial.begin(9600);    //设定波特率为9600 
} 
void loop() 
{ 
  val=analogRead(Flame);//读取火焰传感器的模拟值 
  Serial.println(val); //输出模拟值，并将其打印出来
  if(val>=Sensor_threshold)          //当模拟值大于阀值时蜂鸣器鸣响
  { 
    digitalWrite(Buzzer,HIGH); 
  } else 
  { 
    digitalWrite(Buzzer,LOW);
  }
  delay(200);
 }
