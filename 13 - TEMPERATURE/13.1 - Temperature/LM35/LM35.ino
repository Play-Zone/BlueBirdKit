#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
int temperaturePin = A0;  //温度读取引脚
int temperatureValue = 0;

byte temperatureSymbol[8] = {  //创建 ‘℃’符号 
  B10110,
  B01001,
  B01000,
  B01000,
  B01000,
  B01001,
  B00110
};

void setup() {
  lcd.init();        //液晶初使化
  lcd.backlight();   //打开背光
  lcd.createChar(0,temperatureSymbol);   //将数量写入寄存器
}

void loop() {
  temperatureValue = analogRead(temperaturePin);
  lcd.setCursor(0,0);
  lcd.print("  Temperature ");
  lcd.setCursor(5,1);
  lcd.print(temperatureValue*0.48);  //单位转换，10mV对应1度 temperature * (5/1024)*100
  lcd.write(byte(0));   //显示℃符号
  delay(700);
  lcd.clear();
}
