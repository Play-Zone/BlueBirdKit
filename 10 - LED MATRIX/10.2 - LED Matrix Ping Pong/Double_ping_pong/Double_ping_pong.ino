/***********************************************************************
 * Double ping-pong game
 * ( 8x8 Led Dot Matrix with two 74HC595 on Arduino)
 *
 * by YFROBOT 
 ***********************************************************************/

#include "TimerOne.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define PIN_RedPlayer_Left 0          // declaring the pin for player 1's buttons
#define PIN_RedPlayer_Right 1          
#define PIN_BluePlayer_Right 2        // declaring the pin for player 2's buttons
#define PIN_BluePlayer_Left 3
#define ROW_DATA ((row[0]<<7)|(row[1]<<6)|(row[2]<<5)|(row[3]<<4)|(row[4]<<3)|(row[5]<<2)|(row[6]<<1)|(row[7]<<0))
#define COL_DATA ((col[0]<<7)|(col[1]<<6)|(col[2]<<5)|(col[3]<<4)|(col[4]<<3)|(col[5]<<2)|(col[6]<<1)|(col[7]<<0))

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//Pin connected to DS of 74HC595
int SER = 9;
//Pin connected to ST_CP of 74HC595
int RCK  = 10;
//Pin connected to SH_CP of 74HC595
int SRCK  = 11;

unsigned int left = 0;
unsigned int right = 0;
//The Blue Button
unsigned int BlueButton_R = 0;
unsigned int BlueButton_L = 0;
//The Red Button
unsigned int RedButton_R = 0;
unsigned int RedButton_L = 0;
int BlueScore = 0;
int RedScore = 0;
int angle = 0;
int radians;

//Define row and col array
int row[8]={
  0, 0, 0, 0, 0, 0, 0, 0};   //row0,row1,row2,row3,row4,row5,row6,row7

int col[8]={
  0, 0, 0, 0, 0, 0, 0, 0};   //col0,col1,col2,col3,col4,col5,col6,col7

byte screen[8] = {
  0, 0, 0, 0, 0, 0, 0, 0};
volatile byte screenRow = 0;
volatile byte screenCol = 0;

int _angle;    
int _px;
int _py;
int _w = 7;
int _h = 7;
int _wall[] = {
  3, 3};
int _count = 0;
int _speed = 3;
int _countPoints = 0;

void setup() {

  Timer1.initialize(100);
  pinMode(RCK, OUTPUT);      // pins are outputs
  pinMode(SRCK, OUTPUT);
  pinMode(SER, OUTPUT);
  Timer1.attachInterrupt(doubleBuffer);  //interrupt function
//  attachInterrupt(0, restartGame, LOW);

  lcd.init();                      // initialize the lcd 
  lcd.backlight();                 // Print a message to the LCD.

  Serial.begin(9600);             //Start Serial for debuging purposes
  lcd.setCursor(0,0);
  lcd.print("The game will soonstart!");
  lcd.setCursor(0,1);
  lcd.print("on start!");
  face();      //Display Smile Face
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("READY GO!");
  reset();     //reset
  lcd.clear();
  
}
//interrupt function
void doubleBuffer() {
  row[screenRow]=0;
  col[screenCol]=1;  

  screenCol++;
  if (screenCol >= 8) {
    screenCol = 0;
    screenRow++;
    if (screenRow >= 8) {
      screenRow = 0;
    }
  }
  if((screen[screenRow] >> screenCol) & B1 == B1) {
    row[screenRow]=1;
    col[screenCol]=0;
    digitalWrite(RCK,LOW);
    shiftOut(COL_DATA);
    shiftOut(ROW_DATA);
    digitalWrite(RCK,HIGH);
  } 
  else {
    row[screenRow]=0;
    col[screenCol]=1;
  }
}

void allOFF() {
  for (int i = 0; i < 8; i++)
    screen[i] = 0;
}

void on(byte row, byte column) {
  screen[column-1] |= (B1 << (row - 1));
}

void off(byte row, byte column) {
  screen[column-1] &= ~(B1 << (row - 1));
}
//Read the Blue's Button
void BlueButton(){
  BlueButton_R = analogRead(PIN_BluePlayer_Right);
  BlueButton_L = analogRead(PIN_BluePlayer_Left);
  if(BlueButton_L >800 ){
    if(right>5){
      right =6;
    }
    else{
      right ++;
    }
    delay(40);
  }
  else if(BlueButton_R > 800){
    if(right<1){
      right =0;
    }
    else{
      right --; 
    }
    delay(40);
  }
  else{
  }
}
//Read the Red's Button
void RedButton(){
  RedButton_R = analogRead(PIN_RedPlayer_Right);
  RedButton_L = analogRead(PIN_RedPlayer_Left);
  if(RedButton_L >800 ){
    if(left>5){
      left =6;
    }
    else{
      left ++;
    }
    delay(40);
  }
  else if(RedButton_R > 800){
    if(left<1){
      left =0;
    }
    else{
      left --; 
    }
    delay(40);
  }
  else{
  }
}
void calcWall()
{
  RedButton();
  BlueButton();
  clearWall();

  on(1, left + 1);
  on(1, left + 2);
  on(8, right + 1);
  on(8, right + 2);

  _wall[0] = left;
  _wall[1] = right;
  show();
}

