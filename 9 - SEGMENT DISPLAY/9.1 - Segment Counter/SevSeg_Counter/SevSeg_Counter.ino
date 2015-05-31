unsigned char const dataPin[8]={6,7,8,9,10,11,12,13};  //段选引脚定义
unsigned char const comPin[4]={2,3,4,5};              //位选引脚定义
unsigned char const segmentDigits[10][7]={          // 数字0－9的段码
//a b c d e f g //
  {0,0,0,0,0,0,1},            //*0*
  {1,0,0,1,1,1,1},            //*1*
  {0,0,1,0,0,1,0},            //*2*
  {0,0,0,0,1,1,0},            //*3*
  {1,0,0,1,1,0,0},            //*4*
  {0,1,0,0,1,0,0},            //*5*
  {0,1,0,0,0,0,0},            //*6*
  {0,0,0,1,1,1,1},            //*7*
  {0,0,0,0,0,0,0},            //*8*
  {0,0,0,0,1,0,0},            //*9*
};
void clearDisp()              //清空显示
{   
  for(int j=0;j<4;j++){
    digitalWrite(comPin[j],LOW);     //位选送低电平信号
  }
  for(int i=0;i<8;i++){
    digitalWrite(dataPin[i],HIGH);   //段选送高电平信号
  }
}

void ledData(int n,int data)    
{   
  for(int i=0;i<80;i++){        //单次数据显示延迟
   digitalWrite(comPin[n],HIGH);  //位选通
   for(int j=0;j<=6;j++){
     digitalWrite(dataPin[j],segmentDigits[data][j]);//段选赋值数据
   }   
  }
   digitalWrite(comPin[n],LOW);  //关闭位选
}

void ledDisp(short int a)    //n：显示位   data：显示数据
{
  int q, b, s, g = 0;    
  q = a/1000;                //千位
  b = a%1000/100;            //百位
  s = a%1000%100/10;         //十位
  g = a%1000%100%10;         //个位
  char data[4]={q,b,s,g};
    for(int i=0;i<=3;i++)
    {
      ledData(i,data[i]);
    }
    clearDisp();
}
void setup()
{
  for(int i=2;i<=13;i++){    //IO口初使化，数字2－13全部配置为输出模式
    pinMode(i,OUTPUT);
  }
}

void loop()
{ 
  int count = 0;       //计数变量
  while(1){
    count ++;          //自加
    ledDisp(count);    
    if(count > 9999){   //如果显示值大于9999，则清零count，重新计数
      count = 0;
    }
  }
}
