/*****************************************************************
Example sketch for interfacing with the DS1302 timekeeping chip.
Copyright (c) 2009, Matt Sparks
All rights reserved.
http://quadpoint.org/projects/arduino-ds1302
*******************************************************************/
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
/* Set the appropriate digital I/O pin connections */
uint8_t CE_PIN   = 5;
uint8_t IO_PIN   = 6;
uint8_t SCLK_PIN = 7;

int temperaturePin = A0;  //温度读取引脚
float temperatureValue = 0;
byte temperatureSymbol[8] = {  //创建 ‘℃’符号 
  B10110,
  B01001,
  B01000,
  B01000,
  B01000,
  B01001,
  B00110
};
/* Create a DS1302 object */
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);
String dayBuff[7]={"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};
void print_time()
{
  /* Get the current time and date from the chip */
  Time t = rtc.time();//*
  lcd.setCursor(0,0);
  lcd.print(t.yr);
  lcd.print('-');
  lcd.print(t.mon/10);
  lcd.print(t.mon%10);
    lcd.print('-');
  lcd.print(t.date/10);
  lcd.print(t.date%10);
  lcd.setCursor(13,0);
  lcd.print(dayBuff[t.day-1]);
  lcd.setCursor(0,1);
  lcd.print(t.hr/10);
  lcd.print(t.date%10);
  lcd.print(':');
  lcd.print(t.min/10);
  lcd.print(t.date%10);
  lcd.print(':');
  lcd.print(t.sec/10);
  lcd.print(t.sec%10);
  lcd.setCursor(10,1);
  temperatureValue = analogRead(temperaturePin);
  lcd.print((float)temperatureValue*0.48);
  lcd.write(byte(0));
}
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,temperatureSymbol);
  rtc.write_protect(false);    //WP(write protect) = 0;
  rtc.halt(false);             //clock halt flag = 0;
  Time t(2015, 1, 1, 10, 18, 30, 4);   //time inital: 2011-1-1,10:18:30 thursday
  rtc.time(t);
}
void loop()
{
  
  print_time();    //Print the current time;
}
