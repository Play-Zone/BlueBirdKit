int R_led = 9;
int G_led = 10;
int B_led = 11;

void setup() {
  pinMode(R_led,OUTPUT);
  pinMode(G_led,OUTPUT);
  pinMode(B_led,OUTPUT);
}
void loop() {
   //RGB 输出值
  int R_val;
  int G_val;
  int B_val;
  for ( R_val=0; R_val<=255;R_val++)        //循环语句，控制R亮度增加        
  {
    G_val = 255-R_val;                       //控制G亮度减小
    B_val = 255;                             //控制B亮度不变
    analogWrite(R_led,R_val);
    analogWrite(G_led,G_val);
    analogWrite(B_led,B_val);
    delay(10);             
  }
  for ( B_val=255; B_val>=0;B_val--)         //循环语句，控制PWM亮度减小    
  {
    R_val = 255;                             //控制R亮度不变
    G_val = 255 - B_val;                     //控制G亮度增加
    analogWrite(R_led,R_val);
    analogWrite(G_led,G_val);
    analogWrite(B_led,B_val);
    delay(10);                             
  } 
  for ( R_val=255; R_val>=0;R_val--)        //循环语句，控制PWM亮度减小      
  {
    G_val = 255 ;                           //控制R亮度不变
    B_val = 255 - R_val;                    //控制B亮度增加
    analogWrite(R_led,R_val);
    analogWrite(G_led,G_val);
    analogWrite(B_led,B_val);
    delay(10);                             
  }
}
  