void clearWall()
{
  for (int i = 0; i < 8; i++)
    screen[i] &= B01111110;
}

void clearGame()
{
  for (int i = 0; i < 8; i++)
    screen[i] &= B10000001;
}

void Score(){
  lcd.setCursor(0,0);
  lcd.print("Blue Score:");
  lcd.setCursor(11,0);
  lcd.print(BlueScore);
  lcd.setCursor(0,1);
  lcd.print("Red Score :");
  lcd.setCursor(11,1);
  lcd.print(RedScore);
}

void loop() {
  Score();
  calcWall();
  enterFrameHandler();
  delay(50);
}
//Frame Handler
void enterFrameHandler()
{
  if (_count++ < _speed)
    return;

  _count = 0;
  checkCollision();
  calcAngleIncrement();
  show();
}

void retorted(int angle)
{
  Serial.println(angle);
  _angle = angle;

  if (++_countPoints % 5 == 0 && _speed > 1)
    _speed--;
}

void resetAnim()
{
  for (int i = 0; i < 8; i++)
  {
    screen[i] = B11111111;
    delay(15);
  }
  for (int i = 0; i < 8; i++)
  {
    screen[i] = B00000000;
    delay(15);
  }
}

void face()
{
  on(1, 1);  
  on(1, 2);
  on(1, 7);  
  on(1, 8);
  on(2, 1);  
  on(2, 2);
  on(2, 7);  
  on(2, 8);
  on(4, 4);
  on(4, 5);
  on(5, 4);
  on(5, 5);
  on(7, 2);
  on(7, 7);
  on(8, 3);
  on(8, 4);
  on(8, 5);
  on(8, 6);
  delay(5000);
}

void reset()
{
  resetAnim();

  _px = random(3, 5);
  _py = random(3, 5);
  _angle = random(0, 2) == 0 ? 0 : 180;
  _speed = 5;
  _countPoints = 0;

  show();
  delay(500);
}

void show()
{
  clearGame();
  on(_px + 1, _py + 1);
}
//Collision check
void checkCollision()
{
  if (_px == _w - 1)
  {
    if (_angle == 315 || _angle == 0 || _angle == 45)
    {
      if (_py == _wall[1] || _py == _wall[1] + 1)
      {
        if (_angle == 0 && _py == _wall[1])
          retorted(225);
        else if (_angle == 0 && _py == _wall[1] + 1)
          retorted(135);
        else if (_angle == 45 && _py == _wall[1])
          retorted(135);
        else if (_angle == 45 && _py == _wall[1] + 1)
          retorted(180);
        else if (_angle == 315 && _py == _wall[1])
          retorted(180);
        else if (_angle == 315 && _py == _wall[1] + 1)
          retorted(225);
      }
    }
  }
  else if (_px == 1)
  {
    if (_angle == 225 || _angle == 180 || _angle == 135)
    {
      if (_py == _wall[0] || _py == _wall[0] + 1)
      {
        if (_angle == 180 && _py == _wall[0])
          retorted(315);
        else if (_angle == 180 && _py == _wall[0] + 1)
          retorted(45);
        else if (_angle == 135 && _py == _wall[0])
          retorted(45);
        else if (_angle == 135 && _py == _wall[0] + 1)
          retorted(0);
        else if (_angle == 225 && _py == _wall[0])
          retorted(0);
        else if (_angle == 225 && _py == _wall[0] + 1)
          retorted(315);
      }
    }
  }
  if (_px == _w)
  {
    RedScore++;
    reset();
  }
  else if (_px == 0)
  {
    BlueScore++;
    reset();
  }
  else if (_py == _h)
  {
    if (_angle == 45)
      _angle = 315;
    else if (_angle == 135)
      _angle = 225;
  }
  else if (_py == 0)
  {
    if (_angle == 225)
      _angle = 135;
    else if (_angle == 315)
      _angle = 45;
  }
}

//Calculate the Angle increment
void calcAngleIncrement()
{
  if (_angle == 0 || _angle == 360)
  {
    _px += 1;
  }
  else if (_angle == 45)
  {
    _px += 1;
    _py += 1;
  }
  else if (_angle == 135)
  {
    _px -= 1;
    _py += 1;
  }
  else if (_angle == 180)
  {
    _px -= 1;
  }
  else if (_angle == 225)
  {
    _px -= 1;
    _py -= 1;
  }
  else if (_angle == 315)
  {
    _px += 1;
    _py -= 1;
  }
}
//shift function
void shiftOut(byte myDataOut) {
  //internal function setup
  boolean pinState;

  //clear shift register read for sending data
  digitalWrite(RCK, LOW);
  // for each bit in dataOut send out a bit
  for (int i = 0; i <= 7; i++)  {
    //set clockPin to LOW prior to sending bit
    digitalWrite(SRCK, LOW);
    /*if the value of DataOut and (logical AND) a bitmask
     are true, set pinState to 1 (HIGH)*/
    if ( myDataOut & (1<<i) ) {
      pinState= HIGH;
    }
    else {     
      pinState= LOW;
    }
    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(SER, pinState);
    //send bit out on rising edge of clock
    digitalWrite(SRCK, HIGH);
    digitalWrite(SER, LOW);
  }
  //stop shifting
  digitalWrite(SRCK, LOW);
}


