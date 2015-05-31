//***************************************************************//
//  Name    : Segment Display Code                               //
//  Author  : YFROBOT, beliefs                                   //
//  Date    : 18 May, 2013                                       //
//  Version : 1.0                                                //
//  Notes   : Code for a segment display with 74HC164            //
//***************************************************************//
int clockPin = 12;                                  //时钟引脚CP
int dataPin = 8;                                    //数据引脚AB
unsigned char const comPin[4]={2,3,4,5};                  //位选引脚定义

unsigned char const segmentDigits[11][8]={             //数字0－9段值
// a b c d e f g //
  {0,0,0,0,0,0,1,1},            //*0*
  {1,0,0,1,1,1,1,1},            //*1*
  {0,0,1,0,0,1,0,1},            //*2*
  {0,0,0,0,1,1,0,1},            //*3*
  {1,0,0,1,1,0,0,1},            //*4*
  {0,1,0,0,1,0,0,1},            //*5*
  {0,1,0,0,0,0,0,1},            //*6*
  {0,0,0,1,1,1,1,1},            //*7*
  {0,0,0,0,0,0,0,1},            //*8*
  {0,0,0,0,1,0,0,1},            //*9*
  {1,1,1,1,1,1,1,1}            //全灭
};

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
     digitalWrite(comPin[i],HIGH);  //位选通
     for(int j=0;j<=7;j++){
       digitalWrite(clockPin,LOW);    //先将时钟线拉低，上升沿边缘触发
       digitalWrite(dataPin,segmentDigits[data[i]][7-j]);   //数据位赋值，高位先入
       digitalWrite(clockPin,HIGH);   //将时钟信号线拉高
     }   
     delay(6);                   //显示延时2秒
     digitalWrite(comPin[i],LOW);  //关闭位选
     for(int k=0;k<8;k++){          //数据位赋0xFF,清除显示
     digitalWrite(clockPin,LOW);
     digitalWrite(dataPin,segmentDigits[11][k]);
     digitalWrite(clockPin,HIGH);
    }
  }
}
void setup()
{
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  for(int i=2;i<=5;i++){    //IO口初使化，数字2－13全部配置为输出模式
    pinMode(i,OUTPUT);
  }
}

void loop()
{ 
  int count = 0;       //计数变量
  while(1){
    count ++;          //自加
    ledDisp(count);    
    if(count > 9999)  //如果显示值大于9999，则清零count，重新计数
      count = 0;
  }
}
