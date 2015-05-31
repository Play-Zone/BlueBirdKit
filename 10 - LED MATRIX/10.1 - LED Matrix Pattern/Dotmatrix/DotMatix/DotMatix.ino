//**************************************************************//
//  Name    : shiftOutCode, Dual Binary Counters                 //
//  Author  : Carlyn Maw, Tom Igoe                               //
//  Date    : 25 Oct, 2006                                       //
//  Version : 1.0                                                //
//  Notes   : Code for using a 74HC595 Shift Register            //
//          : to count from 0 to 255                             //
//**************************************************************//

//Pin connected to ST_CP of 74HC595 -RCK
int latchPin = 10;
//Pin connected to SH_CP of 74HC595 -SRCK
int clockPin = 11;
//Pin connected to DS of 74HC595 -SER
int dataPin = 9;

byte faceData[]={0xc3,0xc3,0x00,0x00,0x18,0x18,0x42,0x3c};
void setup(){
  pinMode(latchPin,OUTPUT);
}
void disp(){
  for(int i=0;i<8;i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,~(1<<i));
    shiftOut(dataPin,clockPin,faceData[i]);
    digitalWrite(latchPin,HIGH);
  }
}
void loop(){
  disp();
}
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low
 
  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);
 
  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, LOW);
  digitalWrite(myClockPin, LOW);
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, LOW);
    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) {
      pinState= HIGH;
    }
    else {        
      pinState= LOW;
    }
    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, HIGH);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, LOW);
  }
  //stop shifting
  digitalWrite(myClockPin, LOW);
}
