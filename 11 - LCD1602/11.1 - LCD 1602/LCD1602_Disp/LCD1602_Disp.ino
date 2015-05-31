#include <Wire.h>             //包含I2C的代码
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // PCA8574的A0-A2＝1，所以地址为0X27。
                                 // 16表示16列，2表示2行
void setup(){
  lcd.init();                   //液晶的初使化
  lcd.noBacklight();            //关闭背光
  lcd.setCursor(0,0);          //光标移动到第1行第1列
  lcd.print("Hello, world!");   //第一行显示“Hello， world”
  lcd.setCursor(0,1);          //光标移动到第2行第1列
  lcd.print('a',HEX);          //显示字符“a”的十六进制数值
}
void loop(){
}
